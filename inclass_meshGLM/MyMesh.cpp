#include "MyMesh.h"
#include <GL/freeglut.h>

#include <iostream>
#include <time.h>
using namespace std;

MyMesh::MyMesh()
{
	vertNum = triNum = 0;
	vertices.clear();
	indices.clear();
	vertColors.clear();;
}

MyMesh::~MyMesh()
{
	vertices.clear();
	vertices.shrink_to_fit();

	indices.clear();
	indices.shrink_to_fit();

	vertColors.clear();
	vertColors.shrink_to_fit();
	
}

void MyMesh::load(char* fileName)
{

}

void MyMesh::load(const unsigned int p_vertNum, const unsigned int p_triNum, const float* p_vertices, const unsigned int* p_indices)
{
	vertNum = p_vertNum;
	triNum = p_triNum;

	for (unsigned int i = 0; i < vertNum; i++) {
		vec2 vertex;
		vertex.x = p_vertices[i * 2];
		vertex.y = p_vertices[i * 2 + 1];

		vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < triNum; i++) {
		uvec3 face;
		face.x = p_indices[i * 3];
		face.y = p_indices[i * 3 + 1];
		face.z = p_indices[i * 3 + 2];

		indices.push_back(face);
	}

	// generate random vertex colors

	time_t t;
	srand((unsigned)time(&t));
	for (unsigned int i = 0; i < vertNum; i++) {
		vec3 color;
		color.r = float(rand()) / (RAND_MAX + 1);
		color.g = float(rand()) / (RAND_MAX + 1);
		color.b = float(rand()) / (RAND_MAX + 1);

		vertColors.push_back(color);
	}

}

void MyMesh::update()
{
	// we will use this for transformations later.... 
}

void MyMesh::draw()
{
	for (int i = 0; i < triNum; ++i) {
		glBegin(GL_TRIANGLES);
		uvec3 triangle = indices[i];

		vec2 vertex1 = vertices[triangle.x];
		vec3 color1 = vertColors[triangle.x];

		vec2 vertex2 = vertices[triangle.y];
		vec3 color2 = vertColors[triangle.y];

		vec2 vertex3 = vertices[triangle.z];
		vec3 color3 = vertColors[triangle.z];

		glColor3f(color1.r, color1.g, color1.b);
		glVertex2f(vertex1.x, vertex1.y);

		glColor3f(color2.r, color2.g, color2.b);
		glVertex2f(vertex2.x, vertex2.y);

		glColor3f(color3.r, color3.g, color3.b);
		glVertex2f(vertex3.x, vertex3.y);
		glEnd();
	}
}