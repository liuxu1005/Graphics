#version 120 //Most current OpenGL version avaible in BGE at this shader creation time

// Similar to a C program, we have a main
// It is by default void, and there are no command line arguments.
// There also should be only one shader with a 'main'.
void main()
{

	// This is the position of the vertex.
	// Remember, that the vertex shader is operating on each individual
	// vertex in our program.

	// The gl_ModelViewProjectionMatrix comes from our glMatrixMode(GL_PROJECTION)
	// that we have set in our program.

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

	// Note that we are currently working on the position of the vertex shader.
	// When we write this vertex shader, it is the expectation that this is where we will
	// be processing vertex information. We can no longer use the fixed-function pipeline
	// in order to make modifications to our vertices.

	// Additionally, it's important to remember that we are working on one vertex at a time.
	// We do not have knowledge of other vertices(the topology) around the vertex that is being
	// processed.
	
}





