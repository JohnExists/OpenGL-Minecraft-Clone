#ifndef GL_OBJECT_H
#define GL_OBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include<vector>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;

};

class GLObject
{
protected:
	GLuint data = 0;

public:
	virtual void use() = 0;
	virtual void abandon() = 0;

};

class VertexObject : public GLObject
{
public:
	VertexObject(std::vector<Vertex>* vertices);

	// Inherited via GLObject
	virtual void use() override;
	virtual void abandon() override;
};

class VertexArrayObject : public GLObject
{
private:
	VertexObject* vertexData;
public:
	VertexArrayObject(std::vector<Vertex>* vertices);
	// Inherited via GLObject
	virtual void use() override;
	virtual void abandon() override;

	void draw();

private:
	void link();
	void linkData(int slot, int size, void* offset);

};

#endif // !GL_OBJECT_H