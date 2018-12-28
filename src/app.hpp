#ifndef KNU_APP
#define KNU_APP

#include <chrono>
#include "knu/window2.hpp"
#include <knu/gl_utility.hpp>
#include <knu/mathlibrary6.hpp>

#ifdef WIN32
#define MAJOR_VERSION 4
#define MINOR_VERSION 5
#endif
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#define MAJOR_VERSION 3         // In sdl, for the time being, the only way to request a 4.1 context is
#define MINOR_VERSION 2         // to request a 3.2 context on mac
#endif

using KNU_TIME = std::chrono::duration<double, std::ratio<1, 1000>>;

void APIENTRY debug_output1(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const char *message, const void *userParam);
class App
{
	Window window;
	std::chrono::steady_clock::time_point current_time, last_time;
	float clear_color[4];
	float clear_depth;
    knu::math::matrix4f perspective_matrix;
	knu::math::matrix4f orthographic_matrix;

private:
	void general_setup();
	void draw_scene();
    void process_inputs();
	void update(KNU_TIME seconds);
	void load_shaders();
	void initialize_graphics();
	void process_messages(SDL_Event *event);
	void resize(int w, int h);
    void get_window_size(int &w, int &h);
	int window_width();
	int window_height();

public:
	App();
	int run();
};

#endif
