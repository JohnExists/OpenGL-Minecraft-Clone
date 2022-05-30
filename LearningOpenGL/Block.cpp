#include "Block.h"

//////////////////////////////////
/*		Public Functions		*/
//////////////////////////////////

std::array<glm::vec2, 6> Block::genTexCoords(const BlockType type)
{
	switch (type)
	{
	case BlockType::GRASS:
		return 	std::array<glm::vec2, 6>({
				{ toTex(1), toTex(7) },
				{ toTex(1), toTex(7) },
				{ toTex(1), toTex(7) },
				{ toTex(1), toTex(7) },
				{ toTex(0), toTex(7) },
				{ toTex(2), toTex(7) } });
	case BlockType::DIRT:
		return 	std::array<glm::vec2, 6>({
				{ toTex(0), toTex(7) },
				{ toTex(0), toTex(7) },
				{ toTex(0), toTex(7) },
				{ toTex(0), toTex(7) },
				{ toTex(0), toTex(7) },
				{ toTex(0), toTex(7) } });
	case BlockType::STONE:
		return 	std::array<glm::vec2, 6>({
				{ toTex(3), toTex(7) },
				{ toTex(3), toTex(7) },
				{ toTex(3), toTex(7) },
				{ toTex(3), toTex(7) },
				{ toTex(3), toTex(7) },
				{ toTex(3), toTex(7) } });
		break;
	case BlockType::WOOD:
		return 	std::array<glm::vec2, 6>({
				{ toTex(4), toTex(7) },
				{ toTex(4), toTex(7) },
				{ toTex(4), toTex(7) },
				{ toTex(4), toTex(7) },
				{ toTex(4), toTex(7) },
				{ toTex(4), toTex(7) } });
		break;
	case BlockType::LEAVES:
		return 	std::array<glm::vec2, 6>({
				{ toTex(5), toTex(7) },
				{ toTex(5), toTex(7) },
				{ toTex(5), toTex(7) },
				{ toTex(5), toTex(7) },
				{ toTex(5), toTex(7) },
				{ toTex(5), toTex(7) } });
		break;
	case BlockType::WATER:
		return 	std::array<glm::vec2, 6>({
				{ toTex(6), toTex(7) },
				{ toTex(6), toTex(7) },
				{ toTex(6), toTex(7) },
				{ toTex(6), toTex(7) },
				{ toTex(6), toTex(7) },
				{ toTex(6), toTex(7) } });
		break;
	}

}

//////////////////////////////////
/*		Private Functions		*/
//////////////////////////////////

float Block::toTex(float coord)
{
	return coord/ 8.0f;
}
