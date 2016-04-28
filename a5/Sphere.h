#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"
#include <cmath>

class Sphere : public Shape {
public:
	Sphere() {};
	~Sphere() {};
	
	void map(Point intersection, double *u, double *v) {
	
                if (intersection[0] > 0) {
                    *u = 0.75 - atan(intersection[2]/intersection[0]) / (2 * PI);
                } else {
                    *u = 0.25 - atan(intersection[2]/intersection[0]) / (2 * PI);
                }
                *v = asin(2 * intersection[1])/PI + 0.5;
	
	}	
    double Intersect(Point eyePoint, Vector rayV, Matrix transformMatrix) {
             
        
        Point p = transformMatrix * eyePoint;
        Vector v = transformMatrix * rayV;
        
        double A = dot(v, v);
        double B = 2 * (p[0] * v[0] + 
                   p[1] * v[1] + p[2] * v[2]);
        double C = (p[0] * p[0] + 
                   p[1] * p[1] + p[2] * p[2]) - 0.25;
        double tmp = B * B - 4 * A * C;
        if (tmp < 0 )
            return -1;
        double tmp1 = (-B + sqrt(tmp))/(2 * A);
        double tmp2 = (-B - sqrt(tmp))/(2 * A);
 
 
        if (tmp1 < 0 && tmp2 < 0)
            return -1;
        else if (tmp1 < 0)
            return tmp2;
        else if (tmp2 < 0)
            return tmp1;
        else
            return  tmp1 > tmp2 ? tmp2 : tmp1;
       
    }
	Vector findIsectNormal(Point eyePoint, Vector ray, double dist) {
	    Point intersection = eyePoint + dist * ray;
        
	    Vector n(intersection[0], intersection[1], intersection[2]);
	    double tmpl = dot(n, n);
	    if (tmpl < 0.25000001 & tmpl > 0.24999999 ) {
	        n.normalize();
	        return n;
	    }
	    else {
	        
	        return  Vector(0, 0, 0);
	    }
	    
	}

	void draw() {
	    if ((m_segmentsY != vertices.size() - 1) || (m_segmentsX != vertices[0].size()))
	        calV_N();
	    glBegin(GL_TRIANGLES);
	    
	    for (int i = 0; i < m_segmentsY; i++) {
	        int nextl = i + 1;
	        for (int j = 0; j < m_segmentsX; j++) {
	            
	            int nextv = (j + 1) % (m_segmentsX); 
	            
	            glNormal3f(vertices[i][j][0] * 2, vertices[i][j][1] * 2, vertices[i][j][2] * 2);
	            glVertex3f(vertices[i][j][0], vertices[i][j][1], vertices[i][j][2]);
	            glNormal3f(vertices[nextl][j][0] * 2, vertices[nextl][j][1] * 2, vertices[nextl][j][2] * 2);
	            glVertex3f(vertices[nextl][j][0], vertices[nextl][j][1], vertices[nextl][j][2]);
	            glNormal3f(vertices[nextl][nextv][0] * 2, vertices[nextl][nextv][1] * 2, vertices[nextl][nextv][2] * 2);
	            glVertex3f(vertices[nextl][nextv][0], vertices[nextl][nextv][1], vertices[nextl][nextv][2]);
	            
	            glNormal3f(vertices[i][j][0] * 2, vertices[i][j][1] * 2, vertices[i][j][2] * 2);
	            glVertex3f(vertices[i][j][0], vertices[i][j][1], vertices[i][j][2]);
	            glNormal3f(vertices[nextl][nextv][0] * 2, vertices[nextl][nextv][1] * 2, vertices[nextl][nextv][2] * 2); 
	            glVertex3f(vertices[nextl][nextv][0], vertices[nextl][nextv][1], vertices[nextl][nextv][2]);
	            glNormal3f(vertices[i][nextv][0] * 2, vertices[i][nextv][1] * 2, vertices[i][nextv][2] * 2); 
	            glVertex3f(vertices[i][nextv][0], vertices[i][nextv][1], vertices[i][nextv][2]);
	        }
	  
	    }  
	    
	    glEnd();
	};

	void drawNormal() {
	    if ((m_segmentsY != vertices.size() - 1) || (m_segmentsX != vertices[0].size()))
	        calV_N();
	    glBegin(GL_LINES);
	    
	    for (int i = 0; i <= m_segmentsY; i++) {
	       
	        for (int j = 0; j < m_segmentsX; j++) {
	            Vector tmp = vertices[i][j] + vertices[i][j]/5;
	            
	            glVertex3f(vertices[i][j][0], vertices[i][j][1], vertices[i][j][2]);
	            glVertex3f(tmp[0], tmp[1], tmp[2]);
	        }
	  
	    }  
	    
	    glEnd();
	};
	
private:
    void calV_N() {
    
        float xunit = 2 * PI/m_segmentsX;
        float yunit = PI/m_segmentsY;
        
        float alpha = 0.0f;
        float beta = PI/(-2);
        Vector cur;
        std::vector<Vector> row;
        vertices.clear();
        for (int y = 0; y <= m_segmentsY; y++) {
            for(int x = 0; x < m_segmentsX; x++) {
                cur[0] = 0.5 * fabs(cos(beta)) * cos(alpha);
                cur[1] = 0.5 * sin(beta);
                cur[2] = 0.5 * fabs(cos(beta)) * sin(alpha);
                row.push_back(cur);
                alpha += xunit;
            }
            vertices.push_back(row);
            row.clear();
            beta += yunit;
        
        } 
      
    }
    
    
    std::vector<std::vector<Vector> > vertices;
    
};

#endif
