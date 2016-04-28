#define NUM_OPENGL_LIGHTS 8

#include <iostream>
#include <fstream>
#include <string>
#include <GL/glui.h>
#include "Shape.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Cone.h"
#include "Sphere.h"
#include "SceneParser.h"
#include "Camera.h"
#include <vector>
#include "Algebra.h"
#include "math.h"

using namespace std;

double calDistance(Point eye, Vector ray, Matrix transform, enum PrimitiveType type);
void calColor(double row, double col, int *r, int *g, int *b);
Vector calNormal(Point eyeP, Vector ray, double dist, enum PrimitiveType type);
void flattenHelper(SceneNode *mynode, Matrix& transform);
void flattenParserTree();

/** These are the live variables passed into GLUI ***/
int  isectOnly = 1;

int	 camRotU = 0;
int	 camRotV = 0;
int	 camRotW = 0;
int  viewAngle = 45;
float eyeX = 2;
float eyeY = 2;
float eyeZ = 2;
float lookX = -2;
float lookY = -2;
float lookZ = -2;

/** These are GLUI control panel objects ***/
int  main_window;
string filenamePath = "data/general/test.xml";
GLUI_EditText* filenameTextField = NULL;
GLubyte* pixels = NULL;
int pixelWidth = 0, pixelHeight = 0;
int screenWidth = 0, screenHeight = 0;

/** these are the global variables used for rendering **/
Cube* cube = new Cube();
Cylinder* cylinder = new Cylinder();
Cone* cone = new Cone();
Sphere* sphere = new Sphere();
SceneParser* parser = NULL;
Camera* camera = new Camera();
 
struct mysn {
    Matrix transform;
    enum PrimitiveType obj;
    class SceneMaterial m;

};
std::vector<struct mysn> sceneNodes;
std::vector<class SceneLightData> lights;
SceneGlobalData globalData;
    

void setupCamera();
void updateCamera();

void setPixel(GLubyte* buf, int x, int y, int r, int g, int b) {
	buf[(y*pixelWidth + x) * 3 + 0] = (GLubyte)r;
	buf[(y*pixelWidth + x) * 3 + 1] = (GLubyte)g;
	buf[(y*pixelWidth + x) * 3 + 2] = (GLubyte)b;
}

void callback_start(int id) {
	cout << "start button clicked!" << endl;

	if (parser == NULL) {
		cout << "no scene loaded yet" << endl;
		return;
	}
	
	

	pixelWidth = screenWidth;
	pixelHeight = screenHeight;

	updateCamera();

	if (pixels != NULL) {
		delete pixels;
	}
	pixels = new GLubyte[pixelWidth  * pixelHeight * 3];
	memset(pixels, 0, pixelWidth  * pixelHeight * 3);

	cout << "(w, h): " << pixelWidth << ", " << pixelHeight << endl;

	for (int i = 0; i < pixelWidth; i++) {
		for (int j = 0; j < pixelHeight; j++) {
			//replace the following code
			int r, g, b;
		    calColor((float)i * 2/pixelWidth - 1, 
		             (float)j * 2/pixelHeight - 1, &r, &g, &b);	 
		  
		    setPixel(pixels, i, j, r, g, b);
			 
		}
	}
	glutPostRedisplay();
}

