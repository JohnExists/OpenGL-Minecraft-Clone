#include "Chunk.h"

//////////////////////////////////
/*		Public Functions		*/
//////////////////////////////////

Chunk::Chunk(const glm::vec2& position, World* world, FastNoiseLite& fnl)
	: noise(fnl), position(position), texture(texture), world(world)
{
	blocks = new BlockType[MAX_XZ * MAX_Y * MAX_XZ]{};
	loadBlocks();
}

Chunk::~Chunk()
{
	delete[] blocks;
}


void Chunk::draw(Renderer& renderer, int meshToDraw)
{
	const int DRAW_OPAQUE_MESH = 0;
	const int DRAW_TRANSPARENT_MESH = 1;

	loadMatrix(renderer);
	if (meshToDraw == DRAW_OPAQUE_MESH && mesh != nullptr) renderer.draw(mesh);
	if (meshToDraw == DRAW_TRANSPARENT_MESH && transparent != nullptr) renderer.draw(transparent);
}


void Chunk::loadMesh()
{
	delete mesh;
	mesh = nullptr;

	delete transparent;
	transparent = nullptr;

	std::vector<Vertex> vertices;
	std::vector<Vertex> transparentVertices;

	for (int x = 0; x < MAX_XZ; x++)
	{
		for (int z = 0; z < MAX_XZ; z++)
		{
			for (int y = 0; y < MAX_Y; y++)
			{
				BlockType block = getLocalBlockAt(x, y, z);

				if (block == BlockType::AIR) continue;

				if (block == BlockType::WATER) addBlockToChunkMesh(transparentVertices, x, y, z);
				else addBlockToChunkMesh(vertices, x, y, z);
			}
		}
	}

	//firstTime = true;

	if (vertices.size() != 0) mesh = new Mesh(vertices, texture);
	if (transparentVertices.size() != 0) transparent = new Mesh(transparentVertices, texture);
}

BlockType& Chunk::getBlockAt(glm::vec3& blockPositon)
{
	return getLocalBlockAt(
		blockPositon.x - (this->position.x * MAX_XZ),
		blockPositon.y,
		blockPositon.z - (this->position.y * MAX_XZ)
	);

}

void Chunk::breakBlockAt(glm::vec3& position)
{
	getBlockAt(position) = BlockType::AIR;
	loadMesh();
}

const glm::vec2& Chunk::getPosition() const
{
	return position;
}

//////////////////////////////////
/*		Private Functions		*/
//////////////////////////////////

void Chunk::loadMatrix(Renderer& renderer)
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(position.x * MAX_XZ, 0, position.y * MAX_XZ));

	if (mesh != nullptr) mesh->setModelMatrix(model);
	if (transparent != nullptr) transparent->setModelMatrix(model);
}

void Chunk::loadBlocks()
{
	for (int x = 0; x < MAX_XZ; x++)
	{
		for (int z = 0; z < MAX_XZ; z++)
		{
			int perlinY = getPerlinY(x, z);

			for (int y = 0; y <= std::max(perlinY, SEA_LEVEL); y++)
			{
				BlockType& b = getLocalBlockAt(x, y, z);
				if (y > perlinY) b = BlockType::WATER;
				else if (y == perlinY)
				{
					b = BlockType::GRASS;
					if (perlinY > SEA_LEVEL + 5 &&
						random::generateRandom(std::random_device{}(), 0, 1) < 0.007)
					{
						loadDecoration(Decoration::TREE, x, y, z);
					}
				}
				else if (y > perlinY - 3) b = BlockType::DIRT;
				else if (y <= perlinY - 3) b = BlockType::STONE;

			}
		}
	}

}

void Chunk::loadDecoration(Decoration decoration, int x, int y, int z)
{
	for (const auto& [block, position] : decor::load(decoration))
	{
		if (!isBlockWithinBounds(x + position.x, z + position.z)) continue;
		getLocalBlockAt(x + position.x, y + position.y, z + position.z) = block;
	}
}

BlockType& Chunk::getLocalBlockAt(int x, int y, int z) const
{
	return blocks[x + MAX_XZ * (y + MAX_Y * z)];
}

BlockType& Chunk::getLocalBlockAt(glm::vec3 vector) const
{
	return getLocalBlockAt(vector.x, vector.y, vector.z);
}

