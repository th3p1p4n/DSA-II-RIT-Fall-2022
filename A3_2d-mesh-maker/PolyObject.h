// Course: IGME 309-02
// Student Name: Andrew Broderick
// Assignment Number: 03

#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/constants.hpp>
using namespace glm;
using namespace std;
class PolyObject
{
private:
	vector <vec2> vertices; // all vertices in C++ vector
	vec3 color; // color of this polygon
public:

	PolyObject();
	~PolyObject();
	void addVertex(vec2 p_vert); // add vertex at the end of the vertex list
	void setColor(vec3 p_color); // set the color of this polygon
	unsigned int getVertNum(); // return the number of vertices
	void draw(); // draw the polygon if it’s completed
	void draw(vec2 p_mousePos); // draw the polygon if it’s being created
};
