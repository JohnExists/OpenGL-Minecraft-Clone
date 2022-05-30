#include"Decoration.h"

decor::positions_t* decor::loadTree()
{
	static decor::positions_t* blockPositions = nullptr;

	if (blockPositions == nullptr)
	{
		blockPositions = loadFromFile("Tree.pos");
	}

	return blockPositions;
}

decor::positions_t decor::load(Decoration decoration)
{

	switch (decoration)
	{
	case Decoration::TREE: return *loadTree();
	}

}

decor::positions_t* decor::loadFromFile(const char* filePath)
{
	std::ifstream file(filePath);
	if (!file.is_open()) return nullptr;

	decor::positions_t* blockPositions = new decor::positions_t();

	while (!file.eof()) // While not end of file
	{
		char line[128];
		std::string delimiter = "|";

		file.getline(line, 128);
		std::string lineAsString(line);

		size_t pos = 0;
		int counter = 0;
		int tokens[4]{};
		std::string token;
		while (((pos = lineAsString.find(delimiter)) != std::string::npos) &&
			lineAsString.size() != 0) {
			tokens[counter] = std::stoi(lineAsString.substr(0, pos));

			lineAsString.erase(0, pos + delimiter.length());
			counter++;
		}


		if (tokens[1] == 0 && tokens[2] == 0 && tokens[3] == 0) continue;

		blockPositions->insert(std::make_pair(
			static_cast<BlockType>(tokens[0]), glm::vec3(tokens[1], tokens[2], tokens[3])
		));
	}

	return blockPositions;
}
