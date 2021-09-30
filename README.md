### Home

### What is Sense-Able?
(Forked and edited Fall 2021, Caleb Kisby)

Sense-Able is a research demo / proof-of-concept that I worked on alongside Austin Scampini, Jonathan Senn, Kathryn Vincent, and Jinyu Gao from Fall 2017 - Spring 2018.  During this time, we worked with clients (Peter Mumola and Joel Arenson) on using a LeddarTech® LIDAR sensor to help those with visual impairments avoid walls, pillars, stairs, etc.

But we were senior undergrads -- a full-blown assistance tool was probably a bit ambitious.  And so we ended up producing a program that can detect walls and wall corners by fitting the points to a polynomial curve.  Despite this being much simpler for the current me, I'm still proud of what we accomplished.

The companion app we developed provides the following features:
- A **real-time stream** where you can point the LIDAR to detect walls and wall corners
- An option to detect via a **recorded stream**
- An option to **record your own files** for testing.

Sense-Able is **not** in a suitable condition for real-time use by a person with visual impairments -- **See the warning below.**

### Setup Instructions
First, download and install the latest release [here!](https://github.com/SCCapstone/Sense-Able/releases)

Run the installation script from the terminal:

	sudo ./install-senseable
 
Then run the program via the wrapper script from the `build` directory:

	./runSenseAbleGui

More detailed build instructions can be found in the `docs` directory.  Additionally, I personally wrote up a tutorial
for using the LeddarTech® SDK (`docs/LeddarSDK-C_Tutorial.pdf`) to help future developers save time where we struggled.

### Demonstration
If you would like to take a look at our app and hardware setup in use, just watch this brief video demonstration:
[![Link to the Sense-Able Tutorial](https://user-images.githubusercontent.com/31460278/39223618-0ac9d446-4811-11e8-9f74-4ad2ffee8463.png)](https://youtu.be/I3KSW96VbEU "Sense-Able Tutorial")

### Explore Features
Alternatively, if you would just like to look at the interface and glean a brief sense of what we did, you can visit our [features](https://sccapstone.github.io/Sense-Able/features) page.

### About
To find out more about us (the developers) and our clients, please visit the [about us](https://sccapstone.github.io/Sense-Able/about) page.

### WARNING
The Sense-Able app is currently a research demo, intended for demonstration only.  We strongly advise against using Sense-Able, in its current state, to avoid contact with any of the obstacles supported or unsupported.  By using this app, you agree to the condition that the SCCapstone group, and all members within, are not responsible or liable for any injury that resulted from use of this app.

