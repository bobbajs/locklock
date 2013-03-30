/*
 * Range.h
 *
 *  Created on: 2013-03-24
 *      Author: danny
 */

#ifndef RANGE_H_
#define RANGE_H_
#include "Global.h"

struct Range {
	int x, y;
	int height, width;
	int previouslyCollided, currentlyCollided;
};

struct Range* initRange(int, int, int, int);
void compareRange(struct Range*, struct Range*, int);
void checkButtonCollision(void*, void*);
void checkTxtCollisionForMouse(void*, void*);
void checkImgCollisionForMouse(void*, void*);


#endif /* RANGE_H_ */
