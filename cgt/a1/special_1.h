#ifndef SPECIAL_H
#define SPECIAL_H

#include "Shape.h"

class Special : public Shape {
public:
	Special() {};
	~Special() {};

	void draw() {
	
	    if ((m_segmentsY != vertices.size() - 1) || (m_segmentsX != vertices[0].size()))
	        calV_N();
	        
	    glBegin(GL_TRIANGLES);
	    for (int i = 0; i < m_segmentsY; i++) {
	        int nextl = i + 1;
	        for (int j = 0; j < m_segmentsX; j++) {
	            
	            int nextv = (j + 1) % m_segmentsX; 
	            //glNormal3f(normal[j][0], normal[j][1], normal[j][2]);
	            glVertex3f(vertices[i][j][0], 
	                       vertices[i][j][1], 
	                       vertices[i][j][2]);
	            //glNormal3f(normal[j][0], normal[j][1], normal[j][2]);
	            glVertex3f(vertices[nextl][j][0], 
	                       vertices[nextl][j][1], 
	                       vertices[nextl][j][2]);
	            //glNormal3f(normal[nextv][0], normal[nextv][1], normal[nextv][2]);
	            glVertex3f(vertices[nextl][nextv][0], 
	                       vertices[nextl][nextv][1], 
	                       vertices[nextl][nextv][2]);
	            
	           // glNormal3f(normal[j][0], normal[j][1], normal[j][2]);
	            glVertex3f(vertices[i][j][0], 
	                       vertices[i][j][1], 
	                       vertices[i][j][2]);
	            //glNormal3f(normal[nextv][0], normal[nextv][1], normal[nextv][2]); 
	            glVertex3f(vertices[nextl][nextv][0], 
	                       vertices[nextl][nextv][1], 
	                       vertices[nextl][nextv][2]);
	            glNormal3f(normal[nextv][0], normal[nextv][1], normal[nextv][2]); 
	            glVertex3f(vertices[i][nextv][0], 
	                       vertices[i][nextv][1], 
	                       vertices[i][nextv][2]);
	        }
	  
	    } 
	  /*  for (int i = 0; i < m_segmentsX; i++) {
	        int tmp = (i + 1)%m_segmentsX;
	            
	        glNormal3f(0.0f, -1.0f, 0.0f);
	        glVertex3f(vertices[0][i][0], vertices[0][i][1], vertices[0][i][2]);
	        glNormal3f(0.0f, -1.0f, 0.0f);
	        glVertex3f(centers[0][0], -0.5f, centers[0][2]);
	        glNormal3f(0.0f, -1.0f, 0.0f);
	        glVertex3f(vertices[0][tmp][0], 
	        vertices[0][tmp][1], vertices[0][tmp][2]);
	         
	        //glNormal3f(0.0f, 1.0f, 0.0f);
	        glVertex3f(vertices[m_segmentsY][i][0], 
	                   vertices[m_segmentsY][i][1], 
	                   vertices[m_segmentsY][i][2]);
	        //glNormal3f(0.0f, 1.0f, 0.0f);
	        glVertex3f(centers[centers.size() - 1][0], 0.5f, centers[centers.size()-1][2]);
	        //glNormal3f(0.0f, 1.0f, 0.0f);
	        glVertex3f(vertices[m_segmentsY][tmp][0], 
	                   vertices[m_segmentsY][tmp][1], 
	                   vertices[m_segmentsY][tmp][2]);
	  
	    } */
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
	    glEnd();
	};
	
private:
    void calV_N() {
    
        Vector cur;
        std::vector<Vector> row;
        float unitdegree= 2*PI/m_segmentsX;
        float yunitdegree = PI/m_segmentsY;
        float yunit = 1.0f/m_segmentsY;
        float y_coor = -0.5f;
        
        float beta = -PI;
        vertices.clear();
        normal.clear();
        centers.clear();
        
        //calculate centers;
        for (int i = 0; i <= m_segmentsY; i++) {
            cur[0] = sin(beta) * cos(i * yunitdegree);
            cur[1] = cos(beta);
            cur[2] = sin(beta) * sin(i * yunitdegree);
            centers.push_back(cur);
            beta += yunitdegree;
        }
        beta = -PI;
        //calculate vertices
        for (int i = 0; i <= m_segmentsY; i++) {
            
	        for (int j = 0; j < m_segmentsX; j++) {
	            cur[0] = 0.25* fabs(cos(PI/2 + beta) * cos(j * unitdegree)) * cos(i * yunitdegree) + centers[i][0];
	            cur[1] = centers[i][1] + 0.25 * fabs(cos(j * unitdegree)) * cos(i * yunitdegree);
	            cur[2] = 0.25 * fabs(sin(j * unitdegree) *cos(PI/2 + beta))*sin(i * yunitdegree) + centers[i][2];
	            row.push_back(cur);   
	        }
	        y_coor += yunit;
	        beta += yunitdegree;
	        vertices.push_back(row);
	        row.clear();   
	    }
	    
        //calculate normals
	    for (int i = 0; i < m_segmentsX; i++) {
	    
	        cur[0] = cos(i * unitdegree);
	        cur[1] = 0;  
	        cur[2] = sin(i * unitdegree);
	        normal.push_back(cur);
	    }
    
    };
    
    std::vector<std::vector<Vector> > vertices;
    std::vector<Vector> normal; 
    std::vector<Vector> centers;
};
#endif
