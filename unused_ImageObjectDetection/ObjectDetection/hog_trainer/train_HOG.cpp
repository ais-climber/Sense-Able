#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/ml.hpp"
#include "opencv2/objdetect.hpp"

#include <iostream>
#include <time.h>

using namespace cv;
using namespace cv::ml;
using namespace std;

void get_svm_detector( const Ptr< SVM > & svm, vector< float > & hog_detector );
void convert_to_ml( const std::vector< Mat > & train_samples, Mat& trainData );
void load_images( const String & dirname, vector< Mat > & img_lst, bool showImages );
// void sample_neg( const vector< Mat > & full_neg_lst, vector< Mat > & neg_lst, const Size & size );
void computeHOGs( const Size wsize, const vector< Mat > & img_lst, vector< Mat > & gradient_lst );
int test_trained_detector( String obj_det_filename, String test_dir, String videofilename );


void get_svm_detector( const Ptr< SVM >& svm, vector< float > & hog_detector )
{
    // get the support vectors
    Mat sv = svm->getSupportVectors();
    const int sv_total = sv.rows;
    // get the decision function
    Mat alpha, svidx;
    double rho = svm->getDecisionFunction( 0, alpha, svidx );
    // Assertions are made for a LINEAR SVM

    // cout << sv_total << alpha.total() << svidx.total() << endl;
    // // CV_Assert( alpha.total() == 1 && svidx.total() == 1 && sv_total == 1 );
    // CV_Assert( (alpha.type() == CV_64F && alpha.at<double>(0) == 1.) || 
    //            (alpha.type() == CV_32F && alpha.at<float>(0) == 1.f) );
    // CV_Assert( sv.type() == CV_32F );
    hog_detector.clear();

    hog_detector.resize(sv.cols + 1);
    memcpy( &hog_detector[0], sv.ptr(), sv.cols*sizeof( hog_detector[0] ) );
    hog_detector[sv.cols] = (float)-rho;
}

/*
* Convert training/testing set to be used by OpenCV Machine Learning algorithms.
* TrainData is a matrix of size (#samples x max(#cols,#rows) per samples), in 32FC1.
* Transposition of samples are made if needed.
*/
void convert_to_ml( const vector< Mat > & train_samples, Mat& trainData )
{
    //--Convert data
    const int rows = (int)train_samples.size();
    const int cols = (int)std::max( train_samples[0].cols, train_samples[0].rows );
    Mat tmp( 1, cols, CV_32FC1 ); //< used for transposition if needed
    trainData = Mat( rows, cols, CV_32FC1 );

    for( size_t i = 0 ; i < train_samples.size(); ++i )
    {
        CV_Assert( train_samples[i].cols == 1 || train_samples[i].rows == 1 );

        if( train_samples[i].cols == 1 )
        {
            transpose( train_samples[i], tmp );
            tmp.copyTo( trainData.row( (int)i ) );
        }
        else if( train_samples[i].rows == 1 )
        {
            train_samples[i].copyTo( trainData.row( (int)i ) );
        }
    }
}

// Load all images from a directory
void load_images( const String & dirname, vector< Mat > & img_lst, bool showImages = false )
{
    vector< String > files;
    glob( dirname, files );

    for ( size_t i = 0; i < files.size(); ++i )
    {
        Mat img = imread( files[i] ); // load the image
        if ( img.empty() )            // invalid image, skip it.
        {
            cout << files[i] << " is invalid!" << endl;
            continue;
        }

        if ( showImages )
        {
            imshow( "image", img );
            waitKey( 1 );
        }
        img_lst.push_back( img );
    }
}

// void sample_neg( const vector< Mat > & full_neg_lst, vector< Mat > & neg_lst, const Size & size )
// {
//     Rect box;
//     box.width = size.width;
//     box.height = size.height;
//     const int size_x = box.width;
//     const int size_y = box.height;

//     srand( (unsigned int)time( NULL ) );

//     for ( size_t i = 0; i < full_neg_lst.size(); i++ )
//     {
//         box.x = rand() % ( full_neg_lst[i].cols - size_x );
//         box.y = rand() % ( full_neg_lst[i].rows - size_y );
//         Mat roi = full_neg_lst[i]( box );
//         neg_lst.push_back( roi.clone() );
//     }
// }

