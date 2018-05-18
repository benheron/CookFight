#include "SpriteSheetManager.h"

SpriteSheetManager::SpriteSheetManager(std::string filePath) 
{
	loadSpriteSheet(filePath);
}

SpriteSheetManager::~SpriteSheetManager()
{

}


void SpriteSheetManager::loadSpriteSheet(std::string filePath)
{
	printf("Loading spritesheet data: %s \n", filePath.c_str());


	std::ifstream spriteSheetData(filePath);
	std::unordered_map<std::string, AnimationType*> animations;

	if (spriteSheetData.is_open())
	{
		std::string spriteSheetPath;
		std::string spriteSheetName;

		int numAnimations;


		spriteSheetData >> spriteSheetPath;
		spriteSheetData >> spriteSheetName;

		spriteSheetData >> numAnimations;


		Texture* spriteSheetTexture = new Texture(spriteSheetPath);


		for (int i = 0; i < numAnimations; i++)
		{
			std::string animationID;
			int numFrames;

			spriteSheetData >> animationID;
			spriteSheetData >> numFrames;

			std::vector<Frame*> frames;

			for (int j = 0; j < numFrames; j++)
			{
				glm::vec2 framePos;
				glm::vec2 frameDimens;

				spriteSheetData >> framePos.x;
				spriteSheetData >> framePos.y;

				spriteSheetData >> frameDimens.x;
				spriteSheetData >> frameDimens.y;


				glm::vec2 endFramePos = framePos + frameDimens;


				glm::vec2 uvOffset = (framePos) / spriteSheetTexture->getOrigDimens();
				glm::vec2 uvDimens = (frameDimens) / spriteSheetTexture->getOrigDimens();

				




				//stops texture bleeding
				//forces corodinates to be inside pixel boundaries rather than on the edge
				//uvOffset += glm::vec2(0.0001f, 0.0001f);
			//	uvDimens -= glm::vec2(0.0002f, 0.0002f);





				Frame* fr = new Frame(spriteSheetTexture, uvOffset, uvDimens, frameDimens);
				frames.push_back(fr);

			}
			AnimationType *a = new AnimationType(animationID, frames);
			animations[animationID] = a;


		}

		SpriteSheet* ss = new SpriteSheet(spriteSheetName, spriteSheetTexture, animations);

		spriteSheets[spriteSheetName] = ss;

		spriteSheetData.close();


		printf("Spritesheet data loaded: %s \n", filePath.c_str());
	}
	else {
		printf("Error loading spritesheet data: %s \n", filePath.c_str());
	}

}

