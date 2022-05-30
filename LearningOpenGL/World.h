#ifndef WORLD_H
#define WORLD_H

#include<glm/glm.hpp>

#include<map>
#include<cmath>
#include<string>
#include<queue>

#include"Chunk.h"
#include"Texture.h"
#include"FastNoise.h"
#include"Shader.h"
#include"Block.h"
#include "Camera.h"
#include"Renderer.h"

class Chunk;
class Renderer;
enum class BlockType;

class World
{
private:
	using ChunkList_t = std::map<std::string, Chunk*>;
	using Location_t = glm::vec3;
	using ChunkLocation_t = glm::vec2;

	ChunkList_t chunks;
	std::queue<Chunk*> chunksQueue;
	FastNoiseLite noise;
	Texture* texture;

public:


	World(int seed);

	/**
	*
	* Returns a pointer to a chunk at a certain position
	* Return nullptr if no such chunk exists
	* 
	* @param position
	* Position that the chunk is located at
	* 
	*/
	Chunk* getChunkAt(const ChunkLocation_t& position);
	Chunk* getChunkAtWorld(const Location_t& position);
	BlockType* getBlockAt(Location_t position);
	void draw(Renderer& renderer);
	void updateChunks(const Location_t playerPosition);

	void breakBlockAt(Location_t position);

	void castRay(Camera& camera);
	const Texture* getTexture() const;
private:
	void loadChunk(const ChunkLocation_t& position);
	std::string vectorToString(const ChunkLocation_t& vec) const;

};

#endif // !WORLD_H



