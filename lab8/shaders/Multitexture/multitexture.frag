//fragment shader, create a file for it named fragment.frag
#version 120
uniform sampler2D img;
uniform sampler2D img2;
uniform vec3 color;
varying vec3 color2;	//Going 'in' to the shader
varying vec2 texcoord;

void main()
{
	vec4 texcolor=texture2D(img,texcoord);
	vec4 texcolor2=texture2D(img2,texcoord);
	gl_FragColor=texcolor*0.25 + texcolor2*0.75;
}






