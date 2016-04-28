#include "Camera.h"

Camera::Camera() {
  
}

Camera::~Camera() {
}
void Camera::Reset() {
    nearP = 0.1;
    farP = 25;
    eyeP = Point(0, 0, 0);
    focusP = Point(0, 0, -1);
    lookV = Vector(0, 0, -1);
    upV = Vector(0, 1, 0);
    u = Vector(1, 0, 0);
    v = Vector(0, 1, 0);
    w = Vector(0, 0, 1);
   
    viewA = 45;
    left = -1;
    right = 1;
    bottom = -1;
    top = 1; 
   // sw = 500;
   // sh = 500;
}

void Camera::Orient(Point& eye, Point& focus, Vector& up) {
     //set eye position
     eyeP[0] = eye[0];
     eyeP[1] = eye[1];
     eyeP[2] = eye[2];
  
     //set focue position
     focusP[0] = focus[0];
     focusP[1] = focus[1];
     focusP[2] = focus[2];
   
     //set up vector;
     upV = up;
     
     //set look vector;
     Vector t(focusP[0] - eyeP[0],
              focusP[1] - eyeP[1],
              focusP[2] - eyeP[2]);
     t.normalize();
     lookV = t;
     //set camera coordinates
     
      
     w = -lookV;
     w.normalize();
     t = cross(up, w);
     u = t;
     u.normalize();
     v = cross(w, u);
     v.normalize();
     
}


void Camera::Orient(Point& eye, Vector& look, Vector& up) {
     //set eye position
     eyeP[0] = eye[0];
     eyeP[1] = eye[1];
     eyeP[2] = eye[2];
   
     
     //set look vector;
     look.normalize();
     lookV = look;
     
     //set up vector;
     up.normalize();
     upV = up;
     
     //set focus position;
     focusP = eyeP + look;
     
     //set camera coordinates
     w = -lookV;
     w.normalize();
     u = cross(up, w);
     u.normalize();
     v = cross(w, u);
     v.normalize();
     
}

Matrix Camera::GetProjectionMatrix() {
 /*   double tanw = tan((PI/360)*viewA)*sw/sh;
    double tanh = tan((PI/360)*viewA);
    Matrix s( 1/(tanw * farP), 0 , 0, 0,
	         0,  1/(tanh * farP), 0, 0,
	         0, 0, 1/farP, 0,
	         0, 0, 0, 1 );
	         
	double c = -nearP/farP;
	Matrix m(1, 0, 0, 0,
	         0, 1, 0, 0,
	         0, 0, -1/(c+1), c/(c+1),
	         0, 0,  -1, 0);
 
  
	return m*s; */
	
    double c = -nearP/farP;
	Matrix m(1, 0, 0, 0,
	         0, 1, 0, 0,
	         0, 0, -1/(c+1), c/(c+1),
	         0, 0,  -1, 0);
 
    return m;
	
}


void Camera::SetViewAngle (double viewAngle) {
 
    viewA = viewAngle;
}

void Camera::SetNearPlane (double nearPlane) {
    nearP = nearPlane;
}

void Camera::SetFarPlane (double farPlane) {
    farP = farPlane;
}

void Camera::SetScreenSize (int screenWidth, int screenHeight) {
    sw = screenWidth;
    sh = screenHeight;
}

Matrix Camera::GetModelViewMatrix() {

    Matrix t(1, 0, 0, -eyeP[0],
	         0, 1, 0, -eyeP[1],
	         0, 0, 1, -eyeP[2],
	         0, 0, 0, 1);
	         
	Matrix r(u[0], u[1], u[2], 0,
	         v[0], v[1], v[2], 0,
	         w[0], w[1], w[2], 0,
	         0,  0,  0,  1);

    double tanw = tan((PI/360)*viewA)*sw/sh;
    double tanh = tan((PI/360)*viewA);
    Matrix s( 1/(tanw * farP), 0 , 0, 0,
	         0,  1/(tanh * farP), 0, 0,
	         0, 0, 1/farP, 0,
	         0, 0, 0, 1 );
 
	return s*r*t;
	
}

Matrix Camera::GetOrthMV() {

    Vector l = lookV;
    l.normalize();
    Point p = eyeP + nearP * l;
    Matrix t(1, 0, 0, -p[0],
	         0, 1, 0, -p[1],
	         0, 0, 1, -p[2],
	         0, 0, 0, 1);
	         
	Matrix r(u[0], u[1], u[2], 0,
	         v[0], v[1], v[2], 0,
	         w[0], w[1], w[2], 0,
	         0,  0,  0,  1);
	         
 
 
	return r*t;


}
 
Matrix Camera::GetOrthMatrix() { 

  double tanw = tan((PI/360)*viewA)*sw/sh;
  double tanh = tan((PI/360)*viewA);
             
  Matrix s(1.0f/(tanw * nearP), 0, 0, 0,
             0, 1.0f/(tanh * nearP), 0, 0,
             0, 0, -1.0f/farP, 0,
             0, 0, 0, 1);            
             
    return s;
};

void Camera::RotateV(double angle) {
    double a = angle*(PI/180);
    Matrix r = rot_mat(v, a); 
    u = r * u;
    w = r * w; 
    u.normalize();
    
    w.normalize();
}

void Camera::RotateU(double angle) {
    double a = angle*(PI/180);
    Matrix r = rot_mat(u, a); 
    v = r * v;
    w = r * w;
         
    v.normalize();
    w.normalize();
}

void Camera::RotateW(double angle) {
    double a = angle*(PI/180);
    Matrix r = rot_mat(w, a); 
    u = r * u;
    v = r * v;
    u.normalize();
    v.normalize();
 
}

void Camera::Translate(const Vector &v) {
    eyeP = eyeP + v;
    focusP = focusP + v;
}


void Camera::Rotate(Point p, Vector axis, double degrees) {
    double a = degrees*(PI/180);
    Matrix r = rot_mat(p, axis, a);
    u = r * u;
    v = r * v;
    w = r * w;
    u.normalize();
    v.normalize();
    w.normalize();
}



Point Camera::GetEyePoint() {
	
	return eyeP;
}

Vector Camera::GetLookVector() {
	 
	return lookV;
}

Vector Camera::GetUpVector() {
	
	return upV;
}

double Camera::GetViewAngle() {
  
	return viewA;
}

double Camera::GetNearPlane() {
	return nearP;
}

double Camera::GetFarPlane() {
	return farP;
}

int Camera::GetScreenWidth() {
	return sw;
}

int Camera::GetScreenHeight() {
	return sh;
}

double Camera::GetFilmPlanDepth() {
	return nearP;
}

double Camera::GetLeft() {
	return left;
}

double Camera::GetRight() {
	return right;
}

double Camera::GetBottom() {
	return bottom;
}

double Camera::GetTop() {
	return top;
}

double Camera::GetScreenWidthRatio() {
	return sw/sh;
}

void Camera::SetOrth(double l, double r, double b, double t) {
    left = l;
    right = r;
    bottom = b;
    top = t;

}

 
