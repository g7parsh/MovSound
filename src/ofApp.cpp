#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
threshhold = 0;
ofBackground(ofColor::forestGreen);
	song.loadSound("sounds/Seeya.mp3");
	song.play();
	song.setVolume(1.0);
	song.setLoop(true);

	fftSmoothed = new float[8192];
	for (int i = 0; i < 8192; i++){
		fftSmoothed[i] = 0;
	}
ofPoint center = ofPoint(ofGetWidth()/2,ofGetHeight()/2);

	nBandsToGet = 128;

	for(int i = 0; i < nBandsToGet; i++){
        wave.addVertex(3*i+ ofGetWidth()/2-(4*nBandsToGet/2),ofGetHeight()/2);


	}

//wave.arc(center,(nBandsToGet/2),1,0,180,true,nBandsToGet);

}

//--------------------------------------------------------------
void ofApp::update(){
	ofSoundUpdate();
    angle += fftSmoothed[13];
    threshhold+= angle;

    if (fftSmoothed[13]*75 > 5 and timer < 0 ){
            for(int i = 0 ; i < ofRandom(5,20); i ++){
        fireworks.push_back(Particle(ofPoint(ofRandom(0,ofGetWidth()),ofRandom(ofGetHeight()-200, ofGetHeight())),
                                     ofVec2f(0,0),
                                     ofColor(ofRandom(255),ofRandom(255),ofRandom(255))));
            }
        timer = 60;

    }

    for(int i = 0; i < fireworks.size();i++){

                if (threshhold % 360 >180 && !fireworks[i].destroy){

        fireworks[i].applyForces();
        fireworks[i].update();

                }
    }
	float * val = ofSoundGetSpectrum(nBandsToGet);		// request 128 values for fft
	for (int i = 0;i < nBandsToGet; i++){

		// let the smoothed calue sink to zero:
		fftSmoothed[i] *= 0.96f;

		// take the max, either the smoothed or the incoming:
		if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];

	}
	timer --;

}

//--------------------------------------------------------------
void ofApp::draw(){
    for(int i = 0 ; i < fireworks.size(); i++){
            if (!fireworks[i].destroy){
        fireworks[i].draw();
    }
    }

ofSetColor(ofColor::black);
float width = (float)(ofGetWidth()) / nBandsToGet;

	vector<ofPoint> myPoints = wave.getVertices();
	ofPushMatrix();

	for(int i = 0; i < myPoints.size();i++){



        ofPoint temp = myPoints[i];
        int radius = atan2(abs(temp.x - ofGetWidth()/2),abs(temp.y - ofGetHeight()/2));
        //temp.x =(ofGetWidth()/2) + radius*cos(angle);

        //temp.y =(ofGetHeight()/2) + radius*sin(angle);
        temp.y += sin(temp.y + angle*.5)*100;
        temp.x += cos(temp.x + angle*.5)*100;
        //temp.z *= fftSmoothed[10];


        ofSetColor(fftSmoothed[3]*255,fftSmoothed[7]*100,fftSmoothed[1]*255);
        ofCircle(temp ,((fftSmoothed[6]*100 > 2) ? fftSmoothed[6]*100 : 2));

	}
	ofPopMatrix();

	wave.close();
	for (int i = 0;i < nBandsToGet; i++){
		// (we use negative height here, because we want to flip them
		// because the top corner is 0,0)

		ofRect(i*width,ofGetHeight(),width,-(fftSmoothed[i] * 200));


	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
fireworks.push_back(Particle(ofVec2f(mouseX,mouseY),ofVec2f(0,0),ofColor(ofColor::red)));
cout << "x: " << x << ": y: " << y << endl;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
