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


#define thresh 0.001
#define cap 255
using namespace std;

struct Texture {
	int width;
	int height;
	int max;
	unsigned char *texture;

}; 
struct mysn {
	Matrix objtoworld;
	Matrix worldtoobj;
	Matrix transNorm;
	enum PrimitiveType obj;
	class SceneMaterial m;
	struct Texture texture;


};

int readTexture(Texture *texture, string fileName);
bool findIsect (Point e, Vector look, double *d, int *t);
void mapTexture(Point isect, double *u, double *v, enum PrimitiveType type);
double calDistance(Point eye, Vector ray, Matrix transform, enum PrimitiveType type);
void calColor(Point e, Vector look, double *r, double *g, double *b, int recursive);
Vector calNormal(Point eyeP, Vector ray, double dist, enum PrimitiveType type);
void flattenHelper(SceneNode *mynode, Matrix& transform);
void flattenParserTree();

/** These are the live variables passed into GLUI ***/
int  recursive = 0;

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
string filenamePath = "data/tests/all.xml";
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

	Matrix eyetoworld = invert(camera->GetModelViewMatrix());
	for (int i = 0; i < pixelWidth; i++) {
		for (int j = 0; j < pixelHeight; j++) {
			//replace the following code
			double r = 0;
			double g = 0;
			double b = 0;
 
			const Point e(eyeX, eyeY, eyeZ);
			Point tmplookat((float)i * 2/pixelWidth - 1, 
					(float)j * 2/pixelHeight - 1, -1);
			const Point lookat = eyetoworld * tmplookat;
			Vector look = lookat - e;
			look.normalize();
			calColor(e, look, &r, &g, &b, recursive);	 

			setPixel(pixels, i, j, r * cap, g * cap, b * cap);

		}
	}
	glutPostRedisplay();
}