BlockType Chunk::getBlockTypeAt(int x, int y, int z)
{
	if (y < 0) return BlockType::AIR;

	if (!isBlockWithinBounds(x, z))
	{
		if (firstTime)
		{
			glm::vec3 location = toWorldCoordinates(x, y, z);
			BlockType* block = world->getBlockAt(location);
			if (block != nullptr) return *block;

		}

		int perlinY = getPerlinY(x, z);
		if (perlinY == y) return BlockType::GRASS;
		else if (y <= SEA_LEVEL && y > perlinY) return BlockType::WATER;
		else if (y < perlinY) return BlockType::STONE;
		else return BlockType::AIR;

	}
	return getLocalBlockAt(x, y, z);

}

BlockType Chunk::getBlockTypeAt(glm::vec3 vector)
{
	return getBlockTypeAt(vector.x, vector.y, vector.z);
}

bool Chunk::isBlockAir(const glm::vec3& pos, bool isBlockWater = false)
{
	if (pos.y < 0) return false;
	bool airCheck = getBlockTypeAt(pos) == BlockType::AIR;

	if (!isBlockWater) return airCheck;
	return getBlockTypeAt(pos) == BlockType::WATER || airCheck;
}

std::uint8_t Chunk::getFlags(int x, int y, int z)
{
	glm::vec3 positions[] = {
		{x,		y,		z - 1}, // Back
		{x,		y,		z + 1}, // Front
		{x - 1, y,		z	 }, // Left
		{x + 1, y,		z	 }, // Right
		{x,		y + 1,	z	 }, // Top
		{x,		y - 1,	z	 }, // Bottom
	};

	std::uint8_t flags{};

	for (int i = 0; i < 6; i++)
	{
		if (getBlockTypeAt(x, y, z) == BlockType::WATER)
		{
			if (getBlockTypeAt(positions[i]) == BlockType::AIR &&
				getBlockTypeAt(positions[i]) != BlockType::WATER)
				flags |= 1 << i;
			continue;
		}

		if (isBlockAir(positions[i], getBlockTypeAt(x, y, z) != BlockType::WATER))
			flags |= 1 << i;
	}

	return flags;
}

glm::vec3 Chunk::getVerticesPosition(const glm::vec3& blockPosition,
	const glm::vec3& verticesPositon)
{
	glm::fmat4 translationMatrix = glm::translate(glm::fmat4(1.0f), glm::vec3(
		static_cast<float>(blockPosition.x),
		static_cast<float>(blockPosition.y),
		static_cast<float>(blockPosition.z))
	);

	glm::vec4 vec = translationMatrix *
		glm::vec4(verticesPositon.x, verticesPositon.y, verticesPositon.z, 1.0f);

	return glm::vec3(vec.x, vec.y, vec.z);
}

void Chunk::addBlockToChunkMesh(std::vector<Vertex>& chunkMeshVertices, int x, int y, int z)
{
	std::vector<Vertex> blockVertices({});

	glm::vec3 pos = toWorldCoordinates(x, y, z);

	CubeBuilder::loadVertices(
		getFlags(x, y, z),
		blockVertices,
		Block::genTexCoords(getBlockAt(pos)),
		1.0f / 8.0f
	);

	for (auto& v : blockVertices)
	{
		v.position = getVerticesPosition(glm::vec3(x, y, z), v.position);
		chunkMeshVertices.push_back(v);
	}
}

glm::vec3 Chunk::toWorldCoordinates(int x, int y, int z)
{
	return glm::vec3(
		position.x * MAX_XZ + x, y, position.y * MAX_XZ + z
	);
}

glm::vec3 Chunk::toChunkCoordinates(int x, int y, int z)
{
	return glm::vec3(
		x - (getPosition().x * MAX_XZ),
		y,
		z - (getPosition().y * MAX_XZ)
	);;
}

int Chunk::getPerlinY(int x, int z)
{
	glm::vec3 pos = toWorldCoordinates(x, 0, z);
	return noise.GetNoise((float)pos.x, (float)pos.z) * 12 + 48;

}

bool Chunk::isBlockWithinBounds(int x, int z)
{
	return !(x > MAX_XZ - 1 || x < 0
		|| z > MAX_XZ - 1 || z < 0);
}
