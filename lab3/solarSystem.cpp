#include <GL/glui.h>
#include "solarSystem.h"

solarSystem::solarSystem(){

}

solarSystem::~solarSystem(){

}

// Render this with push and pop operations
// or alternatively implement helper functions
// for each of the planets with parameters.
void solarSystem::render(){
	
	// Some ideas for constants that can be used for
	// rotating the planets.
	static float rotation = 0.1;
	static float orbitX = 0.15;
	static float orbitSpeed = 0.2;
	static float moonOrbitX = 0.1;
	static float moonOrbitY = 0.1;
	static float moonOrbitSpeed = 1;

	// The Sun
	    //glLoadIdentity();
		glPushMatrix();
			glRotatef(rotation,0,1,0);
			glColor3f(0.96f,0.85f,0.26f);
			glutSolidSphere(1.2,10,10);
			// planet 1
			glPushMatrix();
			    glTranslatef(2, 0, 0); 
			    //glRotatef(orbitX * 1.3,0,1,0);
			    glColor3f(0.66f,0.85f,0.26f);
			    glutSolidSphere(0.2,3,10);
			    //moon 1
			    glPushMatrix();
			        glRotatef(moonOrbitX * 1.1,0,3,1);
			        glTranslatef(0.2, 0.2, 0);
			        glColor3f(0.66f,0.05f,0.26f);
			        glutSolidSphere(0.05,10,10);
			
		        glPopMatrix();
			
		    glPopMatrix();
		    //planet 2
		    glPushMatrix();
			    glRotatef(orbitX * 1.1,0,1,0);
			    glTranslatef(3, 0, 0); 
			    
			    glColor3f(0.66f,0.85f,0.65f);
			    glutSolidSphere(0.3,10,10);
			    
			    glPushMatrix();
			        glRotatef(moonOrbitX * 1.1,0,1,0);
			        glTranslatef(0.3, 0.6, 0);
			        glColor3f(0.66f,0.15f,0.26f);
			        glutSolidSphere(0.05,10,10);
			
		        glPopMatrix();
			
		    glPopMatrix();
		    //planet 3
		    glPushMatrix();
			    glRotatef(orbitX * 1.3,0,1,0);
			    glTranslatef(4, 0, 0); 
			    
			    glColor3f(0.36f,0.95f,0.25f);
			    glutSolidSphere(0.3,10,10);
			    //moon 3
			    glPushMatrix();
			        glRotatef(moonOrbitX * 1.1,3,1,3);
			        glTranslatef(0.3, 0.2, 0);
			        glColor3f(0.36f,0.45f,0.26f);
			        glutSolidSphere(0.1,10,10);
			
		        glPopMatrix();
			
		    glPopMatrix();
		    
		    glPushMatrix();
			    glRotatef(orbitX * 1.1,0,1,0);
			    glTranslatef(5, 0, 0); 
			    
			    glColor3f(0.9f,0.2f,0.65f);
			    glutSolidSphere(0.3,10,10);
			    
			    glPushMatrix();
			        glRotatef(moonOrbitX,0,0,3);
			        glTranslatef(0.3, 0.3, 0);
			        glColor3f(0.66f,0.15f,0.26f);
			        glutSolidSphere(0.1 ,10,10);
			
		        glPopMatrix();
			
		    glPopMatrix();
		    
		    glPushMatrix();
			    glRotatef(orbitX * 1.1,0,1,0);
			    glTranslatef(7, 0, 0); 
			    
			    glColor3f(0.76f,0.75f,0.05f);
			    glutSolidSphere(0.3,10,10);
			    
			    glPushMatrix();
			        glRotatef(moonOrbitX ,0,4,3);
			        glTranslatef(0.5, 0.3, 0);
			        glColor3f(0.06f,0.55f,0.26f);
			        glutSolidSphere(0.2,10,10);
			
		        glPopMatrix();
			
		    glPopMatrix();
		    
		    glPushMatrix();
			    glRotatef(-orbitX * 1.1,0,1,0);
			    glTranslatef(9, 0, 0); 
			    
			    glColor3f(0.76f,0.05f,0.05f);
			    glutSolidSphere(0.3,10,10);
			    
			    glPushMatrix();
			        glRotatef(moonOrbitX ,0,4,3);
			        glTranslatef(0.5, 0.3, 0);
			        glColor3f(0.06f,0.95f,0.26f);
			        glutSolidSphere(0.1,10,10);
			
		        glPopMatrix();
			
		    glPopMatrix();
			
		glPopMatrix();
	// Add more planets, moons, and rings here!	
    

	
 
    rotation+= 0.01;
	orbitX+= orbitSpeed;
	moonOrbitX+= moonOrbitSpeed;
	moonOrbitY+= moonOrbitSpeed;
}

 