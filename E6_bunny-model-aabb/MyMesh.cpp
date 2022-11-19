#include <GL/glew.h>
#include <GL/freeglut.h>

#include "MyMesh.h"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

MyMesh::MyMesh()
{
	vertNum = triNum = 0;
	vertices = NULL;
	indices = NULL;
	vNormals = NULL;
	vbo_id = nbo_id = ibo_id = 0;

	vec3 maxVert;
	vec3 minVert;

	amb = diff = spec = vec3(0.5);
	shinness = 5.0f;

	viewMode = SHADED;
}

MyMesh::~MyMesh()
{
	//Don't forget to deallocate the buffer objects from the GPU when your program is shut down!
	glDeleteBuffers(1, &vbo_id);
	glDeleteBuffers(1, &nbo_id);
	glDeleteBuffers(1, &ibo_id);
}

// Create a public function named computeAABB() in MyMesh class, which should be called in
// the init() function in main.cpp, after the model file is loaded. This function should compute
// the values of maxVert and minVert by iterating through all vertices.
void MyMesh::computeAABB()
{
    //…
    // you need to appropriately initialize maxVert and minVert…
    //…
	for (unsigned int i = 0; i < vertNum; i++)
	{
		// …
		// add your code here…
		// …
	}
}

// Create a public function named drawAABB() in MyMesh class, which should be called in the
// display() function in main.cpp.This function should draw a red wireframe box using the maxVert and minVert.
// Hint : the eight corner points of the box can be found from the maximum and minimum vertices.
void MyMesh::drawAABB()
{
	glDisable(GL_LIGHTING);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_LINES);

	// …
	// put your stuff here …
	// …

	glEnd();
	glPopMatrix();
}

vec3 MyMesh::setFaceNormal(vec3 v0, vec3 v1, vec3 v2)
{
	vec3 n = cross((v1 - v0), (v2 - v1));
	if (n.length() == 0)
		return vec3(0);
	return normalize(n);
}


void MyMesh::loadFromOBJ(const char* fileName)
{
	vector <vec3> temp_verts;
	vector <uvec3> temp_tris;

	ifstream fs(fileName);

	char c;
	vec3 pos;
	int index[3];
	int vid = 0;

	std::string line;
	while (std::getline(fs, line)) {
		std::istringstream iss(line);

		iss >> c;

		switch (c) {
		case 'v':
		{
			// read a vertex
			iss >> pos.x;
			iss >> pos.y;
			iss >> pos.z;
			temp_verts.push_back(pos);
			break;
		}
		case 'f':
		{
			// read a triangle's vertex indices
			iss >> index[0];
			iss >> index[1];
			iss >> index[2];
			// NOTE: index in obj files starts from 1
			temp_tris.push_back(uvec3(index[0] - 1, index[1] - 1, index[2] - 1));
			break;
		}
		default:
			// skip the line
			break;
		}
	}
	fs.close();

	vertNum = temp_verts.size();
	triNum = temp_tris.size();
	// store the data into GPU-friendly array structures
	vertices = new float[vertNum * 3];
	indices = new unsigned int[triNum * 3];
	vNormals = new float[vertNum * 3];

	for (unsigned int i = 0; i < vertNum; i++) {
		// copy vertex data to vertex array
		vertices[i * 3 + 0] = temp_verts[i].x;
		vertices[i * 3 + 1] = temp_verts[i].y;
		vertices[i * 3 + 2] = temp_verts[i].z;

		// initialize vertex normal values t0 <0,0,0>
		vNormals[i * 3 + 0] = vNormals[i * 3 + 1] = vNormals[i * 3 + 2] = 0.0f;
	}
	for (unsigned int i = 0; i < triNum; i++) {
		// copy triangle data to index array
		indices[i * 3 + 0] = temp_tris[i].x;
		indices[i * 3 + 1] = temp_tris[i].y;
		indices[i * 3 + 2] = temp_tris[i].z;
	}

	// compute face normals
	for (unsigned int i = 0; i < triNum; i++) {
		// get the face normal of the triangle and accumulate it into each vertex of this triangle
		vec3 n = setFaceNormal(temp_verts[temp_tris[i].x], temp_verts[temp_tris[i].y], temp_verts[temp_tris[i].z]);
		vNormals[temp_tris[i].x * 3 + 0] += n.x;
		vNormals[temp_tris[i].x * 3 + 1] += n.y;
		vNormals[temp_tris[i].x * 3 + 2] += n.z;

		vNormals[temp_tris[i].y * 3 + 0] += n.x;
		vNormals[temp_tris[i].y * 3 + 1] += n.y;
		vNormals[temp_tris[i].y * 3 + 2] += n.z;

		vNormals[temp_tris[i].z * 3 + 0] += n.x;
		vNormals[temp_tris[i].z * 3 + 1] += n.y;
		vNormals[temp_tris[i].z * 3 + 2] += n.z;
	}

	// normalize accumulated vertex normals
	for (unsigned int i = 0; i < vertNum; i++) {
		vec3 n = normalize(vec3(vNormals[i * 3 + 0], vNormals[i * 3 + 1], vNormals[i * 3 + 2]));
		vNormals[i * 3 + 0] = n.x;
		vNormals[i * 3 + 1] = n.y;
		vNormals[i * 3 + 2] = n.z;

		//cout << "v[" << i<<"]'s normal=" << vNormals[i * 3 + 0] << "," << vNormals[i * 3 + 1] << "," << vNormals[i * 3 + 2] << endl;
	}

	prepareBufferObjects();
}

