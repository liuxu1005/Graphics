#ifndef CONE_H
#define CONE_H

#include "Shape.h"
#include <vector>
#define  UNIT 1.0

#include <iostream>

class Cone : public Shape {
public:
	Cone() {};
	~Cone() {};
	
    double Intersect(Point eyePoint, Vector rayV, Matrix transformMatrix) {
        Matrix t = invert(transformMatrix);
        Point p = t * eyePoint;
        Vector v = t * rayV;
        
        bool changed = false;
        double distance = -1;
        double tmp = -1;
        //check side
        tmp = sideDist(p, v);
        if( tmp >= 0 ) {
            if (!changed) {
                distance = tmp;
                changed = true; 
            }
            else if (distance > tmp) {
                distance = tmp;     
            }
        }
        
        //check bottom
        tmp = calDist(p, v, -0.5);
        if( tmp >= 0 ) {
            if (!changed) {
                distance = tmp;
                changed = true; 
            }
            else if (distance > tmp) {
                distance = tmp;     
            }
        } 
        return distance;
    }
    
	Vector findIsectNormal(Point eyePoint, Vector ray, double dist) {
	    Point intersection = eyePoint + dist * ray;
	    double td = intersection[0] * intersection[0] + 
	                intersection[2] * intersection[2];
	    double ty =  (0.5 - intersection[1]) *  (0.5 - intersection[1]) * 0.25;          
	    if(td > ty - 0.0001  && td < ty + 0.0001) {
	        double y = intersection[1] - 0.5 * sqrt(td);
	        Vector n(intersection[0], intersection[1] - y, intersection[2]);
	        n.normalize();
	        return n;
	    }
  
	    if ( intersection[1] > -0.5001 && intersection[1] < -0.4999) {
	        return Vector(0, -1, 0);
	    } 
	 
	    return Vector(0, 0, 0);	
	}

	void draw() {
	    if ((m_segmentsY != vertices.size() - 1) 
	    || (m_segmentsX != vertices[0].size()))
	    calV_N();
	        
        glBegin(GL_TRIANGLES);
        for (int i = 0; i < m_segmentsY; i++) {
	        int nextl = i + 1;
	        for (int j = 0; j < m_segmentsX; j++) {
	            
	            int nextv = (j + 1) % m_segmentsX; 
	            
	            glNormal3f(normal[j][0], normal[j][1], normal[j][2]);
	            glVertex3f(vertices[i][j][0], 
	                       vertices[i][j][1], 
	                       vertices[i][j][2]);
	            glNormal3f(normal[j][0], normal[j][1], normal[j][2]);
	            glVertex3f(vertices[nextl][j][0], 
	                       vertices[nextl][j][1], 
	                       vertices[nextl][j][2]);
	            glNormal3f(normal[nextv][0], normal[nextv][1], normal[nextv][2]);
	            glVertex3f(vertices[nextl][nextv][0], 
	                       vertices[nextl][nextv][1], 
	                       vertices[nextl][nextv][2]);
	            
	            glNormal3f(normal[j][0], normal[j][1], normal[j][2]);
	            glVertex3f(vertices[i][j][0], vertices[i][j][1], vertices[i][j][2]);
	            glNormal3f(normal[nextv][0], normal[nextv][1], normal[nextv][2]); 
	            glVertex3f(vertices[nextl][nextv][0], 
	                       vertices[nextl][nextv][1], 
	                       vertices[nextl][nextv][2]);
	            glNormal3f(normal[nextv][0], normal[nextv][1], normal[nextv][2]); 
	            glVertex3f(vertices[i][nextv][0], 
	                       vertices[i][nextv][1], 
	                       vertices[i][nextv][2]);
	        }
	  
        } 
	    for (int i = 0; i < m_segmentsX; i++) {
	        glNormal3f(0, -1.0f, 0.0f);
	        glVertex3f(vertices[0][i][0], vertices[0][i][1], vertices[0][i][2]);
	        glNormal3f(0, -1.0f, 0.0f);
	        glVertex3f(0, -0.5f, 0.0f);
	        glNormal3f(0, -1.0f, 0.0f);
	        glVertex3f(vertices[0][(i + 1)%m_segmentsX][0], 
	                   vertices[0][(i + 1)%m_segmentsX][1], 
	                   vertices[0][(i + 1)%m_segmentsX][2]);
        } 
	    glEnd(); 
	};

