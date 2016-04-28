#ifndef SHAPE_H
#define SHAPE_H

#include <GL/glui.h>
#include "Algebra.h"


class Shape {
public:
	Shape() {m_segmentsX = 3; m_segmentsY = 3;};
	~Shape() {};

	void setSegments(int x, int y) {
		m_segmentsX = x;
		m_segmentsY = y;
	}

	virtual void draw() {};
	virtual void drawNormal() {};

protected:
	void normalizeNormal (float x, float y, float z) {
		normalizeNormal (Vector(x, y, z));
	};

	void normalizeNormal (Vector v) {
		v.normalize();
		glNormal3dv(v.unpack());
	};

	int m_segmentsX, m_segmentsY;
};

#endif
