#ifndef GEOMETRY_H
#define GEOMETRY_H

/*  ============== Vertex ==============
	Purpose: Stores properties of each vertex
	Use: Used in face structure
	==================================== */  
class vertex{
public:
	float x,y,z;		// position in 3D space
	float confidence;
	float intensity;
	float r,g,b;		// Color values
};

/*  ============== Face ==============
	Purpose: Store list of vertices that make up a polygon.
	In modern versions of OpenGL this value will always be 3(a triangle)
	Use: Used in Shape data structure.
	==================================== */  
class face{
public:
	int vertexCount;  // assuming 3 for this
	int* vertexList;  // assuming this has size 3
  
        //normal vector
        float normX, normY, normZ;
        //dot of normal and look
        float dotProd;

        // Default constructor
	face(){
		vertexCount = 0;
	}

};

/* Edge: Connects two vertices, and two faces. 
 */
class edge{
public:
        int vertices[2];
        int faces[2];
        
        //default constructor
        edge(){
            //these are -1 because 0 would be a meaningful value
			vertices[0] = -1;
			vertices[1] = -1;
            faces[0] = -1;
            faces[1] = -1;
        }
};
#endif
