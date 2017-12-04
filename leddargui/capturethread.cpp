#include "capturethread.h"

CaptureThread::CaptureThread()
{
    //0: opens webcam
    cap.open(0);
}
CaptureThread::~CaptureThread()
{
    return;
}
void CaptureThread::run()
{
    timr = new QTimer(this);
    connect(timr, SIGNAL(timeout()), this, SLOT(startCapture()));

    timr -> start(10);
}

void CaptureThread::startCapture()
{
    while(true){
        if(cap.isOpened()){
            cap >> frame;
            emit(newFrame(&frame));
        }
        else{
            std::cout<<"camera not detected";
        }
    }
}