void computeHOGs( const Size wsize, const vector< Mat > & img_lst, vector< Mat > & gradient_lst )
{
    cv::HOGDescriptor hog(
        wsize, //winSize
        Size(16,16), //blocksize
        Size(8,8), //blockStride,
        Size(8,8), //cellSize,
        9,        //nbins,
        1,      //derivAper,
        1,      //winSigma,
        0,      //histogramNormType,
        0.2,    //L2HysThresh,
        1,      //gammal correction,
        64,     //nlevels=64
        0);     //Use unsigned gradients
    // HOGDescriptor hog;
    // hog.winSize = wsize;



    // Rect r = Rect( 0, 0, wsize.width, wsize.height );
    // r.x += ( img_lst[0].cols - r.width ) / 2;
    // r.y += ( img_lst[0].rows - r.height ) / 2;

    Mat gray;
    vector< float > descriptors;

    for( size_t i=0 ; i< img_lst.size(); i++ )
    {
        cvtColor( img_lst[i], gray, COLOR_BGR2GRAY );
        hog.compute( gray, descriptors); // Size( 8, 8 ), Size( 8, 8 ) );
        gradient_lst.push_back( Mat( descriptors ).clone() );
    }
}

int test_trained_detector( String obj_det_filename, String test_dir, String videofilename )
{
    cout << "Testing trained detector..." << endl;
    HOGDescriptor hog;
    hog.load( obj_det_filename );

    vector< String > files;
    glob( test_dir, files );

    // for (int i=0; i<files.size(); i++){
    //     cout << files[i] << endl;
    // }

    int delay = 0;
    VideoCapture cap;

    if ( videofilename != "" )
    {
        cap.open( videofilename );
    }

    obj_det_filename = "testing " + obj_det_filename;
    namedWindow( obj_det_filename, WINDOW_NORMAL );

    for( size_t i=0; i<files.size(); i++ )
    {
        Mat img;

        if ( cap.isOpened() )
        {
            cap >> img;
            delay = 1;
        }
        else if( i < files.size() )
        {
            img = imread( files[i] );
        }

        if ( img.empty() ) 
        {
            cout << "Image not opened " << files[i] << endl;
            return 0;
        }
        else {
            vector< Rect > detections;
            vector< double > foundWeights;
            //TODO: ADJUST THESE PARAMETERS
            
            double hitThreshold = 0; // Default value
            Size winStride = Size(8,8); 
            Size padding = Size(8,8);

            hog.detectMultiScale( img, detections, foundWeights, hitThreshold, winStride);
            cout << detections.size()<< " ";
            for ( size_t j = 0; j < detections.size(); j++ )
            {   
                cout << "Height " << detections[j].height << endl;
                cout << "Width " << detections[j].width << endl;
                cout << "X " << detections[j].x << endl;
                cout << "Y " << detections[j].y << endl;
                cout << "weight " << foundWeights[j] << endl;
                Scalar color = Scalar( 0, foundWeights[j] * foundWeights[j] * 200, 0 );
                rectangle( img, detections[j], color, 2);
            }

            imshow( obj_det_filename, img );
        }

        if( 27 == waitKey( delay ) )
        {
            return 0;
        }


    }
    return 0;
}

int test_trained_SVM( String svm_filename, String test_dir, String videofilename)
{
    cout << "Testing trained detector..." << endl;
    Ptr<SVM> svm = SVM::load(svm_filename);

    vector< String > files;
    glob( test_dir, files );

    // for (int i=0; i<files.size(); i++){
    //     cout << files[i] << endl;
    // }

    int delay = 0;
    VideoCapture cap;

    if ( videofilename != "" )
    {
        cap.open( videofilename );
    }

    svm_filename = "testing " + svm_filename;
    namedWindow( svm_filename, WINDOW_NORMAL );

    for( size_t i=0; i<files.size(); i++ )
    {
        Mat img;

        if ( cap.isOpened() )
        {
            cap >> img;
            delay = 1;
        }
        else if( i < files.size() )
        {
            img = imread( files[i] );
        }

        if ( img.empty() ) 
        {
            cout << "Image not opened " << files[i] << endl;
            return 0;
        }
        else {
            vector< Rect > detections;
            vector< double > foundWeights;
            //TODO: ADJUST THESE PARAMETERS
            
            double hitThreshold = 0; // Default value
            Size winStride = Size(8,8); 
            Size padding = Size(8,8);

            float response = svm->predict(img);
            // cout << detections.size()<< " ";
            // for ( size_t j = 0; j < detections.size(); j++ )
            // {   
            //     cout << "Height " << detections[j].height << endl;
            //     cout << "Width " << detections[j].width << endl;
            //     cout << "X " << detections[j].x << endl;
            //     cout << "Y " << detections[j].y << endl;
            //     cout << "weight " << foundWeights[j] << endl;
            //     Scalar color = Scalar( 0, foundWeights[j] * foundWeights[j] * 200, 0 );
            //     rectangle( img, detections[j], color, 2);
            // }

            imshow( svm_filename, img );
        }

        if( 27 == waitKey( delay ) )
        {
            return 0;
        }


    }
    return 0;
}

