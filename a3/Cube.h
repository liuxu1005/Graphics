#ifndef CUBE_H
#define CUBE_H

#include "Shape.h"
#include <iostream>

class Cube : public Shape {
public:
	Cube() {};
	~Cube() {};

	void draw() {
	
	    if ((m_segmentsX != sides.size() - 1) 
	        || (m_segmentsY != top.size() - 1))
	        calV_N();
	    glBegin(GL_TRIANGLES);
	    //draw sides
	    for ( int z = 0; z < m_segmentsX; z++) {
	        int len = m_segmentsX;
	        int i = 0;
	        int nextl = z + 1;
	        int nextv;
	        for (; i < len; i++) {
	            nextv = i + 1;
	            glNormal3f(normal_ba[0], normal_ba[1], normal_ba[2]);
	            glVertex3f(sides[z][i][0], sides[z][i][1], sides[z][i][2]);
	            glNormal3f(normal_ba[0], normal_ba[1], normal_ba[2]);
	            glVertex3f(sides[z][nextv][0], 
	                       sides[z][nextv][1], 
	                       sides[z][nextv][2]);
	            glNormal3f(normal_ba[0], normal_ba[1], normal_ba[2]);
	            glVertex3f(sides[nextl][i][0], 
	                       sides[nextl][i][1], 
	                       sides[nextl][i][2]);
	            glNormal3f(normal_ba[0], normal_ba[1], normal_ba[2]);
	            glVertex3f(sides[z][nextv][0], 
	                       sides[z][nextv][1], 
	                       sides[z][nextv][2]);
	            glNormal3f(normal_ba[0], normal_ba[1], normal_ba[2]);
	            glVertex3f(sides[nextl][nextv][0], 
	                       sides[nextl][nextv][1], 
	                       sides[nextl][nextv][2]);
	            glNormal3f(normal_ba[0], normal_ba[1], normal_ba[2]);
	            glVertex3f(sides[nextl][i][0], 
	                       sides[nextl][i][1], 
	                       sides[nextl][i][2]);
	        }
	        len += (1 + m_segmentsY);
	        i++;
	        for (; i < len; i++) {
	            nextv = i + 1;
	            glNormal3f(normal_r[0], normal_r[1], normal_r[2]); 
	            glVertex3f(sides[z][i][0], sides[z][i][1], sides[z][i][2]);
	            glNormal3f(normal_r[0], normal_r[1], normal_r[2]);
	            glVertex3f(sides[z][nextv][0], 
	                       sides[z][nextv][1], 
	                       sides[z][nextv][2]);
	            glNormal3f(normal_r[0], normal_r[1], normal_r[2]);
	            glVertex3f(sides[nextl][i][0], 
	                       sides[nextl][i][1],
	                       sides[nextl][i][2]);
	            glNormal3f(normal_r[0], normal_r[1], normal_r[2]);
	            glVertex3f(sides[z][nextv][0], 
	                       sides[z][nextv][1],
	                       sides[z][nextv][2]);
	            glNormal3f(normal_r[0], normal_r[1], normal_r[2]);
	            glVertex3f(sides[nextl][nextv][0], 
	                       sides[nextl][nextv][1], 
	                       sides[nextl][nextv][2]);
	            glNormal3f(normal_r[0], normal_r[1], normal_r[2]);
	            glVertex3f(sides[nextl][i][0], 
	                       sides[nextl][i][1], 
	                       sides[nextl][i][2]);
	        }
	        len +=(1 + m_segmentsX);
	        i++;
	        for (; i < len; i++) {
	            nextv = i + 1;
	            glNormal3f(normal_f[0], normal_f[1], normal_f[2]);
	            glVertex3f(sides[z][i][0], sides[z][i][1], sides[z][i][2]);
	            glNormal3f(normal_f[0], normal_f[1], normal_f[2]);
	            glVertex3f(sides[z][nextv][0], 
	                       sides[z][nextv][1], 
	                       sides[z][nextv][2]);
	            glNormal3f(normal_f[0], normal_f[1], normal_f[2]);
	            glVertex3f(sides[nextl][i][0], 
	                       sides[nextl][i][1], 
	                       sides[nextl][i][2]);
	            glNormal3f(normal_f[0], normal_f[1], normal_f[2]);
	            glVertex3f(sides[z][nextv][0], 
	                       sides[z][nextv][1], 
	                       sides[z][nextv][2]);
	            glNormal3f(normal_f[0], normal_f[1], normal_f[2]);
	            glVertex3f(sides[nextl][nextv][0], 
	                       sides[nextl][nextv][1], 
	                       sides[nextl][nextv][2]);
	            glNormal3f(normal_f[0], normal_f[1], normal_f[2]);
	            glVertex3f(sides[nextl][i][0], 
	                       sides[nextl][i][1], 
	                       sides[nextl][i][2]);
	        }
	        len += (1 + m_segmentsY);
	        i++;
	        for (; i < len; i++) {
	            nextv = i + 1;
	            glNormal3f(normal_l[0], normal_l[1], normal_l[2]);
	            glVertex3f(sides[z][i][0], sides[z][i][1], sides[z][i][2]);
	            glNormal3f(normal_l[0], normal_l[1], normal_l[2]);
	            glVertex3f(sides[z][nextv][0], 
	                       sides[z][nextv][1], 
	                       sides[z][nextv][2]);
	            glNormal3f(normal_l[0], normal_l[1], normal_l[2]);
	            glVertex3f(sides[nextl][i][0], 
	                       sides[nextl][i][1], 
	                       sides[nextl][i][2]);
	            glNormal3f(normal_l[0], normal_l[1], normal_l[2]);
	            glVertex3f(sides[z][nextv][0], 
	                       sides[z][nextv][1], 
	                       sides[z][nextv][2]);
	            glNormal3f(normal_l[0], normal_l[1], normal_l[2]);
	            glVertex3f(sides[nextl][nextv][0], 
	                       sides[nextl][nextv][1], 
	                       sides[nextl][nextv][2]);
	            glNormal3f(normal_l[0], normal_l[1], normal_l[2]);
	            glVertex3f(sides[nextl][i][0], 
	                       sides[nextl][i][1], 
	                       sides[nextl][i][2]);
	        }
	        
	    
	    }
	    //draw top and bottom
	    for (int i = 0; i < m_segmentsY; i++) {
	        int nextl = i + 1;
	        for (int j = 0; j < m_segmentsX; j++) {
	            int nextv = j + 1;
	            //draw top
	            glNormal3f(normal_t[0], normal_t[1], normal_t[2]);
	            glVertex3f(top[i][j][0], top[i][j][1], top[i][j][2]);
	            glNormal3f(normal_t[0], normal_t[1], normal_t[2]);
	            glVertex3f(top[i][nextv][0], 
	                       top[i][nextv][1], 
	                       top[i][nextv][2]); 
	            glNormal3f(normal_t[0], normal_t[1], normal_t[2]);
	            glVertex3f(top[nextl][j][0], 
	                       top[nextl][j][1], 
	                       top[nextl][j][2]);
	            glNormal3f(normal_t[0], normal_t[1], normal_t[2]);
	            glVertex3f(top[i][nextv][0], top[i][nextv][1], top[i][nextv][2]);
	            glNormal3f(normal_t[0], normal_t[1], normal_t[2]);
	            glVertex3f(top[nextl][nextv][0], 
	                       top[nextl][nextv][1], 
	                       top[nextl][nextv][2]);
	            glNormal3f(normal_t[0], normal_t[1], normal_t[2]);
	            glVertex3f(top[nextl][j][0], top[nextl][j][1], top[nextl][j][2]);
	            //draw bottom
	            glNormal3f(normal_b[0], normal_b[1], normal_b[2]);
	            glVertex3f(bottom[i][j][0], bottom[i][j][1], bottom[i][j][2]);
	            glNormal3f(normal_b[0], normal_b[1], normal_b[2]);
	            glVertex3f(bottom[i][nextv][0], 
	                       bottom[i][nextv][1], 
	                       bottom[i][nextv][2]);
	            glNormal3f(normal_b[0], normal_b[1], normal_b[2]); 
	            glVertex3f(bottom[nextl][j][0], 
	                       bottom[nextl][j][1], 
	                       bottom[nextl][j][2]);
	            glNormal3f(normal_b[0], normal_b[1], normal_b[2]);
	            glVertex3f(bottom[i][nextv][0], 
	                       bottom[i][nextv][1], 
	                       bottom[i][nextv][2]);
	            glNormal3f(normal_b[0], normal_b[1], normal_b[2]);
	            glVertex3f(bottom[nextl][nextv][0], 
	                       bottom[nextl][nextv][1], 
	                       bottom[nextl][nextv][2]);
	            glNormal3f(normal_b[0], normal_b[1], normal_b[2]);
	            glVertex3f(bottom[nextl][j][0], 
	                       bottom[nextl][j][1], 
	                       bottom[nextl][j][2]);
	        }
	        
	    }
	    
	    glEnd(); 
	    
	};