void MyMesh::prepareBufferObjects()
{
	// prepare VBO
	// generate a new VBO and get the associated ID
	glGenBuffers(1, &vbo_id);

	// bind VBO in order to use
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

	// upload data to VBO - data went to GPU
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* vertNum * 3, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // clean up

	// it is safe to delete after copying data to VBO
	// for example, if vertices array was dynamically created, it is saft to call "delete [ ] vertices;"
	delete[] vertices;

	// repeat for vertex normal
	glGenBuffers(1, &nbo_id);
	glBindBuffer(GL_ARRAY_BUFFER, nbo_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertNum * 3, vNormals, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0); // clean up
	delete[] vNormals;

	// repeat for indices
	glGenBuffers(1, &ibo_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)* triNum * 3, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // clean up
	delete[] indices;
}
void MyMesh::update()
{
	// we will use this for transformations later.... 
}

void MyMesh::draw()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	switch (viewMode) {

	case SHADED:
		drawShadedMesh();
		break;
	case SHADED_WITH_WIREFRAME:
		drawShadedMesh();
		drawWireframeMesh();
		break;

	default:
		break;
	}

	glPopMatrix();
}

void MyMesh::drawShadedMesh()
{
	if (vertNum <= 0 && triNum <= 0)
		return;
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0f, 1.0f);
	glPolygonMode(GL_FRONT, GL_FILL);

	glMaterialfv(GL_FRONT, GL_AMBIENT, value_ptr(amb));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, value_ptr(diff));
	glMaterialfv(GL_FRONT, GL_SPECULAR, value_ptr(spec));
	glMaterialf(GL_FRONT, GL_SHININESS, shinness);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, nbo_id);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_id);
	glDrawElements(GL_TRIANGLES, triNum * 3, GL_UNSIGNED_INT, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glPopMatrix();
	glDisable(GL_POLYGON_OFFSET_FILL);
}

void MyMesh::drawWireframeMesh()
{
	if (vertNum <= 0 && triNum <= 0)
		return;

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING); // disable lighting so that it uses the default flat color for shading
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glColor3f(0.1f, 0.1f, 0.1f); 
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, nbo_id);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_id);
	glDrawElements(GL_TRIANGLES, triNum * 3, GL_UNSIGNED_INT, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	glPopMatrix();
}