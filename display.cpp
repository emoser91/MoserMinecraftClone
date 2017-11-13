#include "display.h"
#include <iostream>
#include <GL/glew.h>
#include "Camera.h"

//Constructor method handles all creation of window and backface culling
display::display(int width, int height, const std::string& title)
{
	//std::cout << "Constructor" << std::endl;
	SDL_Init(SDL_INIT_EVERYTHING); //if using SDL for more then windowing, dont do it here

	//allocation of space for colors and sizing
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
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

	//addtional removing of back pixels on complicated surfaces - advanced version
	glEnable(GL_DEPTH_TEST);

	//Removing back sides of surfaces from showing through - basic version
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

 // Distructor handles all shut down  of window created
display::~display()
{
	//std::cout << "Destructor" << std::endl;
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

//Method that returns if the window is closed or not
bool display::IsClosed()
{
	return m_isClosed;
}

//Method that creates background color of created window
void display::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//Method that swaps buffers 
void display::Update()
{
	SDL_GL_SwapWindow(m_window);

	SDL_Event e;

	//Loop to look for quit button clicked
	while(SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			m_isClosed = true;
	}
}