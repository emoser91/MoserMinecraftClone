// OpenGLProject.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <SDL2/SDL.h>
#include "display.h"
#include <GL/glew.h>
#include "mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"
#include <vector>
#include "Timer.h"
#include "Render.h"

//future: set up get hight and get width functions
//Windowized screen size
#define WIDTH 1920
#define HEIGHT 1080

int  windowWidth = 0x780;
int  windowHeight = 0x438;

//function prototypes
void DoMovement();
void DrawErrorCheck(std::string);

//need to pass camera into DoMovement instead
Camera camera(glm::vec3(0.0f, 0.0f, -20.0f), 70.0f, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

int main(int argc, char** argv)
{
	display display(WIDTH, HEIGHT, "Minecraft Clone");

	//Manual method of defining vertex of mesh generated with triangles - single triangle
	//Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0, 0)),
						  //Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1)),
						  //Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1, 0)), };

	//unsigned int indices[] = { 0, 1, 2 };

	//Cube Mesh for Grass Texture
	Vertex verticesGrass[] =
	{
		Vertex(glm::vec3(-1, -1, -1), glm::vec2(0.5, 0.66),   glm::vec3(0, 0, -1)), 
		Vertex(glm::vec3(-1, 1, -1),  glm::vec2(0.5, 0.33),   glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(1, 1, -1),   glm::vec2(0.25, 0.33),  glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(1, -1, -1),  glm::vec2(0.25, 0.66),  glm::vec3(0, 0, -1)),

		Vertex(glm::vec3(-1, -1, 1),  glm::vec2(0.5, 0.66),   glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(-1, 1, 1),   glm::vec2(0.5, 0.33),   glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, 1, 1),    glm::vec2(0.25, 0.33),  glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, -1, 1),   glm::vec2(0.25, 0.66),  glm::vec3(0, 0, 1)),

		Vertex(glm::vec3(-1, -1, -1), glm::vec2(0.25, 0.66),  glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(-1, -1, 1),  glm::vec2(0.25, 1),     glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(1, -1, 1),   glm::vec2(0.5, 1),      glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(1, -1, -1),  glm::vec2(0.5, 0.66),   glm::vec3(0, -1, 0)),
													          
		Vertex(glm::vec3(-1, 1, -1),  glm::vec2(0.25, 0),     glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(-1, 1, 1),   glm::vec2(0.25, 0.33),  glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, 1, 1),    glm::vec2(0.5, 0.33),   glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, 1, -1),   glm::vec2(0.5, 0),      glm::vec3(0, 1, 0)),
													          
		Vertex(glm::vec3(-1, -1, -1), glm::vec2(0.25, 0.66),  glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(-1, -1, 1),  glm::vec2(0.5, 0.66),   glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(-1, 1, 1),   glm::vec2(0.5, 0.33),   glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(-1, 1, -1),  glm::vec2(0.25, 0.33),  glm::vec3(-1, 0, 0)),
													          
		Vertex(glm::vec3(1, -1, -1),  glm::vec2(0.25, 0.66),  glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(1, -1, 1),   glm::vec2(0.5, 0.66),   glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(1, 1, 1),    glm::vec2(0.5, 0.33),   glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(1, 1, -1),   glm::vec2(0.25, 0.33),  glm::vec3(1, 0, 0)),
	};

	Vertex verticesCube[] =
	{
		Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 0),  glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(-1, 1, -1),  glm::vec2(0, 0),  glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(1, 1, -1),   glm::vec2(0, 1),  glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(1, -1, -1),  glm::vec2(1, 1),  glm::vec3(0, 0, -1)),

		Vertex(glm::vec3(-1, -1, 1),  glm::vec2(1, 0),  glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(-1, 1, 1),   glm::vec2(0, 0),  glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, 1, 1),    glm::vec2(0, 1),  glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, -1, 1),   glm::vec2(1, 1),  glm::vec3(0, 0, 1)),

		Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 0),  glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(-1, -1, 1),  glm::vec2(0, 0),  glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(1, -1, 1),   glm::vec2(0, 1),  glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(1, -1, -1),  glm::vec2(1, 1),  glm::vec3(0, -1, 0)),

		Vertex(glm::vec3(-1, 1, -1),  glm::vec2(1, 0),  glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(-1, 1, 1),   glm::vec2(0, 0),  glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, 1, 1),    glm::vec2(0, 1),  glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, 1, -1),   glm::vec2(1, 1),  glm::vec3(0, 1, 0)),

		Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 0),  glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(-1, -1, 1),  glm::vec2(0, 0),  glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(-1, 1, 1),   glm::vec2(0, 1),  glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(-1, 1, -1),  glm::vec2(1, 1),  glm::vec3(-1, 0, 0)),

		Vertex(glm::vec3(1, -1, -1),  glm::vec2(1, 0),  glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(1, -1, 1),   glm::vec2(0, 0),  glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(1, 1, 1),    glm::vec2(0, 1),  glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(1, 1, -1),   glm::vec2(1, 1),  glm::vec3(1, 0, 0)),
	};


	unsigned int indices[] = 
	{ 
		0, 1, 2,
		0, 2, 3,

		6, 5, 4,
		7, 6, 4,

		10, 9, 8,
		11, 10, 8,

		12, 13, 14,
		12, 14, 15,

		16, 17, 18,
		16, 18, 19,

		22, 21, 20,
		23, 22, 20
	};

	Mesh meshCube(verticesCube, sizeof(verticesCube) / sizeof(verticesCube[0]), indices, sizeof(indices) / sizeof(indices[0]) );
	Mesh meshGrass(verticesGrass, sizeof(verticesGrass) / sizeof(verticesGrass[0]), indices, sizeof(indices) / sizeof(indices[0]));

	//Mesh generation with the use of an imported .obj file
	//Mesh mesh2("./res/monkey3.obj");
	//Mesh mesh2("./res/simpleCube.obj");

	//Shaders add color to generated Meshes
	//Shader shader("./res/basicShader");

	//Textures add textures from a .jpg image over the top of a mesh
	Texture textureCobbleStone("./res/cobblestone_minecraft.jpg");
	Texture textureGrass("./res/grass.jpg");
	Texture textureDirt("./res/dirt_minecraft.jpg");
	
	Transform transform;

	Timer gameTime;

	float counter = 0.0f;

	while (!display.IsClosed())
	{

		gameTime.TimerStart();

		display.Clear(0.0f, 0.15f, 0.3f, 1.0f); //display color (red,green,blue,alpha)

		//transformations
		/*
		//float sinCounter = sinf(counter);
		//float absSinCounter = abs(sinCounter);

		//transform.GetPos()->x = sinf(counter);
		//transform.GetRot()->z = counter;
		//transform.GetScale()->x = absSinCounter;
		//transform.GetScale()->y = absSinCounter;

		//rotate and flip transformations
		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);

		//transform.GetPos()->x = sinCounter;
		//transform.GetPos()->z = cosCounter;
		//transform.GetRot()->x = counter * 100;
		//transform.GetRot()->y = counter * 100;
		//transform.GetRot()->z = counter * 100;

		//camera movement
		//camera.MoveForward(0.001f);
		//camera.MoveRight(0.001f);
		//camera.MoveLeft(0.001f);
		//camera.Pitch(0.0001f);
		//camera.RotateY(0.0001f);

		//transform.GetPos()->x = 0;
		*/

		/*
		//creation of 10x10x2 cube of single cubes
		for (int countZ = 0; countZ < 10; countZ++)
		{
			for (int countY = 0; countY < 2; countY++)
			{
				for (int countX = 0; countX < 10; countX++)
				{
					transform.GetPos()->y = -countY - (1.0f * countY);
					transform.GetPos()->x = countX + (1.0f * countX);
					transform.GetPos()->z = countZ + (1.0f * countZ);
					shader.Update(transform, camera);
					mesh.Draw();
				}
			}
		}
		*/

		//Render cube Grass
		Shader shader("./res/BasicShader/basicShader");
		shader.Bind();
		textureGrass.Bind(0);
		transform.GetPos()->y = 0;
		transform.GetPos()->x = 0;
		transform.GetPos()->z = 0;
		shader.Update(transform, camera);
		meshGrass.Draw();

		DrawErrorCheck("Block Error");
		
		//Render cube Cobble
		textureCobbleStone.Bind(0);
		transform.GetPos()->y = 0;
		transform.GetPos()->x = 3;
		transform.GetPos()->z = 0;
		shader.Update(transform, camera);
		meshCube.Draw();

		DrawErrorCheck("Block Error");

		//Render cube Dirt
		textureDirt.Bind(0);
		transform.GetPos()->y = 0;
		transform.GetPos()->x = 6;
		transform.GetPos()->z = 0;
		shader.Update(transform, camera);
		meshCube.Draw();

		DrawErrorCheck("Block Error");

		//Render Crosshairs
		Shader shader2("./res/CrosshairShader/crossShader");
		shader2.Bind();
		textureCobbleStone.Bind(0);
		transform.GetPos()->y = 0;
		transform.GetPos()->x = 0;
		transform.GetPos()->z = 0;
		shader2.Update(transform, camera);
		meshCube.DrawCrossHair();

		DrawErrorCheck("Crosshair Error");
		
		DoMovement();

		display.Update();//swap buffers and check for quit
		SDL_Delay(20);

		//gameTime.TimerEnd("End time"); //end time for debugging
		gameTime.TimerClock(); //display game timer

	}//while

	//std::cout << "Hello World!" << std::endl;
    return 0;
}//int main

