#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetColor(255);
	ofSetLineWidth(2);
	ofSetCircleResolution(36);

	ofFbo fbo;
	ofPixels pixels;
	fbo.allocate(ofGetWidth(), ofGetHeight());
	fbo.begin();
	ofClear(0);

	ofTrueTypeFont font;
	font.loadFont("fonts/Kazesawa-Extrabold.ttf", 200, true, true, true);
	string word = "NFTs";
	font.drawString(word, ofGetWidth() * 0.5 - font.stringWidth(word) * 0.5, ofGetHeight() * 0.5 + font.stringHeight(word) * 0.5);

	fbo.end();
	fbo.readToPixels(pixels);

	this->span = 10;
	for (auto x = 0; x < ofGetWidth(); x += this->span) {

		for (int y = 0; y < ofGetHeight(); y += this->span) {

			if (pixels.getColor(x, y) != ofColor(0, 0)) {

				this->location_list.push_back(glm::vec2(x, y));
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (int i = 0; i < this->location_list.size(); i++) {

		ofPushMatrix();
		ofTranslate(this->location_list[i]);

		auto noise_value = ofNoise(ofRandom(1000), ofGetFrameNum() * 0.0035);
		auto start_param = noise_value < 0.5 ? (noise_value < 0.45 ? 0 : ofMap(noise_value, 0.45, 0.5, 0, 25)) : 25;

		auto start = this->make_point(this->span, start_param);
		auto end = this->make_point(this->span, start_param + 50);

		ofDrawLine(start, end);
		ofDrawCircle(start, 3);
		ofDrawCircle(end, 3);

		ofPopMatrix();
	}
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}