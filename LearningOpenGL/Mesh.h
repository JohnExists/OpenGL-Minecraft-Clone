#ifndef MESH_H
#define MESH_H

#include<vector>
#include<iostream>
#include <glad/glad.h>
#include<initializer_list>
#include<glm/gtc/matrix_transform.hpp>

#include "Texture.h"
#include "Shader.h"
#include "GLObject.h"


class Mesh
{
protected:
	std::vector<Vertex>		vertices;
	const Texture*			texture;
	glm::mat4 modelMatrix;
	VertexArrayObject* vao = nullptr;

public:
	Mesh(
		const std::vector<Vertex>		vertices,
		const Texture*					texture
	);

	void scale(float x, float y, float z);
	void translate(float x, float y, float z);
	//void rotate();

	void draw();
	void loadVertices();

	std::vector<Vertex>& getVertices();
	void setModelMatrix(const glm::mat4 model);
	glm::mat4& getModelMatrix();

};

#endif