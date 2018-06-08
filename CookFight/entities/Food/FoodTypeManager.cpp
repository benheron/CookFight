#include "FoodTypeManager.h"

FoodTypeManager::FoodTypeManager(std::string filePath)
{
	loadFoodData(filePath);
}

FoodTypeManager::~FoodTypeManager()
{

}

void FoodTypeManager::loadFoodData(std::string filePath)
{
	//File loading message
	printf("Loading food data \n");

	//Open the file using a ifstream
	std::ifstream file(filePath);

	//If the file successfully opens
	if (file.is_open())
	{
		//Load the number of different spritesheets.
		std::string textureFilePath;
		int numFood;
		int numFoodStates;
		glm::vec2 dimensions;
		
		

		file >> textureFilePath;
		file >> numFood;

		file >> numFoodStates;

		file >> dimensions.x;
		file >> dimensions.y;

		foodDimens = glm::vec3(dimensions, 0);

		foodTexture = new Texture(textureFilePath);
		glm::vec2 foodTextureDimens = foodTexture->getOrigDimens();


		

		std::unordered_map<std::string, AnimationType*> animations;


		for (int i = 0; i < numFoodStates; i++)
		{
			std::string foodState;
			file >> foodState;

			foodStates.push_back(foodState);
		}


		for (int i = 0; i < numFood; i++)
		{
			std::string foodName;

			file >> foodName;

			foodTypeNames.push_back(foodName);



			////////////////////////////////////////////////////////////////
			////////--CHANGE TO HAVE MORE STATES - IE PREPARED FOOD--////////
			////////////////////////////////////////////////////////////////
			
			std::vector<Frame*> frames;
			std::unordered_map<std::string, glm::vec2> uvOffsets;

			for (int j = 0; j < numFoodStates; j++)
			{

				glm::vec2 spritePos;
				spritePos.x = j*dimensions.x;
				spritePos.y = i*dimensions.y;

				//glm::vec2 uvOffset = (0.5f + spritePos) / foodTextureDimens;
				glm::vec2 uvOffset = spritePos / foodTextureDimens;
				glm::vec2 uvDimens = dimensions / foodTextureDimens;
				
				uvOffsets[foodStates[j]] = uvOffset;


				Frame* fr = new Frame(foodTexture, uvOffset, uvDimens, dimensions);
				frames.push_back(fr);

			}

			AnimationType *a = new AnimationType(foodTypeNames[i], frames);
			animations[foodTypeNames[i]] = a;


			glm::vec2 position;
			position.x = 0;
			position.y = i * dimensions.y;

			//glm::vec2 uvOffset = position / foodTextureDimens;
			glm::vec2 uvDimens = dimensions / foodTextureDimens;

			FoodType* ft = new FoodType(foodTexture, foodName, uvOffsets, uvDimens);
			foodTypes[foodName] = ft;
			foodTypesVector.push_back(ft);

		}

		foodSpriteSheet = new SpriteSheet("Food", foodTexture, animations);


		//Close the file
		file.close();

		//File loaded message
		printf("Food data loaded. \n");
	}
	else
	{
		//Error message
		printf("Unable to open file : %s \n", filePath);
	}
}

FoodType* FoodTypeManager::getFoodType(std::string foodTypeID)
{
	return foodTypes[foodTypeID];
}

std::unordered_map<std::string, FoodType*> FoodTypeManager::getFoodTypes() {
	return foodTypes;
}

std::vector<FoodType*> FoodTypeManager::getFoodTypesVector() {
	return foodTypesVector;
}

Texture* FoodTypeManager::getFoodTypeTexture(std::string foodTypeID)
{
	return foodTexture;
}