void calColor(Point e, Vector look, double *r, double *g, double *b, int recursive) {
	if (recursive < 0) {
		*r =  0;
		*g =  0;
		*b =  0; 
		return;
	}

	int target = -1;
	double dist = -1;
	bool found = false;

    found = findIsect(e, look, &dist, &target);

	//there is valid intersection
	if (found) {

		Point tmpe = sceneNodes[target].worldtoobj * e;        
		Point intersection = e + dist * look;
		Vector tmpv = sceneNodes[target].worldtoobj * look;
		Vector nor = calNormal(tmpe,  tmpv, dist, sceneNodes[target].obj );
		nor = sceneNodes[target].transNorm * nor;
		nor.normalize();

        //diffuse lighting
		double r_d = 0;
		double g_d = 0;
		double b_d = 0;
		//specular lighting
		double r_s = 0;
		double g_s = 0;
		double b_s = 0;
		//texture
		double r_t = 0;
		double g_t = 0;
		double b_t = 0;
		//reflective lighting
		double r_rfl = 0;
		double g_rfl = 0;
		double b_rfl = 0;
		//refractive lighing
		double r_rft = 0;
		double g_rft = 0;
		double b_rft = 0;
		
		int lnum = lights.size();
		for (int i = 0; i < lnum; i++) {
			//only consider point light and directional
			Vector l;
			if (lights[i].type == LIGHT_POINT) {
			    l = lights[i].pos - intersection;
			} else if (lights[i].type == LIGHT_DIRECTIONAL) {
			    l = -lights[i].dir;
			} else { continue; }
			
			
			l.normalize();
			Vector r = 2 * dot(nor, l) * nor  - l;
			r.normalize();
			double product_d = dot(nor, l);
			double product_s = -dot(look, r);

			//only consider positive direction
			int tmptarget = -1;
			double tmpdist = -1;
			bool tmpfound = false;
			if (lights[i].type == LIGHT_POINT) {
			    tmpfound = findIsect(lights[i].pos, -l, &tmpdist, &tmptarget);
			    if (!tmpfound || (tmptarget != target)) continue;
			} else {
			    
			    tmpfound = findIsect(intersection + 0.0001 * l, l, &tmpdist, &tmptarget);
			    if (tmpfound) continue;
			}
			if (product_d > 0) {

				r_d += lights[i].color.r * product_d;  
				g_d += lights[i].color.g * product_d;
				b_d += lights[i].color.b * product_d;
			}

			if (product_s > 0) {
				double shininess = sceneNodes[target].m.shininess > 0 ?
				           pow(product_s, sceneNodes[target].m.shininess) :
				           product_s;
				r_s += lights[i].color.r * shininess;  
				g_s += lights[i].color.g * shininess;
				b_s += lights[i].color.b * shininess; 

			} 

		}

        //recursive lighting
        Vector newlook = look - 2 * dot(look, nor) * nor;
        newlook.normalize();
        Point neweye = intersection + 0.0001 * newlook; 
        calColor(neweye, newlook, &r_rfl, &g_rfl, &b_rfl, recursive - 1);
        
        		
		*r +=  (globalData.ka * sceneNodes[target].m.cAmbient.r 
				+ r_d * globalData.kd * sceneNodes[target].m.cDiffuse.r
				+ r_s * sceneNodes[target].m.cSpecular.r * globalData.ks 
				+ r_rfl * globalData.ks * sceneNodes[target].m.cReflective.r);
				 
		*g +=  (globalData.ka * sceneNodes[target].m.cAmbient.g 
				+ g_d * globalData.kd * sceneNodes[target].m.cDiffuse.g
				+ g_s * sceneNodes[target].m.cSpecular.g * globalData.ks 
				+ g_rfl * globalData.ks * sceneNodes[target].m.cReflective.g);
  
		*b += (globalData.ka * sceneNodes[target].m.cAmbient.b
				+ b_d * globalData.kd * sceneNodes[target].m.cDiffuse.b
				+ b_s * sceneNodes[target].m.cSpecular.b * globalData.ks 
				+ b_rfl * globalData.ks * sceneNodes[target].m.cReflective.b);
		  		
 	
				
				
 
		//map texture

		if (sceneNodes[target].m.textureMap != NULL &&
				(sceneNodes[target].m.textureMap->filename.size() > 0)) {
			if (sceneNodes[target].texture.texture == NULL) {
				readTexture(&(sceneNodes[target].texture), 
						sceneNodes[target].m.textureMap->filename);
			}


			Point isect = (tmpe + dist * tmpv); 

			double u, v;
			mapTexture(isect, &u, &v, sceneNodes[target].obj); 

			int w = sceneNodes[target].texture.width;
			int h = sceneNodes[target].texture.height;
			int s = u * w * sceneNodes[target].m.textureMap->repeatU;
			s = s % w;
			int t = v * h * sceneNodes[target].m.textureMap->repeatV;
			t = t % h;

			unsigned char *tmpc = sceneNodes[target].texture.texture 
				+ (sceneNodes[target].texture.height - t - 1) * 3 * w 
				+ 3 * s;

			*r = *r * (1 - sceneNodes[target].m.blend)
				+ tmpc[0] * sceneNodes[target].m.blend 
				/ sceneNodes[target].texture.max;
			*g = *g * (1 - sceneNodes[target].m.blend)
				+ tmpc[1] * sceneNodes[target].m.blend 
				/ sceneNodes[target].texture.max;
			*b = *b * (1 - sceneNodes[target].m.blend)
				+ tmpc[2] * sceneNodes[target].m.blend 
				/sceneNodes[target].texture.max;

		}
		if (*r > 1) *r = 1;
		if (*g > 1) *g = 1;
		if (*b > 1) *b = 1;

	} else {

		*r =  0;
		*g =  0;
		*b =  0; 

	} 
}

