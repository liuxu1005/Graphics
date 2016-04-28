// Similar to a C program, we have a main
// It is by default void, and there are no command line arguments.
// There also should be only one shader with a 'main'.

void main()
{
	
	// The overall job of the fragment shader is to give a color to a pixel.
	// To do that, we use gl_FragColor.

	// We will use a built in GLSL datatype called vec4 that holds values for the color.
	// This is similar to when we used glColor3f in the fixed-function pipeline.
	vec4 color = vec4(1.0, 0.0, 0.0, 1.0);
	gl_FragColor = 	color;

	// Note that we can change the pixel color, but we cannot change the actual pixel coordinate
	// Changes to the viewport are done after the vertex shader but before the fragment shader.

}






