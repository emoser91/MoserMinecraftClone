/*

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

//Windowized screen size
#define WIDTH 1920
#define HEIGHT 1080

int main(int argc, char** argv)
{
	display display(WIDTH, HEIGHT, "Minecraft Clone");
					SDL_Init(SDL_INIT_EVERYTHING); //if using SDL for more then windowing, dont do it here

					SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);//allocation of space for colors and sizing
					SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
					SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
					SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); //how transparent the color is
					SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); //total of previous bit amount: amount of data that opengl will allocate for a pixel
					SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16); //depth or z buffer (24 if needed)
					SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); //allocate more space for a second window
																 //Creation of a window for use with opengl content and make it resizable
					m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
					m_glContext = SDL_GL_CreateContext(m_window);

					//Start up of GLEW initilization and error checking
					GLenum status = glewInit();

					if (status != GLEW_OK)
					{
						std::cerr << "Glew failed to initialize" << std::endl;
					}

					m_isClosed = false; //flag for status of window

					//Backface culling of objects generated within the created window
					glEnable(GL_DEPTH_TEST);//addtional removing of back pixels on complicated surfaces - advanced version

					//Removing back sides of surfaces from showing through - basic version
					glEnable(GL_CULL_FACE);
					glCullFace(GL_BACK);


	//Manual method of defining vertex of mesh generated with triangles - single triangle
	//Each vertex is a single point of the triangle
	Vertex vertices[] =
	{
		Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0, 0)),
		Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1)),
		Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1, 0)),
	};

	unsigned int indices[] = { 0, 1, 2 };

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
				IndexedModel model;

				for (unsigned int i = 0; i < numVertices; i++)
				{
					model.positions.push_back(*vertices[i].GetPos());
					model.texCoords.push_back(*vertices[i].GetTexCoord());
					model.normals.push_back(*vertices[i].GetNormal());
				}

				for (unsigned int i = 0; i < numIndices; i++)
					model.indices.push_back(indices[i]);

				m_drawCount = model.indices.size();

				glGenVertexArrays(1, &m_vertexArrayObject);
				glBindVertexArray(m_vertexArrayObject);

				glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffer);

				glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffer[POSITION_VB]);
				glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);

				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

				glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffer[TEXCOORD_VB]);
				glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

				glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffer[NORMAL_VB]);
				glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);

				glEnableVertexAttribArray(2);
				glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffer[INDEX_VB]);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

				glBindVertexArray(0);

	Shader shader("./res/basicShader");
				m_program = glCreateProgram();
				m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER); //Vertex shader
				m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER); // Fragment shader

				//Add all shaders to the shader program
				for (unsigned int i = 0; i < NUM_SHADERS; i++)
				{
					glAttachShader(m_program, m_shaders[i]);
				}

				//Tells opengl what part of data to read in as what variable in the shader program
				glBindAttribLocation(m_program, 0, "position");
				glBindAttribLocation(m_program, 1, "texCoord");
				glBindAttribLocation(m_program, 2, "normal");

				//Link program for shaders
				glLinkProgram(m_program);
				CheckShaderError(m_program, GL_LINK_STATUS, true, "Error linking shader program");

				//Validate program for shaders
				glValidateProgram(m_program);
				CheckShaderError(m_program, GL_LINK_STATUS, true, "Invalid shader program");

				m_uniforms[TRANSFROM_U] = glGetUniformLocation(m_program, "transform");

	Texture textureCobbleStone("./res/cobblestone_minecraft.jpg");
				int width, height, numComponents;
				unsigned char* data = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);

				if (data == NULL)
					std::cerr << "Unable to load texture: " << fileName << std::endl;

				glGenTextures(1, &m_texture);
				glBindTexture(GL_TEXTURE_2D, m_texture);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

				stbi_image_free(data);

	Camera camera(glm::vec3(0.0f, 0.0f, -20.0f), 70.0f, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
				//init of varribles
				m_perspective = glm::perspective(fov, aspect, zNear, zFar);
				m_postion = pos;
				//future: create getter/setter for m_forward and m_up to allow change
				m_forward = glm::vec3(0, 0, 1); //hard coded forward, z axis
				m_up = glm::vec3(0, 1, 0); //hard coded up, y axis

	Transform transform;

	while (!display.IsClosed())
	{
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f); //display color (red,green,blue,alpha)
					glClearColor(r, g, b, a);
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Bind();
					glUseProgram(m_program);

		textureCobbleStone.Bind(0); //change texture
					assert(unit <= 0 && unit <= 31);

					glActiveTexture(GL_TEXTURE0 + unit);
					glBindTexture(GL_TEXTURE_2D, m_texture);

		transform.GetPos()->y = 0;
		transform.GetPos()->x = 0;
		transform.GetPos()->z = 0;

		shader.Update(transform, camera);
					glm::mat4 model = camera.GetViewProjection() * transform.GetModel();
					glUniformMatrix4fv(m_uniforms[TRANSFROM_U], 1, GL_FALSE, &model[0][0]);

		mesh.Draw();

		display.Update();//swap buffers and check for quit
					glBindVertexArray(m_vertexArrayObject);
					glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);
					glBindVertexArray(0);

	}

	return 0;

}

*/