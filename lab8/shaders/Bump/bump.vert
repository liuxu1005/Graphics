#version 120 

// Similar to a C program, we have a main
// It is by default void, and there are no command line arguments.
// There also should be only one shader with a 'main'.
void main()
{

	// Note that we are currently working on the position of the vertex shader.
	// When we write this vertex shader, it is the expectation that this is where we will
	// be processing vertex information. We can no longer use the fixed-function pipeline
	// in order to make modifications to our vertices.

	// Additionally, it's important to remember that we are working on one vertex at a time.
	// We do not have knowledge of other vertices(the topology) around the vertex that is being
	// processed.

	// We are using two textures. Normally we will need to call the line between twice,
	// once with 0 (texture0), once with 1 (texture1), but since our two textures
	// are using the same coordinates (that is, they overlap perfectly over the same object)
	// we can default to using just the texture0 coordinates.
	// it might seem strange that we're dealing with textures info in a "vertex" shader,
	// but remember that the coordinates of the texture need to be proposed in this shader
	// and passed on to the fragment shader.

	gl_TexCoord[0] = gl_MultiTexCoord0;


	// The gl_ModelViewProjectionMatrix comes from our glMatrixMode(GL_PROJECTION)
	// that we have set in our program. Noet that this matrix is no longer available
	// in the more recent versions of GLSL. But for this assignment, to keep things
	// simple, we keep that here.


	// This is the final (world coordinate) position of the vertex.

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}



