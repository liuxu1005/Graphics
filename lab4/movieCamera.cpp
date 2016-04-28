/*  =================== File Information =================
  File Name: movieCamera.cpp
  Description:
  Author: 

  Purpose:
  Examples:


Relevant keywords and OpenGL calls to (understand/complete/create cool effects) for this lab:
-glFrustrum
-glDepthRange
-glMultMatrixf
-glTranslate/glRotate/glScale
-glOrtho
-OpenGL field of view


  ===================================================== */
#include <math.h>
#include "movieCamera.h"

// Static initializers
float movieCamera::rotate_around = 0;


	/*  ===============================================
	      Desc: Default Constructor
	      Precondition: Setup your matrix to the identity
	      Postcondition:
    	=============================================== */ 
movieCamera::movieCamera(){
	}

	/*  ===============================================
	      Desc: Default Destructor
	      Precondition:
	      Postcondition:
    	=============================================== */ 
movieCamera::~movieCamera(){

}

/*
	Implement the clipping plane
*/
/*  ===============================================
      Desc: Zoom in on an object.  Optionally clip out objects that are 'far' away from this object
      Precondition:
      Postcondition:
	=============================================== */ 
void movieCamera::closeUp(float your_x, float your_y, float your_z, float near, float far){
    //glDepthRange( near, far);
    gluLookAt(0, 3,  0, your_x, your_y, your_z, 0 ,1 ,0);
    glMatrixMode(GL_PROJECTION);   
    glLoadIdentity();
    glFrustum( -0.7, 0.7, -0.7, 0.7, near, far*3);
    
    glMatrixMode(GL_MODELVIEW);
}

/*
	Change the field of view
*/
/*  ===============================================
      Desc: Change the viewing angle of the camera lense
      Precondition:
      Postcondition:
	=============================================== */ 
void movieCamera::wideAngle(float _fov){

}

/*
	Set the camera to an orthogonal view
*/
/*  ===============================================
  Desc: Remove the depth attribute from the camera.
  Precondition:
  Postcondition:
=============================================== */ 
void movieCamera::orthogonal(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble nearVal, GLdouble farVal){
    float s = 4;
   
    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();
    glOrtho(left*s, right*s, bottom*s, top*s, nearVal, farVal);
    
    glMatrixMode(GL_MODELVIEW);
    
}

/*  ===============================================
      Desc: Render the scene in a normal perspective field of view.
            The parameters for this function match that of the OpenGL Utility library.
      Precondition:
      Postcondition:
	=============================================== */ 
void movieCamera::perspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar){

}
/*  ===============================================
      Desc: Set the camera to a 'look at' a target from a specified position and follow it.
            your_x would be your position, and the target could be a moving or non-moving target
      Precondition:
      Postcondition:
	=============================================== */ 
void movieCamera::follow(float your_x, float your_y, float your_z,
						float target_x, float target_y, float target_z,
						float up_x, float up_y, float up_z){
	gluLookAt(your_x - 3, your_y + 3, your_z + 2, your_x, your_y + 2, your_z, up_x, 1 , up_z);
   
						
}
/*  ===============================================
      Desc: Spin around a point in space at a distance(i.e. "radius")
      Precondition:
      Postcondition:
	=============================================== */ 
void movieCamera::spinAroundPoint(float your_x, float your_y, float your_z, float distance){
	rotate_around += 1;

	/* Your code here */
	gluLookAt(your_x + 5.2* distance * cos(-180 - rotate_around*3.14 /180), your_y + 4, your_z + 5.2*distance * sin(-180 - rotate_around*3.14 /180), your_x, your_y + 2, your_z, 0, 1 , 0);

	if(rotate_around>360){ rotate_around = 0; }
}