	void drawNormal() {
	    if ((m_segmentsX != sides.size() - 1) 
	        || (m_segmentsY != top.size() - 1))
	        calV_N();
	    glBegin(GL_LINES);
	    //draw sides normal
	    glColor3f(1.0f, 0.0f, 0.0f);
	    Vector tmp;
	    for ( int z = 0; z <= m_segmentsX; z++) {
	        int len = m_segmentsX;
	        int i = 0;
	        for (; i <= len; i++) {
	            tmp = sides[z][i] + normal_ba/20;
	            glVertex3f(sides[z][i][0], sides[z][i][1], sides[z][i][2]);
	            glVertex3f(tmp[0], tmp[1], tmp[2]);
	        }
	        len += (1 + m_segmentsY);
	     
	        for (; i <= len; i++) {
	            tmp = sides[z][i] + normal_r/20;
	            glVertex3f(sides[z][i][0], sides[z][i][1], sides[z][i][2]);
	            glVertex3f(tmp[0], tmp[1], tmp[2]);
	        }
	        len +=(1 + m_segmentsX);
	       
	        for (; i <= len; i++) {
	            tmp = sides[z][i] + normal_f/20;
	            glVertex3f(sides[z][i][0], sides[z][i][1], sides[z][i][2]);
	            glVertex3f(tmp[0], tmp[1], tmp[2]);
	        }
	        len += (1 + m_segmentsY);
	        
	        for (; i <= len; i++) {
	            tmp = sides[z][i] + normal_l/20;
	            glVertex3f(sides[z][i][0], sides[z][i][1], sides[z][i][2]);
	            glVertex3f(tmp[0], tmp[1], tmp[2]);
	        }  
	    
	    }
	    //draw top normal
	    for (int y = 0; y <= m_segmentsY; y++) {
            for (int x = 0; x <= m_segmentsX; x++) {
                tmp = top[y][x] + normal_t/20;
                glVertex3f(top[y][x][0], top[y][x][1], top[y][x][2]);
	            glVertex3f(tmp[0], tmp[1], tmp[2]);
            }
             
        }
        //draw top normal
	    for (int y = 0; y <= m_segmentsY; y++) {
            for (int x = 0; x <= m_segmentsX; x++) {
                tmp = bottom[y][x] + normal_b/20;
                glVertex3f(bottom[y][x][0], bottom[y][x][1], bottom[y][x][2]);
	            glVertex3f(tmp[0], tmp[1], tmp[2]);
            }
             
        }
	    glEnd();
	};
	
private:	
    void calV_N() {
        Vector cur;
        std::vector<Vector> row;
        float yunit = 1.0f/m_segmentsY;
        float zunit = 1.0f/m_segmentsX;
        float xunit = 1.0f/m_segmentsX;
        float z_coor = -0.5f;
        sides.clear();
        top.clear();
        bottom.clear();
        for (int z = 0; z <= m_segmentsX; z++) {
            float tmp = -0.5f;
            for (int x = 0; x <= m_segmentsX; x++) {
                cur[0] = tmp; 
                cur[1] = -0.5f;
                cur[2] = z_coor;
                row.push_back(cur);
                tmp += xunit;
            }
            tmp = -0.5f;
            for (int y = 0; y <= m_segmentsY; y++) {
                cur[0] = 0.5f; 
                cur[1] = tmp;
                cur[2] = z_coor;
                row.push_back(cur);
                tmp += yunit;
            }
            tmp = 0.5f;
            for (int x = 0; x <= m_segmentsX; x++) {
                cur[0] = tmp; 
                cur[1] = 0.5f;
                cur[2] = z_coor;
                row.push_back(cur);
                tmp -= xunit;
            }
            tmp = 0.5f;
            for (int y = 0; y <= m_segmentsY; y++) {
                cur[0] = -0.5f; 
                cur[1] = tmp;
                cur[2] = z_coor;
                row.push_back(cur);
                tmp -= yunit;
            }
            sides.push_back(row);
            row.clear();
            z_coor += zunit;
        }
        
        
        //calculate vertices on top
       
        float x_coor;
        float y_coor = -0.5f;
        for (int y = 0; y <= m_segmentsY; y++) {
            x_coor = -0.5f;
            for (int x = 0; x <= m_segmentsX; x++) {
                cur[0] = x_coor; 
                cur[1] = y_coor;
                cur[2] = 0.5f;
                row.push_back(cur);
                x_coor += xunit;
            }
            y_coor += yunit;
            top.push_back(row);
            row.clear();
        }
        //calculate vertices on bottom
         
        
        y_coor = 0.5f;
        for (int y = 0; y <= m_segmentsY; y++) {
            x_coor = -0.5f;
            for (int x = 0; x <= m_segmentsX; x++) {
                cur[0] = x_coor; 
                cur[1] = y_coor;
                cur[2] = -0.5f;
                row.push_back(cur);
                x_coor += xunit;
            }
            y_coor -= yunit;
            bottom.push_back(row);
            row.clear();
        }
        
        /*****draw normals****************/
        //front face normal
        normal_f[0] = 0.0f;
	    normal_f[1] = 1.0f;
	    normal_f[2] = 0.0f;
	    //back face normal
	    normal_ba[0] = 0.0f;
	    normal_ba[1] = -1.0f;
	    normal_ba[2] = 0.0f;
        //left face normal
	    normal_l[0] = -1.0f;
	    normal_l[1] = 0.0f;
	    normal_l[2] = 0.0f;
	    //right face normal
	    normal_r[0] = 1.0f;
	    normal_r[1] = 0.0f;
	    normal_r[2] = 0.0f;
	    //top face normal
	    normal_t[0] = 0.0f;
	    normal_t[1] = 0.0f;
	    normal_t[2] = 1.0f;
	    //bottom face normal
	    normal_b[0] = 0.0f;
	    normal_b[1] = 0.0f;
	    normal_b[2] = -1.0f;
	    
	     
    };
  
    
    std::vector<std::vector<Vector> > sides;
    std::vector<std::vector<Vector> > top;
    std::vector<std::vector<Vector> > bottom;
     
    Vector normal_f;
    Vector normal_ba;
    Vector normal_l; 
    Vector normal_r; 
    Vector normal_t; 
    Vector normal_b; 
};

#endif