//Prints out any draw errors for debugging
void DrawErrorCheck(std::string string)
{
	GLenum error = glGetError();
	if (error != 0)
		std::cout << string << ": " << error << std::endl;
}

void DoMovement()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		// Mouse Movement
		if ((event.type == SDL_MOUSEMOTION) && (event.button.button == SDL_BUTTON_LEFT))
		{
			/* If the mouse is moving to the left */
			if (event.motion.xrel < 0)
			{
				//camera.MoveLeft(0.1f);
				camera.RotateY(-0.02f);
			}
			/* If the mouse is moving to the right */
			else if (event.motion.xrel > 0)
			{
				//camera.MoveRight(0.1f);
				camera.RotateY(0.02f);
			}
			/* If the mouse is moving up */
			else if (event.motion.yrel < 0)
			{
				//camera.MoveUp(0.1f);
				camera.Pitch(0.02f);
			}
			/* If the mouse is moving down */
			else if (event.motion.yrel > 0)
			{
				//camera.MoveDown(0.1f);
				camera.Pitch(-0.02f);
			}
		}
		if (event.type == SDL_MOUSEWHEEL)
		{
			if (event.wheel.y == 1) // scroll up
			{
				camera.MoveForward(1.0f);
			}
			else if (event.wheel.y == -1) // scroll down
			{
				camera.MoveForward(-1.0f);
			}
		}

		// We are only worried about SDL_KEYDOWN and SDL_KEYUP events 
		switch (event.type)
		{

		case SDL_KEYDOWN:
			//std::cout << "KeyPressed" << std::endl;
			// Check the SDLKey values and move change the coords 
			switch (event.key.keysym.sym)
			{
			case SDLK_a:
				camera.MoveRight(1.0f);
				break;
			case SDLK_d:
				camera.MoveLeft(1.0f);
				break;
			case SDLK_w:
				camera.MoveForward(1.0f);
				break;
			case SDLK_s:
				camera.MoveForward(-1.0f);
				break;
			case SDLK_q:
				camera.RotateY(-0.01f);
				break;
			case SDLK_e:
				camera.RotateY(0.01f);
				break;
			case SDLK_SPACE:
				camera.MoveUp(1.0f);
				break;
			case SDLK_LSHIFT:
				camera.MoveDown(1.0f);
				break;
			default:
				break;
			}

		case SDL_KEYUP:
			break;

			break;
		}
	}
}
