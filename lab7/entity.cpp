/*
	File Name: entity.cpp
	Description:
	Author:

	Purpose: Base class to be inherited from for 3D objects that can be transformed
	Examples:
*/
#include "entity.h"

entity::entity(){
	x = 0;
	y = 0;
	z = 0;
	sx = 1.0;
	sy = 1.0;
	sz = 1.0;
}

float entity::getXPosition(){ return x; }
float entity::getYPosition(){ return y; }
float entity::getZPosition(){ return z; }

void entity::setPosition(float _x, float _y, float _z){
	x = _x;
	y = _y;
	z = _z;
}

void entity::setXPosition(float _x){ x = _x; }
void entity::setYPosition(float _y){ y = _y; }
void entity::setZPosition(float _z){ z = _z; }

float entity::getXScale(){ return sx; }
float entity::getYScale(){ return sy; }
float entity::getZScale(){ return sz; }

void entity::setScale(float _sx, float _sy, float _sz){
	sx = _sx;
	sy = _sy;
	sz = _sz;
}
void entity::setXScale(float _sx){ sx = _sx; }
void entity::setYScale(float _sy){ sy = _sy; }
void entity::setZScale(float _sz){ sz = _sz; }