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
  
    
    std::vector<std::vector<Vector> > vertices;
    std::vector<Vector> normal;    
    
};

#endif
