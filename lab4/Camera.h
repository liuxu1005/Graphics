

#ifndef CAMERA_H
#define CAMERA_H

#include "Algebra.h"
#include <math.h>
#include <iostream>

 

class Camera {
public:
Camera();
~Camera();
void Orient(Point& eye, Point& focus, Vector& up);
void Orient(Point& eye, Vector& look, Vector& up);
void SetViewAngle (double viewAngle);
void SetNearPlane (double nearPlane);
void SetFarPlane (double farPlane);
void SetScreenSize (int screenWidth, int screenHeight);
void SetOrth(double l, double r, double b, double t);  

Matrix GetProjectionMatrix();
Matrix GetModelViewMatrix();
Matrix GetOrthMatrix();
Matrix GetOrthMV();

void RotateV(double angle);
void RotateU(double angle);
void RotateW(double angle);
void Rotate(Point p, Vector axis, double degree);
void Translate(const Vector &v);

Point GetEyePoint();
Vector GetLookVector();
Vector GetUpVector();
double GetViewAngle();
double GetNearPlane();
double GetFarPlane();
int GetScreenWidth();
int GetScreenHeight();
double GetLeft();
double GetRight();
double GetBottom();
double GetTop();
double GetFilmPlanDepth();
double GetScreenWidthRatio();

 

private:
    Point eyeP, focusP;
    Vector lookV, upV, u, v, w;
   
    double viewA, nearP, farP;
    double left, right, bottom, top;
    int sw, sh;
    
    
};
#endif

