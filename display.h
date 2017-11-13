/*
Display Class 


*/

#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>//used for creation of window
#include <string>

class display
{
	public:
		display(int width, int height, const std::string& title);

		void Clear(float r, float g, float b, float a);
		void Update();
		bool IsClosed();

		virtual ~display();

	protected:
	private:
		display(const display& other) {}//unused
		void operator=(const display& other) {}//unused

		SDL_Window* m_window;
		SDL_GLContext m_glContext;
		bool m_isClosed;
};
#endif //DISPLAY_H