	void drawNormal() {
	     if ((m_segmentsY != vertices.size() - 1) 
	        || (m_segmentsX != vertices[0].size()))
	        calV_N();
	    glBegin(GL_LINES);
	    glColor3f(1.0f, 0.0f, 0.0f);
	    Vector tmp;
	    for (int i = 0; i <= m_segmentsY; i++) {
	        for (int j = 0; j < m_segmentsX; j++) {
	            tmp = vertices[i][j] + normal[j]/20;
	            glVertex3f(vertices[i][j][0], 
	                       vertices[i][j][1], 
	                       vertices[i][j][2]);
	            glVertex3f(tmp[0], tmp[1], tmp[2]); 
	        }
        } 
        Vector tmp1, tmp2, bcenter;
	 
	    tmp1[0] = 0;
	    tmp1[1] = -0.1;
	    tmp1[2] = 0;
	    
	    bcenter[0] = 0;
	    bcenter[1] = -0.5;
	    bcenter[2] = 0;
	    
	    bcenter = bcenter + tmp1;
	   
	    
	    for (int j = 0; j < m_segmentsX; j++) {
	            
	            tmp2 = vertices[0][j] + tmp1;
	            glVertex3f(vertices[0][j][0], vertices[0][j][1], vertices[0][j][2]);
	            glVertex3f(tmp2[0], tmp2[1], tmp2[2]);
	         
	    }
	    glVertex3f(0, -0.5, 0);
	    glVertex3f(bcenter[0], bcenter[1], bcenter[2]);
	    	     
	    glEnd(); 
	    
	};
	
private:
    void calV_N() {
        Vector cur;
        std::vector<Vector> row;
        double unitdegree= 2*PI/m_segmentsX;
        double yunit = (UNIT)/(2 * m_segmentsY);
       
        double r = 0.5;
        vertices.clear();
        normal.clear();
        //calculate vertices
        for (int i = 0; i <= m_segmentsY; i++) {
	        for (int j = 0; j < m_segmentsX; j++) {
	            cur[0] = r * cos(j * unitdegree);
	            cur[1] = (double)i/m_segmentsY - 0.5;
	            cur[2] = r * sin(j * unitdegree); 
	            row.push_back(cur);   
	        }
	        r = r - yunit;
	        vertices.push_back(row);
	        row.clear();
        }
	    
	    float y = 1.0f/sqrt(5); 
	    float h = 2.0f/sqrt(5);
	    //calculate normals
	    for (int i = 0; i < m_segmentsX; i++) {
	    
	        cur[0] = h * cos(i * unitdegree);
	        cur[1] = y;
	        cur[2] = h * sin(i * unitdegree);
	        normal.push_back(cur);
        }
    
    
    };
    
 
     double sideDist(Point eyePoint, Vector rayV) {
        double distance = -1;  
        double y1, y2;
            
        
        double A = 4 * (rayV[0] * rayV[0] + rayV[2] * rayV[2]) - rayV[1] * rayV[1];
        double B = 8 * (eyePoint[0] * rayV[0] + eyePoint[2] * rayV[2]) 
                   - 2 * eyePoint[1] * rayV[1] + rayV[1]; 
                    
        double C = 4 * (eyePoint[0] * eyePoint[0] + eyePoint[2] * eyePoint[2])
                   - eyePoint[1] * eyePoint[1] + eyePoint[1] - 0.25;
        double tmp = B * B - 4 * A * C;   
        
        if (tmp >= 0) {
            
            double tmp1 = (-B + sqrt(tmp))/(2 * A);
            double tmp2 = (-B - sqrt(tmp))/(2 * A);
 
            y1 = eyePoint[1] + tmp1 * rayV[1];
            y2 = eyePoint[1] + tmp2 * rayV[1];
            if (tmp1 < 0 && tmp2 < 0)
                distance = -1;
            else if (tmp1 < 0 && y2 > -0.5 && y2 < 0.5)
                distance = tmp2;
            else if (tmp2 < 0 && y1 > -0.5 && y1 < 0.5)
                distance = tmp1;
            else if (y2 > -0.5 && y2 < 0.5 && y1 > -0.5 && y1 < 0.5)
                distance = tmp1 > tmp2 ? tmp2 : tmp1;
            else if (y2 > -0.5 && y2 < 0.5 )
                distance = tmp2;
            else if (y1 > -0.5 && y1 < 0.5)
                distance = tmp1;
        
        
        }
        
        return distance;
    }
 
    double calDist(Point eyePoint, Vector rayV, double position) {
        double distance = -1;  
        double x, y, z;
        double tmp = -1;               
   
        tmp = (position - eyePoint[1])/rayV[1]; 
        if (tmp < 0) return distance;
        x = eyePoint[0] + tmp * rayV[0];  
        z = eyePoint[2] + tmp * rayV[2];
        if (x * x + z * z <= 0.25)
            distance = tmp;  
    
        return distance;
    };        
    
    std::vector<std::vector<Vector> > vertices;
    std::vector<Vector> normal;    
    
};

#endif
