#include "Mover.h"

//--------------------------------------------------------------
Mover::Mover(glm::vec2 start) {

	this->start = start;
	this->next = this->think();
	log_list.push_back(this->start);
}

//--------------------------------------------------------------
void Mover::update(int separation_rate) {

	// ��������p�̃t���O
	this->separation = false;

	// ���̏ꏊ��T��
	int param = ofGetFrameNum() % this->motion_cycle;
	if (param == 0) {

		if (this->count > 0) {
		
			this->start = this->next;
			this->next = this->think();
		}

		// �����̐ߖڂ̃^�C�~���O�ŕ����L���𔻒蔻��
		this->separation = ofRandom(100) < separation_rate;
	}
	
	// �� / ���̐���
	if(param > this->motion_cycle * 0.55) {

		auto location = this->start + ((this->next - this->start) / this->motion_cycle) * ofMap(param, this->motion_cycle * 0.55, this->motion_cycle - 1, 0, this->motion_cycle);
		this->log_list.push_back(location);
	}
	else {

		this->log_list.push_back(this->log_list.back());
	}

	// ��ʊO�ɏo�� Mover �͍폜�Ώ�
	if (this->log_list.back().x < 0 || this->log_list.back().x > ofGetWidth() || this->log_list.back().y < 0 || this->log_list.back().y > ofGetHeight()) {
		
		this->dead = true;
	}

	// �O�Օ\���p��5�t���[���������ۑ�
	while (this->log_list.size() > 5) {

		this->log_list.erase(this->log_list.begin());
	}

	this->count++;
}

//--------------------------------------------------------------
void Mover::draw(vector<unique_ptr<Mover>>& mover_list) {

	// �߂��ɂ������������
	ofFill();
	bool draw_line = false;
	for (auto& other : mover_list) {

		if (this->log_list.back() == other->getLocation()) { continue; }
		if (glm::distance(this->log_list.back(), other->getLocation()) < 100) {

			ofDrawLine(this->log_list.back(), other->getLocation());
			draw_line = true;
		}
	}

	// ���̊�_�ƂȂ�~
	if (draw_line) { ofDrawCircle(this->log_list.back(), 5); }

	// ���g�̏ꏊ�������~
	ofNoFill();
	for (int i = 0; i < this->log_list.size(); i++) {

		ofSetColor(ofMap(i, 0, this->log_list.size() - 1, 200, 39));
		ofDrawCircle(this->log_list[i], 15);
	}
}

//--------------------------------------------------------------
glm::vec2 Mover::think() {

	int radius = 175;
	int deg = ofRandom(360);
	auto tmp_next = this->start + glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
	return tmp_next;
}

//--------------------------------------------------------------
glm::vec2 Mover::getLocation() {
	
	return this->log_list.back();
}

//--------------------------------------------------------------
bool Mover::isDead() {

	return this->dead;
}

//--------------------------------------------------------------
bool Mover::isSeparation() {

	return this->separation;
}