void calColor(double row, double col, int *r, int *g, int *b) {
    int target = 0;
    double dist = -1;
    bool found = false;
    const Point e(eyeX, eyeY, eyeZ);
    Point tmplookat(row, col, -1);
    const Point lookat = invert(camera->GetModelViewMatrix()) * tmplookat;
    Vector look = lookat - e;
    look.normalize();
    int size = sceneNodes.size();
    
    for (int j = 0; j < size; j++) {

        double tmpdist = calDistance(e, look, 
                                    sceneNodes[j].transform, sceneNodes[j].obj);
    
        if (tmpdist < 0 ) continue;

        if(!found) {
          
            target = j;
            dist = tmpdist;
            found = true;
            continue;
        }
        
        if (dist > tmpdist) {
            target = j;
            dist = tmpdist;
        }     
         
    } 
     
    //
    if (found) {
    
        Matrix t = invert(sceneNodes[target].transform);
        Point tmpe = t * e;        
        
        Point intersection = e + dist * look;
        Vector tmpv = t * look;
     
        Vector nor = calNormal(tmpe,  tmpv, dist, sceneNodes[target].obj );
      
        nor = transpose(invert(sceneNodes[target].transform)) * nor;
        nor.normalize();
        int lnum = lights.size();
       
        float lr = 0;
        float lg = 0;
        float lb = 0;
        float sr = 0;
        float sg = 0;
        float sb = 0;
        for (int i = 0; i < lnum; i++) {
            //only consider point light
            //if (lights[i].type != LIGHT_POINT) continue;
            Vector l = lights[i].pos - intersection;
            l.normalize();
            Vector r = 2 * dot(nor, l) * nor  - l;
            r.normalize();
            double tmpproduct = dot(nor, l);
            double tmprproduct = -dot(look, r);
          
            //only consider positive direction
            if (tmpproduct > 0) {
       
                lr += lights[i].color.r * tmpproduct;  
                lg += lights[i].color.g * tmpproduct;
                lb += lights[i].color.b * tmpproduct;
            }
            
            if (tmprproduct > 0) {
                double shininess = tmprproduct;//pow(tmprproduct, sceneNodes[target].m.shininess);
                sr += lights[i].color.r * shininess;  
                sg += lights[i].color.g * shininess;
                sb += lights[i].color.b * shininess; 
              //  std::cout<<"relfective "<< tmprproduct<<"  "<<sceneNodes[target].m.shininess
              //           <<"   " <<shininess<<std::endl;            
            
            } 
            
        }
        if(isectOnly == 1) {   
            *r =  255;
            *g =  255;
            *b =  255; 
        } else {
        
            
            
            //cap all value which is larger than 1.0
            
        
            float tmpr =  (globalData.ka * sceneNodes[target].m.cAmbient.r 
                    + lr * globalData.kd * sceneNodes[target].m.cDiffuse.r
                    + sr * globalData.ks ); 
            float tmpg =  (globalData.ka * sceneNodes[target].m.cAmbient.g 
                   + lg * globalData.kd * sceneNodes[target].m.cDiffuse.g
                   + sg * globalData.ks);
            float tmpb = (globalData.ka * sceneNodes[target].m.cAmbient.b
                   + lb * globalData.kd * sceneNodes[target].m.cDiffuse.b
                   + sb * globalData.ks ); 
           
            *r = tmpr * 100;
            *g = tmpg * 100;
            *b = tmpb * 100;
           /*
           
               
            if (tmpr > 1.0) { 
                *r = 255;
            } else {
                *r = tmpr * 255; 
            }
            
            if (tmpg > 1.0) {
                *g = 255;
            } else {
                *g = tmpg * 255 ;
            }
            if (tmpb > 1.0) {
                *b = 255;
            } else {
        
                *b = tmpb * 255 ;
            } */
        }
      
    } else {
       
        *r =  0;
        *g =  0;
        *b =  0; 
    
    } 
    
}

double calDistance(Point eye, Vector ray, Matrix transform, enum PrimitiveType type) {

    switch (type) {
        case SHAPE_CUBE:
            return cube->Intersect(eye, ray, transform);
	
	    case SHAPE_CYLINDER:
	        return cylinder->Intersect(eye, ray, transform);
	        
	    case SHAPE_CONE:
	        return cone->Intersect(eye, ray, transform);
	        
	    case SHAPE_SPHERE:
	        return sphere->Intersect(eye, ray, transform);
	    
	    default:
	        
            return -1;
    }   

}

Vector calNormal(Point eyeP, Vector ray, double dist, enum PrimitiveType type) {
 
    switch (type) {
        case SHAPE_CUBE:
            return cube->findIsectNormal(eyeP, ray, dist);
	
	    case SHAPE_CYLINDER:
	        return cylinder->findIsectNormal(eyeP, ray, dist);
	    
	    case SHAPE_CONE:
	        return cone->findIsectNormal(eyeP, ray, dist);
	        
	    case SHAPE_SPHERE:
	        return sphere->findIsectNormal(eyeP, ray, dist);
	        
	    default:
            return Vector(0, 0, 0);
    
    }  

}

