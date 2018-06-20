#include "Renderer.h"

Renderer::Renderer(Platform* platform, ResourceManager * rm) : platform(platform), rm(rm)
{
	if (shaderProg.loadProgram("Shaders/VertShader.vert", "Shaders/FragShader.frag"))
	{

		glClearColor(0.3f, 0.3f, 0.3f, 0.0f);

		// Enable depth test
		glDisable(GL_DEPTH_TEST);

		

		mvpID = glGetUniformLocation(shaderProg.getProgramID(), "mvp");




		blendColourID = glGetUniformLocation(shaderProg.getProgramID(), "blendColour");


		offsetUVID = glGetUniformLocation(shaderProg.getProgramID(), "offsetUV");


		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);

		

		textureID = glGetUniformLocation(shaderProg.getProgramID(), "textureSampler");

	}
	
	if (txtShader.loadProgram("Shaders/TextVertShader.vert", "Shaders/TextFragShader.frag"))
	{
		Text2DUniformID = glGetUniformLocation(txtShader.getProgramID(), "myTextureSampler");
	}

}

Renderer::~Renderer()
{

}

void Renderer::render(std::vector<State*> states)
{
	//std::vector<Entity*> entities = em->getEntities();

	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaderProg.getProgramID());

	for (int j = 0; j < states.size(); j++)
	{
		Camera *c = states[j]->getCamera();

		

		std::vector<Entity*> entities = states[j]->getRenderables();


		glm::mat4 projMat = glm::ortho(0.0f, platform->getRenderSize().x, platform->getRenderSize().y, 0.0f, 3.0f, -3.0f);

		glm::mat4 viewMat = states[j]->getCamera()->getCamMatrix();
			

		renderCount = 0;
		//loop through all entities
		
		addToScreen(entities, projMat, viewMat);





		//loop through all entities
		/*for (int i = 0; i < entities.size(); i++)
		{
			std::vector<Model*> ms = entities[i]->getModels();

			//only render if said should render
			if (entities[i]->getShouldRender())
			{

				//loop through all models within an entity
				for (int k = 0; k < ms.size(); k++)
				{
					glm::mat4 modelMat = entities[i]->getModelMatrix(k);

					glm::mat4 mvp = projMat*viewMat*modelMat;

					glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);


					glm::vec4 bc = entities[i]->getBlendColour();

					glUniform4fv(blendColourID, 1, &bc[0]);

					//vertices buffer
					GLuint vertexBuffer = ms[k]->getVertexBuffer2D();

					//UV buffer
					GLuint uvBuffer = ms[k]->getUVBuffer();

					glm::vec2 uvOffset = entities[i]->getTextureUVOffset();


					//= glm::vec2(0);

					glUniform2fv(offsetUVID, 1, &uvOffset[0]);


					GLsizei indexSize = ms[k]->getVertices2D().size();

					GLuint tID = entities[i]->getTexture(k)->getTextureID();


					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, tID);

					glUniform1i(textureID, 0);

					//lastTextID = tID;







					glEnableVertexAttribArray(0);
					glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
					glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);


					glEnableVertexAttribArray(1);
					glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
					glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

					glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

					// Draw call
					glDrawArrays(GL_TRIANGLES, 0, indexSize);

					glDisable(GL_BLEND);

					//disable vertex position
					glDisableVertexAttribArray(0);
					glDisableVertexAttribArray(1);
				}
			}
		}*/



	}
	







	//unbind program
	glUseProgram(NULL);





}

void Renderer::renderScreenSpace(std::vector<State *> states)
{
	

	glUseProgram(shaderProg.getProgramID());

	for (int j = 0; j < states.size(); j++)
	{
		Camera *c = states[j]->getCamera();



		std::vector<Entity*> entities = states[j]->getHUDElements();


		glm::mat4 projMat = glm::ortho(0.0f, platform->getRenderSize().x, platform->getRenderSize().y, 0.0f, 3.0f, -3.0f);

		glm::mat4 viewMat = glm::mat4(1);

		//loop through all entities
		
		addToScreen(entities, projMat, viewMat);
		

			

		


	}



//	printf("Num obj render: %i \n", renderCount);




	//unbind program
	glUseProgram(NULL);


}

void Renderer::renderFrameRate(Text* frameRateText)
{
	GLuint txtProgramId = txtShader.getProgramID();

	glUseProgram(txtProgramId);

	
	Model* m = frameRateText->getModel();
	//vertices buffer
	GLuint vertexBuffer = m->getVertexBuffer2D();

	//normal buffer
	GLuint uvBuffer = m->getUVBuffer();


	GLsizei indexSize = m->getVertices2D().size();

	GLuint fontID = frameRateText->getFontTexture()->getTextureID();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, fontID);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(Text2DUniformID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Draw call
	glDrawArrays(GL_TRIANGLES, 0, indexSize);

	glDisable(GL_BLEND);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}


void Renderer::addToScreen(std::vector<Entity*> entities, glm::mat4 projMat, glm::mat4 viewMat)
{

	for (int i = 0; i < entities.size(); i++)
	{
	
		std::vector<Model*> ms = entities[i]->getModels();

		
		if (entities[i]->getShouldRender())
		{
			for (int k = 0; k < ms.size(); k++)
			{
				renderCount++;
				glm::mat4 modelMat = entities[i]->getModelMatrix(k);

				glm::mat4 mvp = projMat*viewMat*modelMat;

				glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);


				glm::vec4 bc = entities[i]->getBlendBrightnessColour();

				glUniform4fv(blendColourID, 1, &bc[0]);

				//vertices buffer
				GLuint vertexBuffer = ms[k]->getVertexBuffer2D();

				//UV buffer
				GLuint uvBuffer = ms[k]->getUVBuffer();

				glm::vec2 uvOffset = entities[i]->getTextureUVOffset();


				//= glm::vec2(0);

				glUniform2fv(offsetUVID, 1, &uvOffset[0]);


				GLsizei indexSize = ms[k]->getVertices2D().size();

				GLuint tID = entities[i]->getTexture(k)->getTextureID();


				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, tID);

				glUniform1i(textureID, 0);

				glEnableVertexAttribArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);


				glEnableVertexAttribArray(1);
				glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				// Draw call
				glDrawArrays(GL_TRIANGLES, 0, indexSize);

				glDisable(GL_BLEND);

				//disable vertex position
				glDisableVertexAttribArray(0);
				glDisableVertexAttribArray(1);

			}

			//render children
			std::vector<Entity*> entChildren = entities[i]->getChildren();
			if (entChildren.size() > 0)
			{
				addToScreen(entChildren, projMat, viewMat);
			}
		}
		
		

	}




}