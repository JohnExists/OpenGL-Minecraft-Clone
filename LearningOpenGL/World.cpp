#include "World.h"

World::World(int seed)
{
	noise = FastNoiseLite(seed);
	noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);

	this->texture = new Texture("Textures/atlas.png");
	texture->setScalingFilter(GL_NEAREST, GL_NEAREST);
	texture->setWrapAround(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
	loadChunk(glm::vec2(0, 0));
}

Chunk* World::getChunkAt(const ChunkLocation_t& vectorPosition)
{
	std::string position = vectorToString(vectorPosition);
	Chunk* chunk = nullptr;
	if (chunks.count(position)) chunk = chunks.at(position);

	return chunk;
}

Chunk* World::getChunkAtWorld(const Location_t& position)
{
	ChunkLocation_t chunkPosition = glm::vec2(
		floor(position.x / 16.0f),
		floor(position.z / 16.0f)
	);

	return getChunkAt(chunkPosition);
}

BlockType* World::getBlockAt(Location_t position)
{
	Chunk* chunk = getChunkAtWorld(position);
	if (chunk == nullptr) return nullptr;
	return &chunk->getBlockAt(position);
}


void World::draw(Renderer& renderer)
{
	texture->useSlot(renderer.getShader(ShaderType::DEFAULT_SHADER), "texture1", 0);

	for (auto& [position, chunk] : chunks) chunk->draw(renderer, 0);
	for (auto& [position, chunk] : chunks) chunk->draw(renderer, 1);
}

void World::updateChunks(Location_t playerPosition)
{
	static const int RENDER_DISTANCE = 4;

	ChunkLocation_t playerChunk = getChunkAtWorld(playerPosition)->getPosition();

	for (int i = playerChunk.x - RENDER_DISTANCE; i < playerChunk.x + RENDER_DISTANCE; i++)
	{
		for (int j = playerChunk.y - RENDER_DISTANCE; j < playerChunk.y + RENDER_DISTANCE; j++)
		{
			loadChunk(glm::vec2(i, j));
		}
	}

	if (!chunksQueue.empty())
	{
		chunksQueue.front()->loadMesh();
		chunksQueue.pop();
	}

}

void World::breakBlockAt(Location_t position)
{
	Chunk* chunk = getChunkAtWorld(position);
	chunk->breakBlockAt(position);

	glm::vec3 pos(
		position.x - (chunk->getPosition().x * Chunk::MAX_XZ),
		position.y,
		position.z - (chunk->getPosition().y * Chunk::MAX_XZ)
	);;

	glm::vec2 other;

	 if(pos.x < 1) other = chunk->getPosition() + glm::vec2(-1, 0);
	 else if(pos.x > Chunk::MAX_XZ - 1) other = chunk->getPosition() + glm::vec2(1, 0);
	 else if(pos.z < 1) other = chunk->getPosition() + glm::vec2(0, -1);
	 else if(pos.z > Chunk::MAX_XZ - 1) other = chunk->getPosition() + glm::vec2(0, 1);

	 Chunk* otherChunk = getChunkAt(other);
	 if (otherChunk != nullptr) otherChunk->loadMesh();

}

void World::castRay(Camera& camera)
{
	Location_t castFrom = camera.getPosition();
	glm::vec3 castTo = camera.getDirectionVector();

	for (float rayLength = 0; rayLength <= 6; rayLength+= 0.01)
	{
		Location_t rayLocation = castFrom + (castTo * rayLength);
		BlockType* block = &getChunkAtWorld(rayLocation)->getBlockAt(rayLocation);

		if (*block != BlockType::AIR && *block != BlockType::WATER)
		{
			breakBlockAt(rayLocation);
			return;
		}
	}
}

const Texture* World::getTexture() const
{
	return texture;
}

void World::loadChunk(const ChunkLocation_t& vectorPosition)
{
	std::string positon = vectorToString(vectorPosition);
	if (chunks.count(positon)) return;

	Chunk* chunk = new Chunk(vectorPosition, this, noise);

	chunks.insert({positon, chunk});
	chunksQueue.push(chunk);
}

std::string World::vectorToString(const ChunkLocation_t& vec) const
{
	return std::to_string(vec.x) + ':' +
		std::to_string(vec.y);
}