void callback_load(int id) {
	char curDirName [2048];
	if (filenameTextField == NULL) {
		return;
	}
	printf ("%s\n", filenameTextField->get_text());

	if (parser != NULL) {
		delete parser;
	}
	parser = new SceneParser (filenamePath);
	cout << "success? " << parser->parse() << endl;
	
	setupCamera();
	flattenParserTree();
	std::cout<<"nodes "<<sceneNodes.size()<<std::endl;
 
}


/***************************************** myGlutIdle() ***********/


void flattenParserTree() {
    if (parser == NULL)
        return;
    sceneNodes.clear();
    lights.clear();
    //get light data
    int numLights = parser->getNumLights();
	for (int i = 0; i < numLights; i++) {
        SceneLightData lightData;
		parser->getLightData(i, lightData);
		lights.push_back(lightData);
	}
	parser->getGlobalData(globalData);
	//get objects
	Matrix transform;
	flattenHelper(parser->getRootNode(), transform);

}

Matrix calTransform(SceneNode *mynode) {
    Matrix t; 
  
    int size = mynode->transformations.size();
  
    for (int i = 0; i < size; i++) {
        switch (mynode->transformations[i]->type) {
            case TRANSFORMATION_TRANSLATE:          
                t = t * trans_mat(mynode->transformations[i]->translate);
                break;
            case TRANSFORMATION_SCALE:
                t = t * scale_mat(mynode->transformations[i]->scale);
                break;
            case TRANSFORMATION_ROTATE:
                t = t * rot_mat(mynode->transformations[i]->rotate, mynode->transformations[i]->angle);
                break; 
            case TRANSFORMATION_MATRIX:
                t = t * mynode->transformations[i]->matrix;
                break;                       
        
        }   
    }
    return t; 
}

void flattenHelper(SceneNode *mynode, Matrix& transform) {

    if (mynode == NULL)
        return;
    struct mysn tmpNode;
    Matrix tmpTrans = transform * calTransform(mynode);
    tmpNode.transform = tmpTrans;
    
    int size = mynode->primitives.size();

    for (int i = 0; i < size ; i++) {
 
        tmpNode.m  = mynode->primitives[i]->material;
        tmpNode.obj = mynode->primitives[i]->type; 
        sceneNodes.push_back(tmpNode);
        
    }
        
    size = mynode->children.size();
 
    for (int j = 0; j < size; j++ ) {
        flattenHelper(mynode->children[j], tmpTrans);
    }

}

void myGlutIdle(void)
{
	/* According to the GLUT specification, the current window is
	undefined during an idle callback.  So we need to explicitly change
	it if necessary */
	if (glutGetWindow() != main_window)
		glutSetWindow(main_window);

	glutPostRedisplay();
}


/**************************************** myGlutReshape() *************/

void myGlutReshape(int x, int y)
{
	float xy_aspect;

	xy_aspect = (float)x / (float)y;
	glViewport(0, 0, x, y);
	camera->SetScreenSize(x, y);

	screenWidth = x;
	screenHeight = y;

	glutPostRedisplay();
}


/***************************************** setupCamera() *****************/
void setupCamera()
{
	SceneCameraData cameraData;
	parser->getCameraData(cameraData);

	camera->Reset();
	camera->SetViewAngle(cameraData.heightAngle);
	if (cameraData.isDir == true) {
		camera->Orient(cameraData.pos, cameraData.look, cameraData.up);
	}
	else {
		camera->Orient(cameraData.pos, cameraData.lookAt, cameraData.up);
	}

	viewAngle = camera->GetViewAngle();
	Point eyeP = camera->GetEyePoint();
	Vector lookV = camera->GetLookVector();
	eyeX = eyeP[0];
	eyeY = eyeP[1];
	eyeZ = eyeP[2];
	lookX = lookV[0];
	lookY = lookV[1];
	lookZ = lookV[2];
	camRotU = 0;
	camRotV = 0;
	camRotW = 0;
	GLUI_Master.sync_live_all();
}

