#ifndef SPECIAL_H
#define SPECIAL_H

#include "Shape.h"

class Special : public Shape {
public:
	Special() {};
	~Special() {};

	void draw() {
	
	    if ((m_segmentsY != vertices1.size() - 1) || (m_segmentsX != vertices1[0].size()))
	        calV_N();
	        
	    glBegin(GL_TRIANGLES);
	    for (int i = 0; i < m_segmentsY; i++) {
	        int nextl = i + 1;
	        for (int j = 0; j < m_segmentsX; j++) {
	            
	            int nextv = (j + 1) % m_segmentsX; 
	            glNormal3f(normals1[i][j][0], normals1[i][j][1], normals1[i][j][2]);
	            glVertex3f(vertices1[i][j][0], 
	                       vertices1[i][j][1], 
	                       vertices1[i][j][2]);
	            glNormal3f(normals1[nextl][j][0], normals1[nextl][j][1], normals1[nextl][j][2]);
	            glVertex3f(vertices1[nextl][j][0], 
	                       vertices1[nextl][j][1], 
	                       vertices1[nextl][j][2]);
	            glNormal3f(normals1[nextl][nextv][0], normals1[nextl][nextv][1], normals1[nextl][nextv][2]);
	            glVertex3f(vertices1[nextl][nextv][0], 
	                       vertices1[nextl][nextv][1], 
	                       vertices1[nextl][nextv][2]);
	            
	            glNormal3f(normals1[i][j][0], normals1[i][j][1], normals1[i][j][2]);
	            glVertex3f(vertices1[i][j][0], 
	                       vertices1[i][j][1], 
	                       vertices1[i][j][2]);
	            glNormal3f(normals1[nextl][nextv][0], normals1[nextl][nextv][1], normals1[nextl][nextv][2]);
	            glVertex3f(vertices1[nextl][nextv][0], 
	                       vertices1[nextl][nextv][1], 
	                       vertices1[nextl][nextv][2]);
	            glNormal3f(normals1[i][nextv][0], normals1[i][nextv][1], normals1[i][nextv][2]); 
	            glVertex3f(vertices1[i][nextv][0], 
	                       vertices1[i][nextv][1], 
	                       vertices1[i][nextv][2]);
	                       
	                      
	                       

	            glNormal3f(normals2[i][j][0], normals2[i][j][1], normals2[i][j][2]);
	            glVertex3f(vertices2[i][j][0], 
	                       vertices2[i][j][1], 
	                       vertices2[i][j][2]);
	            glNormal3f(normals2[nextl][j][0], normals2[nextl][j][1], normals2[nextl][j][2]);
	            glVertex3f(vertices2[nextl][j][0], 
	                       vertices2[nextl][j][1], 
	                       vertices2[nextl][j][2]);
	            glNormal3f(normals2[nextl][nextv][0], normals2[nextl][nextv][1], normals2[nextl][nextv][2]);
	            glVertex3f(vertices2[nextl][nextv][0], 
	                       vertices2[nextl][nextv][1], 
	                       vertices2[nextl][nextv][2]);
	            
	            glNormal3f(normals2[i][j][0], normals2[i][j][1], normals2[i][j][2]);
	            glVertex3f(vertices2[i][j][0], 
	                       vertices2[i][j][1], 
	                       vertices2[i][j][2]);
	            glNormal3f(normals2[nextl][nextv][0], normals2[nextl][nextv][1], normals2[nextl][nextv][2]);
	            glVertex3f(vertices2[nextl][nextv][0], 
	                       vertices2[nextl][nextv][1], 
	                       vertices2[nextl][nextv][2]);
	            glNormal3f(normals2[i][nextv][0], normals2[i][nextv][1], normals2[i][nextv][2]); 
	            glVertex3f(vertices2[i][nextv][0], 
	                       vertices2[i][nextv][1], 
	                       vertices2[i][nextv][2]);
	        }
	  
	    } 
	  
	    glEnd(); 
	};

