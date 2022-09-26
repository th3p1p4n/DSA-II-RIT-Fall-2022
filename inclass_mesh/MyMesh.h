#pragma once

class MyMesh
{
private: 
	unsigned int vertNum; 
	unsigned int triNum;
	
	float* vertices;
	unsigned int* indices; 
	float* vertColors;
	
	// In the future, we will define more vertex and triangle related parameters...
	// vertex normals; - vertNum *3
	// face normals;  - triNum *3
	// texCoords;  - vertNum *2 

public: 
	MyMesh();
	~MyMesh();

	void load(char* fileName);     // called at initialization
	void load(const unsigned int p_vertNum, const unsigned int p_triNum, const float* p_vertices, const unsigned int* p_indices);
	void update();   // usually called in idle, mouse, motion, keyboard callbacks
	void draw();     // called in display callback

	unsigned int getVertNum() { return vertNum; };
	unsigned int getTriNum() { return triNum; };
};

