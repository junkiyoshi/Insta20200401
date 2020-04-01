#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(2);

	auto m = make_unique<Mover>(glm::vec2(ofGetWidth() * 0.5, ofGetHeight() * 0.5));
	this->mover_list.push_back(move(m));
}

//--------------------------------------------------------------
void ofApp::update() {

	// 数によって分割する確率を変化させる
	int separation_rate = ofMap(this->mover_list.size(), 1, 30, 100, 0);

	// 更新
	for (auto& mover : this->mover_list) {

		mover->update(separation_rate);
	}

	// 分割
	for (int i = 0; i < this->mover_list.size(); i++) {

		if(this->mover_list[i]->isSeparation()){

			auto m = make_unique<Mover>(this->mover_list[i]->getLocation());
			this->mover_list.push_back(move(m));
		}
	}

	// 削除
	for (int i = this->mover_list.size() - 1; i >= 0; i--) {

		if (this->mover_list[i]->isDead()) {

			this->mover_list.erase(this->mover_list.begin() + i);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (auto& mover : this->mover_list) {

		mover->draw(this->mover_list);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}