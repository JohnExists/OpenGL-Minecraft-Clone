#ifndef CUBE_BUILDER_H
#define CUBE_BUILDER_H

#include<glm/glm.hpp>

#include<vector>
#include<array>
#include<cstdint>

#include"Mesh.h"

#define LEFT_BOTTOM_BACK	{-0.5f, -0.5f, -0.5f}
#define RIGHT_TOP_BACK		{ 0.5f,  0.5f, -0.5f}
#define RIGHT_BOTTOM_BACK	{ 0.5f, -0.5f, -0.5f}
#define LEFT_TOP_BACK		{-0.5f,  0.5f, -0.5f}

#define LEFT_BOTTOM_FRONT	{-0.5f, -0.5f, 0.5f}
#define RIGHT_TOP_FRONT		{ 0.5f,  0.5f, 0.5f}
#define RIGHT_BOTTOM_FRONT	{ 0.5f, -0.5f, 0.5f}
#define LEFT_TOP_FRONT		{-0.5f,  0.5f, 0.5f}

#define LEFT_BOTTOM_BACK {-0.5f, -0.5f, -0.5f}

class CubeBuilder : public Mesh
{
public:
	enum class Face
	{
		BACK = 1 << 0, //	(-z)
		FRONT = 1 << 1, //	(+z)
		LEFT = 1 << 2, //	(-x)
		RIGHT = 1 << 3, //	(+x)
		TOP = 1 << 4, //	(+y)
		BOTTOM = 1 << 5 //	(-y)
	};

	static void loadVertices(std::uint8_t flags, std::vector<Vertex>& vertices,
		std::array<glm::vec2, 6> tex, float res);

	static void loadFace(std::vector<Vertex>& vertices, 
		std::array<glm::vec2, 6> tex, float res, CubeBuilder::Face face);

};


#endif // !CUBE_BUILDER_H
