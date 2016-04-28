#version 120
uniform vec3 color;
varying vec3 color2;	//out
attribute vec3 atr;	//in
varying vec2 texcoord;

void main()
{
	gl_Position=gl_ModelViewProjectionMatrix*gl_Vertex;
	color2=atr;
	texcoord=gl_MultiTexCoord0.xy;
}




