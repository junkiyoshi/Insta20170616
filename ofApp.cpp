#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(30);
	ofBackground(0);
	ofSetWindowTitle("20170616");

	for (int i = 0; i < 12; i++) {
		Particle particle = Particle(ofRandom(-ofGetWidth() / 2, ofGetWidth() / 2), ofRandom(-ofGetHeight() / 2, ofGetHeight() / 2), ofRandom(-512, 512));
		this->particles.push_back(particle);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	vector<int> removeIndexes = {};

	for (int i = 0; i < this->particles.size(); i++) {
		this->particles[i].think();
		this->particles[i].flok(this->particles);
		this->particles[i].borders();
		this->particles[i].update();

		if (this->particles[i].life < 0) {
			removeIndexes.push_back(i);
		}
	}

	for (int i = removeIndexes.size() - 1; i > -1; i--) {
		this->particles.erase(this->particles.begin() + removeIndexes[i]);
	}

	Leap::Frame frame = leap.frame();
	for (Leap::Hand hand : frame.hands()) {
		if (hand.isRight()) {
			for (Leap::Finger finger : hand.fingers()) {
				if (finger.tipVelocity().magnitude() > 512) {
					ofVec3f tip_point = ofVec3f(finger.tipPosition().x, finger.tipPosition().y - ofGetHeight() / 2, finger.tipPosition().z);
					Particle particle = Particle(tip_point.x + finger.direction().x * finger.length(),// * -1,
						tip_point.y + finger.direction().y * finger.length() - 1,
						tip_point.z + finger.direction().z * finger.length() - 1);
					this->particles.push_back(particle);
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	this->cam.begin();

	Leap::Frame frame = leap.frame();
	for (Leap::Hand hand : frame.hands()) {
		ofSetColor(255);
		if (hand.isRight()) {
			this->drawHand(hand);
		}
	}

	for (auto& p : this->particles) {
		p.draw();
	}

	this->cam.end();
}

//--------------------------------------------------------------
void ofApp::drawHand(Leap::Hand hand) {
	Leap::FingerList fingers = hand.fingers();
	for (int j = 0; j < fingers.count(); j++) {
		this->drawFinger(fingers[j]);
	}

	ofPushMatrix();
	ofVec3f palm_point = ofVec3f(hand.palmPosition().x, hand.palmPosition().y - ofGetHeight() / 2, hand.palmPosition().z);
	ofTranslate(palm_point);
	ofSphere(10);
	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::drawFinger(Leap::Finger finger) {

	ofVec3f tip_point = ofVec3f(finger.tipPosition().x, finger.tipPosition().y - ofGetHeight() / 2, finger.tipPosition().z);
	ofPushMatrix();
	ofTranslate(tip_point);
	ofSphere(5);
	ofPopMatrix();

	ofVec3f base_point = ofVec3f(tip_point.x + finger.direction().x * finger.length(),// * -1,
		tip_point.y + finger.direction().y * finger.length() - 1,
		tip_point.z + finger.direction().z * finger.length() - 1);
	ofPushMatrix();
	ofTranslate(base_point);
	ofSphere(5);
	ofPopMatrix();

	ofLine(tip_point, base_point);
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

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