void updateCamera()
{
	camera->Reset();

	Point guiEye (eyeX, eyeY, eyeZ);
	Point guiLook(lookX, lookY, lookZ);
	camera->SetViewAngle(viewAngle);
	Vector v = camera->GetUpVector(); 
	camera->Orient(guiEye, guiLook, v);
	camera->RotateU(camRotU);
	camera->RotateV(camRotV);
	camera->RotateW(camRotW);
}

/***************************************** myGlutDisplay() *****************/

void myGlutDisplay(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	if (parser == NULL) {
		return;
	}

	if (pixels == NULL) {
		return;
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glDrawPixels(pixelWidth, pixelHeight, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	glutSwapBuffers();
}

void onExit()
{
	delete cube;
	delete cylinder;
	delete cone;
	delete sphere;
	delete camera;
	if (parser != NULL) {
		delete parser;
	}
	if (pixels != NULL) {
		delete pixels;
	}
}

/**************************************** main() ********************/

int main(int argc, char* argv[])
{
	atexit(onExit);

	/****************************************/
	/*   Initialize GLUT and create window  */
	/****************************************/

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(500, 500);

	main_window = glutCreateWindow("COMP 175 Assignment 4");
	glutDisplayFunc(myGlutDisplay);
	glutReshapeFunc(myGlutReshape);

	/****************************************/
	/*         Here's the GLUI code         */
	/****************************************/

	GLUI* glui = GLUI_Master.create_glui("GLUI");

	filenameTextField = new GLUI_EditText( glui, "Filename:", filenamePath);
	filenameTextField->set_w(300);
	glui->add_button("Load", 0, callback_load);
	glui->add_button("Start!", 0, callback_start);
	glui->add_checkbox("Isect Only", &isectOnly);
	
	GLUI_Panel *camera_panel = glui->add_panel("Camera");
	(new GLUI_Spinner(camera_panel, "RotateV:", &camRotV))
		->set_int_limits(-179, 179);
	(new GLUI_Spinner(camera_panel, "RotateU:", &camRotU))
		->set_int_limits(-179, 179);
	(new GLUI_Spinner(camera_panel, "RotateW:", &camRotW))
		->set_int_limits(-179, 179);
	(new GLUI_Spinner(camera_panel, "Angle:", &viewAngle))
		->set_int_limits(1, 179);

	glui->add_column_to_panel(camera_panel, true);

	GLUI_Spinner* eyex_widget = glui->add_spinner_to_panel(camera_panel, "EyeX:", GLUI_SPINNER_FLOAT, &eyeX);
	eyex_widget->set_float_limits(-10, 10);
	GLUI_Spinner* eyey_widget = glui->add_spinner_to_panel(camera_panel, "EyeY:", GLUI_SPINNER_FLOAT, &eyeY);
	eyey_widget->set_float_limits(-10, 10);
	GLUI_Spinner* eyez_widget = glui->add_spinner_to_panel(camera_panel, "EyeZ:", GLUI_SPINNER_FLOAT, &eyeZ);
	eyez_widget->set_float_limits(-10, 10);

	GLUI_Spinner* lookx_widget = glui->add_spinner_to_panel(camera_panel, "LookX:", GLUI_SPINNER_FLOAT, &lookX);
	lookx_widget->set_float_limits(-10, 10);
	GLUI_Spinner* looky_widget = glui->add_spinner_to_panel(camera_panel, "LookY:", GLUI_SPINNER_FLOAT, &lookY);
	looky_widget->set_float_limits(-10, 10);
	GLUI_Spinner* lookz_widget = glui->add_spinner_to_panel(camera_panel, "LookZ:", GLUI_SPINNER_FLOAT, &lookZ);
	lookz_widget->set_float_limits(-10, 10);

	glui->add_button("Quit", 0, (GLUI_Update_CB)exit);

	glui->set_main_gfx_window(main_window);

	/* We register the idle callback with GLUI, *not* with GLUT */
	GLUI_Master.set_glutIdleFunc(myGlutIdle);

	glutMainLoop();

	return EXIT_SUCCESS;
}