int main( int argc, char** argv )
{
    const char* keys =
    {
        "{help h|     | show help message}"
        "{pd    |     | path of directory contains possitive images}"
        "{nd    |     | path of directory contains negative images}"
        "{td    |     | path of directory contains test images}"
        "{tv    |     | test video file name}"
        "{dw    |     | width of the detector}"
        "{dh    |     | height of the detector}"
        "{d     |false| train twice}"
        "{t     |false| test a trained detector}"
        "{v     |false| visualize training steps}"
        "{fn    |my_detector.yml| file name of trained SVM}"
    };

    CommandLineParser parser( argc, argv, keys );

    if ( parser.has( "help" ) )
    {
        parser.printMessage();
        exit( 0 );
    }

    String pos_dir = parser.get< String >( "pd" );
    String neg_dir = parser.get< String >( "nd" );
    String test_dir = parser.get< String >( "td" );
    String obj_det_filename = parser.get< String >( "fn" );
    String videofilename = parser.get< String >( "tv" );
    int detector_width = parser.get< int >( "dw" );
    int detector_height = parser.get< int >( "dh" );
    bool test_detector = parser.get< bool >( "t" );
    bool train_twice = parser.get< bool >( "d" );
    bool visualization = parser.get< bool >( "v" );

    // Test and Exit
    if ( test_detector )
    {
        test_trained_detector( obj_det_filename, test_dir, videofilename );
        exit( 0 );
    }

    // Are there files in the directory?
    if( pos_dir.empty() || neg_dir.empty() )
    {
        parser.printMessage();
        cout << "Wrong number of parameters.\n\n"
             << "Example command line:\n" << argv[0] << " -pd=/INRIAPerson/96X160H96/Train/pos -nd=/INRIAPerson/neg -td=/INRIAPerson/Test/pos -fn=HOGpedestrian96x160.yml -d\n"
             << "\nExample command line for testing trained detector:\n" << argv[0] << " -t -dw=96 -dh=160 -fn=HOGpedestrian96x160.yml -td=/INRIAPerson/Test/pos";
        exit( 1 );
    }

    vector< Mat > pos_lst, neg_lst, gradient_lst;
    vector< int > labels;

    clog << "Positive images are being loaded..." ;
    load_images( pos_dir, pos_lst, visualization );
    if ( pos_lst.size() > 0 )
    {
        clog << "...[done]" << endl;
    }
    else
    {
        clog << "no image in " << pos_dir <<endl;
        return 1;
    }

    Size pos_image_size = pos_lst[0].size();

    for ( size_t i = 0; i < pos_lst.size(); ++i )
    {
        if( pos_lst[i].size() != pos_image_size )
        {
            cout << "All positive images should be same size!" << endl;
            exit( 1 );
        }
    }

    // Not sure why we need to reduce the size by 64?
    pos_image_size = pos_image_size / 8 * 8;

    if ( detector_width && detector_height )
    {
        pos_image_size = Size( detector_width, detector_height );
    }

    labels.assign( pos_lst.size(), +1 );
    const unsigned int old = (unsigned int)labels.size();



    clog << "Negative images are being loaded...";
    load_images( neg_dir, neg_lst, false );
        if ( neg_lst.size() > 0 )
    {
        clog << "...[done]" << endl;
    }
    else
    {
        clog << "no image in " << neg_dir <<endl;
        return 1;
    }
    // sample_neg( full_neg_lst, neg_lst, pos_image_size );
    clog << "...[done]" << endl;

    for (size_t i=0; i<neg_lst.size(); ++i)
    {
        if (neg_lst[i].size() != pos_image_size )
        {
            cout << "All negative images must be the same size as the positive images too!" << endl;
            exit(-1);
        }
    }



    labels.insert( labels.end(), neg_lst.size(), -1 );
    CV_Assert( old < labels.size() );

    clog << "Histogram of Gradients are being calculated for positive images...";
    computeHOGs( pos_image_size, pos_lst, gradient_lst );
    clog << "...[done]" << endl;

    clog << "Histogram of Gradients are being calculated for negative images...";
    computeHOGs( pos_image_size, neg_lst, gradient_lst );
    clog << "...[done]" << endl;

    Mat train_data;
    convert_to_ml( gradient_lst, train_data );

    clog << "Training SVM...";
    Ptr< SVM > svm = SVM::create();

    svm->setType(SVM::C_SVC);
    svm->setKernel(SVM::LINEAR);
    svm->setC(1);
    svm->setGamma(0.5);
    /* Default values to train SVM */
    // svm->setCoef0( 0.0 );
    // svm->setDegree( 3 );
    // svm->setTermCriteria( TermCriteria( CV_TERMCRIT_ITER + CV_TERMCRIT_EPS, 1000, 1e-3 ) );
    // svm->setGamma( 0 );
    // svm->setKernel( SVM::RBF );
    // svm->setNu( 0.5 );
    // svm->setP( 0.1 ); // for EPSILON_SVR, epsilon in loss function?
    // svm->setC( 0.001 ); // From paper, soft classifier
    // svm->setType( SVM::C_SVC ); // C_SVC; // EPSILON_SVR; // may be also NU_SVR; // do regression task
    svm->trainAuto( train_data, ROW_SAMPLE, Mat( labels ) );
    clog << "...[done]" << endl;

    if ( train_twice )
    {
        clog << "Testing trained detector on negative images. This may take a few minutes...";
        HOGDescriptor my_hog;
        my_hog.winSize = pos_image_size;

        // Set the trained svm to my_hog
        vector< float > hog_detector;
        get_svm_detector( svm, hog_detector );
        my_hog.setSVMDetector( hog_detector );

        vector< Rect > detections;
        vector< double > foundWeights;

        for ( size_t i = 0; i < neg_lst.size(); i++ )
        {
            my_hog.detectMultiScale( neg_lst[i], detections, foundWeights );
            for ( size_t j = 0; j < detections.size(); j++ )
            {
                Mat detection = neg_lst[i]( detections[j] ).clone();
                resize( detection, detection, pos_image_size );
                neg_lst.push_back( detection );
            }
            if ( visualization )
            {
                for ( size_t j = 0; j < detections.size(); j++ )
                {
                    rectangle( neg_lst[i], detections[j], Scalar( 0, 255, 0 ), 2 );
                }
                imshow( "testing trained detector on negative images", neg_lst[i] );
                waitKey( 5 );
            }
        }
        clog << "...[done]" << endl;

        labels.clear();
        labels.assign( pos_lst.size(), +1 );
        labels.insert( labels.end(), neg_lst.size(), -1);

        gradient_lst.clear();
        clog << "Histogram of Gradients are being calculated for positive images...";
        computeHOGs( pos_image_size, pos_lst, gradient_lst );
        clog << "...[done]" << endl;

        clog << "Histogram of Gradients are being calculated for negative images...";
        computeHOGs( pos_image_size, neg_lst, gradient_lst );
        clog << "...[done]" << endl;

        clog << "Training SVM again...";
        convert_to_ml( gradient_lst, train_data );
        svm->train( train_data, ROW_SAMPLE, Mat( labels ) );
        clog << "...[done]" << endl;
    }

    vector< float > hog_detector;
    get_svm_detector( svm, hog_detector );
    HOGDescriptor hog;
    hog.winSize = pos_image_size;
    hog.setSVMDetector( hog_detector );
    hog.save( obj_det_filename );

    test_trained_detector( obj_det_filename, test_dir, videofilename );

    return 0;
}
