#ifndef BLOCK_H
#define BLOCK_H

#include<glm/glm.hpp>

#include<vector>
#include<cstdint>
#include<memory>
#include<algorithm>
#include<map>
#include<array>
#include<utility>

#include"Mesh.h"
#include"Chunk.h"
#include"CubeBuilder.h"
#include"Decoration.h"

enum class BlockType
{
	AIR = 0,
	GRASS,
	DIRT,
	STONE,
	WOOD,
	LEAVES,
	WATER
};

class Block
{

public:

	static std::array<glm::vec2, 6> genTexCoords(const BlockType type);

private:
	static float toTex(float coord);
};

#endif // !BLOCK_H


