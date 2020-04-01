#pragma once
#include "ofMain.h"

class Mover {
public:

	Mover(glm::vec2 start);
	glm::vec2 think();
	void update(int separation_rate);
	void draw(vector<unique_ptr<Mover>>& mover_list);
	glm::vec2 getLocation();
	bool isDead();
	bool isSeparation();

private:

	int motion_cycle = 60;
	unsigned int count = 0;
	glm::vec2 start;
	glm::vec2 next;
	vector<glm::vec2> log_list;
	bool dead = false;
	bool separation = false;
};