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
	this->previouslyCollided = 0;
	this->currentlyCollided = 0;
	return this;
}

// check collision
// object 1 is always cursor
// object 2 is always button
void compareRange(struct Range* r1, struct Range* r2){
	int r2_xRange_start = r2->x;

	int r2_xRange_end = r2->x + r2->width;
	if (r2_xRange_end > 320){
		r2_xRange_end = 320;
	}

	int r2_yRange_start = r2->y;

	int r2_yRange_end = r2->y + r2->height;
	if (r2_yRange_end > 240){
		r2_yRange_end = 240;
	}

	if (r1->x >= r2_xRange_start && r1->x < r2_xRange_end &&
		r1->y >= r2_yRange_start && r1->y < r2_yRange_end){
		r1->currentlyCollided = 1;
	} else {
		r1->currentlyCollided = 0;
	}

	if (r1->previouslyCollided == 0 && r1->currentlyCollided == 1){
		printf("Collision!");
	}

	r1->previouslyCollided = r1->currentlyCollided;

	// if it overlaps the range area and haven't been
	// detected before, it is collision
	/*if (r1->x > r2_xRange_start && r1->x < r2_xRange_end &&
			r1->y > r2_yRange_start && r1->y < r2_yRange_end
			&& r1->collided == 0){
		r1->collided = 1;
		r1->currentlyCollided = 1;
		printf("Collision happens!");
		//return 1;
	}*/
}

void checkCollision(void* cursor, void* button){
	struct Range* r_cursor = ((struct Object*)((struct Cursor*)cursor)->super)->r;
	struct Range* r_button = (struct Range*)((struct Button*)button)->range;

	int x_button_start = r_button->x;
	int y_button_start = r_button->y;
	int x_button_end = x_button_start + r_button->width;
	int y_button_end = y_button_start + r_button->height;

	// don't go overlap the boundary
	if (x_button_end > 320) {x_button_end = 320;}
	if (y_button_end > 240) {y_button_end = 240;}

	if (r_cursor->x >= x_button_start && r_cursor->x < x_button_end &&
			r_cursor->y >= y_button_start && r_cursor->y < y_button_end){
		((struct Range*)((struct Object*)((struct Cursor*)cursor)->super)->r)->currentlyCollided = 1;
	} else {
		((struct Range*)((struct Object*)((struct Cursor*)cursor)->super)->r)->currentlyCollided = 0;
	}

	if (((struct Range*)((struct Object*)((struct Cursor*)cursor)->super)->r)->previouslyCollided == 0 &&
			((struct Range*)((struct Object*)((struct Cursor*)cursor)->super)->r)->currentlyCollided == 1){
		printf("Collision detected!\n");
		printf("position of cursor is x = %d, y = %d\n", r_cursor->x, r_cursor->y);
		printf("position of button is x = %d, y = %d\n", r_button->x, r_button->y);

	}

	((struct Range*)((struct Object*)((struct Cursor*)cursor)->super)->r)->previouslyCollided =
			((struct Range*)((struct Object*)((struct Cursor*)cursor)->super)->r)->currentlyCollided;
}
