#ifndef CYLINDER_H
#define CYLINDER_H

#include "Shape.h"

class Cylinder : public Shape {
public:
	Cylinder() {};
	~Cylinder() {};

	void draw() {
	
	    if ((m_segmentsY != vertices.size() - 1) || (m_segmentsX != vertices[0].size()))
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
	            glVertex3f(vertices[i][j][0], 
	                       vertices[i][j][1], 
	                       vertices[i][j][2]);
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
	        int tmp = (i + 1)%m_segmentsX;
	            
	        glNormal3f(0.0f, -1.0f, 0.0f);
	        glVertex3f(vertices[0][i][0], vertices[0][i][1], vertices[0][i][2]);
	        glNormal3f(0.0f, -1.0f, 0.0f);
	        glVertex3f(0.0f, -0.5f, 0.0f);
	        glNormal3f(0.0f, -1.0f, 0.0f);
	        glVertex3f(vertices[0][tmp][0], 
	        vertices[0][tmp][1], vertices[0][tmp][2]);
	         
	        glNormal3f(0.0f, 1.0f, 0.0f);
	        glVertex3f(vertices[m_segmentsY][i][0], 
	                   vertices[m_segmentsY][i][1], 
	                   vertices[m_segmentsY][i][2]);
	        glNormal3f(0.0f, 1.0f, 0.0f);
	        glVertex3f(0.0f, 0.5f, 0.0f);
	        glNormal3f(0.0f, 1.0f, 0.0f);
	        glVertex3f(vertices[m_segmentsY][tmp][0], 
	                   vertices[m_segmentsY][tmp][1], 
	                   vertices[m_segmentsY][tmp][2]);
	  
	    } 
	    glEnd(); 
	};

	void drawNormal() {
	    if ((m_segmentsY != vertices.size() - 1) || (m_segmentsX != vertices[0].size()))
	        calV_N();
	    
	    glBegin(GL_LINES);
	    glColor3f(1.0f, 0.0f, 0.0f);
	    for (int i = 0; i <= m_segmentsY; i++) {
	         
	        for (int j = 0; j < m_segmentsX; j++) {
	            
	            Vector tmp = vertices[i][j] + normal[j]/10;
	            glVertex3f(vertices[i][j][0], vertices[i][j][1], vertices[i][j][2]);
	            glVertex3f(tmp[0], tmp[1], tmp[2]);
	                    
	        }
	    }
	    Vector tmp1, tmp2, tmp3, bcenter, tcenter;
	    int top = vertices.size() - 1;
	    tmp1[0] = 0;
	    tmp1[1] = -0.1;
	    tmp1[2] = 0;
	    
	    tmp2[0] = 0;
	    tmp2[1] = 0.1;
	    tmp2[2] = 0;
	    
	    bcenter[0] = 0;
	    bcenter[1] = -0.5;
	    bcenter[2] = 0;
	    
	    tcenter[0] = 0;
	    tcenter[1] = 0.5;
	    tcenter[2] = 0;
	    
	    bcenter = bcenter + tmp1;
	    tcenter = tcenter + tmp2;
	    
	    for (int j = 0; j < m_segmentsX; j++) {
	            
	            tmp3 = vertices[0][j] + tmp1;
	            glVertex3f(vertices[0][j][0], vertices[0][j][1], vertices[0][j][2]);
	            glVertex3f(tmp3[0], tmp3[1], tmp3[2]);
	            
	            tmp3 = vertices[top][j] + tmp2;
	            glVertex3f(vertices[top][j][0], vertices[top][j][1], vertices[top][j][2]);
	            glVertex3f(tmp3[0], tmp3[1], tmp3[2]);       
	    }
	    glVertex3f(0, -0.5, 0);
	    glVertex3f(bcenter[0], bcenter[1], bcenter[2]);
	    glVertex3f(0, 0.5, 0);
	    glVertex3f(tcenter[0], tcenter[1], tcenter[2]);
	    
	    glEnd();
	};
	
private:
    void calV_N() {
    
        Vector cur;
        std::vector<Vector> row;
        double unitdegree= 2*PI/m_segmentsX;
        double yunit = 1.0f/m_segmentsY;
        double y_coor = -0.5f;
        vertices.clear();
        normal.clear();
        for (int i = 0; i <= m_segmentsY; i++) {
	        for (int j = 0; j < m_segmentsX; j++) {
	            cur[0] = 0.5 * cos(j * unitdegree);
	            cur[1] = y_coor;
	            cur[2] = 0.5 * sin(j * unitdegree);
	            row.push_back(cur);   
	        }
	        y_coor += yunit;
	        vertices.push_back(row);
	        row.clear();
	    }
	    

	    for (int i = 0; i < m_segmentsX; i++) {
	    
	        cur[0] = cos(i * unitdegree);
	        cur[1] = 0;  
	        cur[2] = sin(i * unitdegree);
	        normal.push_back(cur);
	    }
    
    };
    
    std::vector<std::vector<Vector> > vertices;
    std::vector<Vector> normal; 
};
#endif
