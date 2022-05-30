#include "Mesh.h"

//////////////////////////////////
/*		Public Functions		*/
//////////////////////////////////

Mesh::Mesh(
	const std::vector<Vertex>		vertices, 
	const Texture*					texture
) 
{
	this->vertices	= vertices;
	this->texture	= texture;
	loadVertices();
}

void Mesh::scale(float x, float y, float z)
{
	modelMatrix = glm::scale(modelMatrix, glm::vec3(x, y, z));
}

void Mesh::translate(float x, float y, float z)
{
	modelMatrix = glm::translate(modelMatrix, glm::vec3(x, y, z));
}


void Mesh::draw()
{
	if (vao == nullptr) return;

	vao->use();
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	vao->abandon();
}

void Mesh::loadVertices()
{
	if (vertices.empty()) return;

	delete vao;
	vao = new VertexArrayObject(&this->vertices);

}

std::vector<Vertex>& Mesh::getVertices()
{
	return vertices;
}

void Mesh::setModelMatrix(const glm::mat4 model)
{
	this->modelMatrix = model;
}

glm::mat4& Mesh::getModelMatrix()
{
	return modelMatrix;
}

