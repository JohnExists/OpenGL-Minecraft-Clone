#ifndef DECORATION_H
#define DECORATION_H

#include<map>
#include<glm/glm.hpp>
#include<fstream>
#include<string>

#include"Block.h"

enum class BlockType;

enum class Decoration
{
	TREE
};

namespace decor
{

	using positions_t = std::multimap<BlockType, glm::vec3>;

	positions_t* loadTree();
	positions_t load(Decoration decoration);
	positions_t* loadFromFile(const char* filePath);

}

#endif // !DECORATION_H


