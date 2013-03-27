/*
 * Range.c
 *
 *  Created on: 2013-03-24
 *      Author: danny
 */

#include "Range.h"

struct Range* initRange(int x, int y, int w, int h) {
	struct Range* this = (struct Range*)malloc(sizeof(struct Range));
	this->x = x;
	this->y = y;
	this->width = w;
	this->height = h;
	this->collided = 0;
	return this;
}

// check collision
// object 1 is always cursor
// object 2 is always button
void compareRange(struct Range* r1, struct Range* r2){
	int r2_xRange_start = r2->x - r2->width;
	if (r2_xRange_start < 0){
		r2_xRange_start = 0;
	}

	int r2_xRange_end = r2->x + r2->width;
	if (r2_xRange_end > 320){
		r2_xRange_end = 320;
	}

	int r2_yRange_start = r2->y - r2->height;
	if (r2_yRange_start < 0){
		r2_yRange_start = 0;
	}

	int r2_yRange_end = r2->y + r2->height;
	if (r2_yRange_end > 240){
		r2_yRange_end = 240;
	}

	// if it overlaps the range area and haven't been
	// detected before, it is collision
	if (r1->x > r2_xRange_start && r1->x < r2_xRange_end &&
			r1->y > r2_yRange_start && r1->y < r2_yRange_end
			&& r1->collided == 0){
		r1->collided = 1;
		printf("Collision happens!");
		//return 1;
	}

	//return 0;
}
