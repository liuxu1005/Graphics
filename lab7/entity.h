/*
	File Name: entity.h
	Description:
	Author:

	Purpose: Base class to be inherited from for 3D objects that can be transformed
	Examples:
*/
#ifndef ENTITY_H
#define ENTITY_H

class entity{

public:
	/*
	Constructor
	*/
	entity();

	float getXPosition();
	float getYPosition();
	float getZPosition();

	void setPosition(float x, float y, float z);
	void setXPosition(float _x);
	void setYPosition(float _y);
	void setZPosition(float _z);

	float getXScale();
	float getYScale();
	float getZScale();

	void setScale(float _sx, float _sy, float _sz);
	void setXScale(float _sx);
	void setYScale(float _sx);
	void setZScale(float _sx);
	

private:
		// translate values
		float x,y,z;
		// scale values
		float sx,sy,sz;
};

#endif