bool findIsect (Point e, Vector look, double *d, int *t) {

    int target = 0;
	double dist = -1;
	bool found = false;

	//calculate distance from eye to intersection
	int size = sceneNodes.size();

	for (int j = 0; j < size; j++) {

		double tmpdist = calDistance(e, look, sceneNodes[j].worldtoobj,
				sceneNodes[j].obj);

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
	
	if (found) {
	    *t = target;
	    *d = dist;
	    return true;
	}
	return false;
}

void mapTexture(Point isect, double *u, double *v, enum PrimitiveType type) {

	switch (type) {
		case SHAPE_CUBE:
			return cube->map(isect, u, v);

		case SHAPE_CYLINDER:
			return cylinder->map(isect, u, v);

		case SHAPE_CONE:
			return cone->map(isect, u, v);

		case SHAPE_SPHERE:
			return sphere->map(isect, u, v);

		default:
			*u = 0;
			*v = 0;
			return;
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

int readTexture(Texture *texture, string fileName) {
	// Open an input file stream for reading a file
	std::ifstream ppmFile(fileName.c_str());
	// If our file successfully opens, begin to process it.
	if (ppmFile.is_open()){
		int width, height;
		char *magicNumber;
		// line will store one line of input
		std::string line;
		// Our loop invariant is to continue reading input until
		// we reach the end of the file and it reads in a NULL character
		std::cout << "Reading in ppm file: " << fileName << std::endl;
		// Our delimeter pointer which is used to store a single token in a given
		// string split up by some delimeter(s) specified in the strtok function
		char* delimeter_pointer;
		int iteration = 0;
		int pos = 0;
		while ( getline (ppmFile,line) ){
			delimeter_pointer = strtok(NULL," ");        
			char* copy = new char[line.length()+1];
			strcpy(copy,line.c_str());
			delimeter_pointer = strtok(copy," ");

			// Read in the magic number
			if(iteration==0){
				magicNumber = delimeter_pointer;
				std::cout << "Magic Number: " << magicNumber << " ";
				std::cout << std::endl;
			}
			else if(iteration==1){
				std::cout << line << std::endl;
			}
			// Read in dimensions
			else if(iteration==2){
				width = atoi(delimeter_pointer);
				std::cout << "width: " << width << " ";
				texture->width = width;
				delimeter_pointer = strtok(NULL," ");
				height = atoi(delimeter_pointer);
				std::cout << "height: " << height << std::endl;
				texture->height = height;
				// Allocate memory for the color array
				if (width > 0 && height > 0){
					texture->texture = new unsigned char[width*height*3];
					if(texture->texture==NULL){
						std::cout << "Unable to allocate memory for ppm" << std::endl;
						exit(1);
					}
				}
				else{
					std::cout << "PPM not parsed correctly, width and height dimensions are 0" << std::endl;
					exit(1);
				}
			}
			else if(iteration==3){
				std::cout << "color range: 0-" << delimeter_pointer << std::endl;
				texture->max = atoi(delimeter_pointer);
			}
			else{
				// Iterate through the entire line and begin storing values
				while(delimeter_pointer != NULL){
					//std::cout << delimeter_pointer << " ";
					texture->texture[pos] = atoi(delimeter_pointer);
					pos++;
					delimeter_pointer = strtok(NULL," ");
				}
			}
			delete copy;
			iteration++;
		}
		ppmFile.close();
	}
	else{
		std::cout << "Unable to open ppm file" <<fileName<< std::endl;
		return -1;
	} 
	return 0;
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
	tmpNode.objtoworld = tmpTrans;
	tmpNode.worldtoobj = invert(tmpTrans);
	tmpNode.transNorm = transpose(tmpNode.worldtoobj);
	tmpNode.texture.texture = NULL;

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

	int size = sceneNodes.size();

	for (int j = 0; j < size; j++) {
		if (sceneNodes[j].texture.texture != NULL)
			delete sceneNodes[j].texture.texture;
	}
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

	main_window = glutCreateWindow("COMP 175 Assignment 5");
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
	GLUI_Spinner* recursiveSpinner = 
		glui->add_spinner("Recursive:", GLUI_SPINNER_INT, &recursive);
	recursiveSpinner->set_int_limits(0, 10);

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