	void drawNormal() {
	    if ((m_segmentsY != vertices1.size() - 1) || (m_segmentsX != vertices1[0].size()))
	        calV_N();
	    Vector tmp;
	    glBegin(GL_LINES);
	    glColor3f(1.0f, 0.0f, 0.0f);
	    for (int i = 0; i <= m_segmentsY; i++) {
	        
	        for (int j = 0; j < m_segmentsX; j++) {
	            
	            glVertex3f(vertices1[i][j][0], 
	                       vertices1[i][j][1], 
	                       vertices1[i][j][2]); 
	            tmp = vertices1[i][j] + normals1[i][j]/15; 
	            glVertex3f(tmp[0], tmp[1], tmp[2]);
	            
	            glVertex3f(vertices2[i][j][0], 
	                       vertices2[i][j][1], 
	                       vertices2[i][j][2]); 
	            tmp = vertices2[i][j] + normals2[i][j]/15; 
	            glVertex3f(tmp[0], tmp[1], tmp[2]);
	            
	        }
	    }
	    glEnd();
	};
	
private:
    void calV_N() {
    
        Vector cur;
        std::vector<Vector> row1, row2, nrow1, nrow2;
        float unitdegree= 2*PI/m_segmentsX;
        float yunitdegree = PI/m_segmentsY;
        float yunit = 1.0f/m_segmentsY;
        float y_coor = -0.5f;
        float r = 1.0f/3.0f;
        float r1 = 1.0f/6.0f;
        
        float beta = -PI;
        vertices1.clear();
        vertices2.clear();
        normals1.clear();
        normals2.clear();
        centers1.clear();
        centers2.clear();
        
        //calculate centers;
        for (int i = 0; i <= m_segmentsY; i++) {
            cur[0] = r * sin(beta) * cos(i * yunitdegree);
            cur[1] = r * cos(beta);
            cur[2] = r * sin(beta) * sin(i * yunitdegree);
            centers1.push_back(cur);
            cur[0] = r * sin(beta) * cos(i * yunitdegree - PI);
            cur[1] = r * cos(beta);
            cur[2] = r * sin(beta) * sin(i * yunitdegree - PI);
            centers2.push_back(cur);
            beta += yunitdegree;
        }
        beta = -PI;
        //calculate vertices
        for (int i = 0; i <= m_segmentsY; i++) {
            
	        for (int j = 0; j < m_segmentsX; j++) {
	        
	            
	            cur[0] = r1 * cos(j * unitdegree) * sin(beta) * cos(i * yunitdegree) 
	                     + r1 * sin(j * unitdegree)*cos(PI/2 + i * yunitdegree);  
	                      
	            cur[1] = r1 * cos(j * unitdegree) * cos(beta);
	            cur[2] = r1 * cos(j * unitdegree) * sin(beta) * sin(i * yunitdegree)
	                     + r1 * sin(j * unitdegree)* sin(PI/2 + i * yunitdegree);
	                     
	            row1.push_back(centers1[i] + cur);
	            cur.normalize();
	            nrow1.push_back(cur); 
	             
	            cur[0] = r1 * cos(j * unitdegree) * sin(beta) * cos(i * yunitdegree -PI) 
	                     + r1 * sin(j * unitdegree)*cos(i * yunitdegree - PI/2);
	            cur[1] = r1 * cos(j * unitdegree) * cos(beta);
	            cur[2] = r1 * cos(j * unitdegree) * sin(beta) * sin(i * yunitdegree - PI)
	                     + r1 * sin(j * unitdegree)* sin(i * yunitdegree - PI/2);
	            
	            row2.push_back(centers2[i] + cur); 
	            cur.normalize();
	            nrow2.push_back(cur);
	        }
	        y_coor += yunit;
	        beta += yunitdegree;
	        vertices1.push_back(row1);
	        vertices2.push_back(row2);
	        normals1.push_back(nrow1);
	        normals2.push_back(nrow2);
	        row1.clear(); 
	        row2.clear(); 
	        nrow1.clear();
	        nrow2.clear(); 
	    }
	  
	    
   
    
    };
    
    std::vector<std::vector<Vector> > vertices1;
    std::vector<std::vector<Vector> > vertices2;
    std::vector<std::vector<Vector> > normals1; 
    std::vector<std::vector<Vector> > normals2; 
    std::vector<Vector> centers1;
    std::vector<Vector> centers2;
    
};
#endif
