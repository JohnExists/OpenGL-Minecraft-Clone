#ifndef CHUNK_H
#define CHUNK_H

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<vector>
#include<array>
#include<string>
#include<unordered_map>
#include<algorithm>

#include"Random.h"
#include"Texture.h"
#include"FastNoise.h"
#include"Block.h"
#include"World.h"
#include"Mesh.h"
#include"Decoration.h"
#include"Renderer.h"
#include"World.h"

class Block;
class Renderer;
class World;
enum class BlockType;
enum class Decoration;

class Chunk
{
private:

	Mesh* mesh = nullptr;
	Mesh* transparent = nullptr;
	glm::vec2 position;
	BlockType* blocks;
	Texture* texture;
	World* world;
	FastNoiseLite& noise;

	bool firstTime = false;

public:

	static const int MAX_XZ = 16;
	static const int MAX_Y	= 256;

	static const int SEA_LEVEL = 40;

	Chunk(const glm::vec2& position, World* world, FastNoiseLite& fnl);
	~Chunk();

	void draw(Renderer& renderer, int meshToDraw);

	void loadMesh();

	BlockType& getBlockAt(glm::vec3& positon);
	void breakBlockAt(glm::vec3& position);

	const glm::vec2& getPosition() const;

private:
	void loadMatrix(Renderer& renderer);
	void loadBlocks();
	void loadDecoration(Decoration decoration, int x, int y, int z);

	BlockType& getLocalBlockAt(int x, int y, int z) const;
	BlockType& getLocalBlockAt(glm::vec3 position) const;

	BlockType getBlockTypeAt(int x, int y, int z);
	BlockType getBlockTypeAt(glm::vec3 position);

	bool isBlockAir(const glm::vec3& position, bool isBlockWater);

	std::uint8_t getFlags(int x, int y, int z);
	glm::vec3 getVerticesPosition(const glm::vec3& blockPosition, const glm::vec3& positon);
	void addBlockToChunkMesh(std::vector<Vertex>& chunkMeshVertices,
		int x, int y, int z);

	glm::vec3 toWorldCoordinates(int x, int y, int z);
	glm::vec3 toChunkCoordinates(int x, int y, int z);

	int getPerlinY(int x, int z);
	bool isBlockWithinBounds(int x, int z);


};


#endif // !CHUNK_H