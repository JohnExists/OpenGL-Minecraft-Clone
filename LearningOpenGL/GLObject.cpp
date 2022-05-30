#include "GLObject.h"


VertexObject::VertexObject(std::vector<Vertex>* vertices)
{
	glGenBuffers(1, &data);

	this->use();

	glBufferData(
		GL_ARRAY_BUFFER,
		vertices->size() * sizeof(Vertex),
		&vertices->at(0),
		GL_STATIC_DRAW
	);

}

void VertexObject::use()
{
	glBindBuffer(GL_ARRAY_BUFFER, data);
}

void VertexObject::abandon()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexArrayObject::VertexArrayObject(std::vector<Vertex>* vertices)
{
	glGenVertexArrays(1, &data);
	this->use();
	vertexData = new VertexObject(vertices);
	this->link();
	this->abandon();
	vertexData->abandon();
}

void VertexArrayObject::use()
{
	glBindVertexArray(data);
}

void VertexArrayObject::abandon()
{
	glBindVertexArray(0);
}

void VertexArrayObject::draw()
{
}

void VertexArrayObject::link()
{
	linkData(0, 3, (void*) 0);
	linkData(1, 3, (void*) offsetof(Vertex, normal));
	linkData(2, 2, (void*) offsetof(Vertex, texCoords));

}

void VertexArrayObject::linkData(int slot, int size, void* offset)
{
	glEnableVertexAttribArray(slot);
	glVertexAttribPointer(
		slot , size, GL_FLOAT, GL_FALSE, sizeof(Vertex), offset
	);

}
