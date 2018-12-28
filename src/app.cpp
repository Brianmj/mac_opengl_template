#include "app.hpp"
#include <string>
#include <iostream>

using namespace knu::math;

void App::general_setup()
{
	load_shaders();
	glEnable(GL_DEPTH_TEST);


}

void App::draw_scene()
{
	glClearBufferfv(GL_COLOR, 0, clear_color);
	glClearBufferfv(GL_DEPTH, 0, &clear_depth);
    

}

void App::process_inputs()
{
    int returned_keys_count = 0;
    auto ptr = SDL_GetKeyboardState(&returned_keys_count);
    std::vector<std::uint8_t> keyboard_state(ptr, ptr + returned_keys_count);
    
    
}

void App::update(KNU_TIME seconds)
{

}

void App::load_shaders()
{

}

void App::process_messages(SDL_Event *event)
{
	switch (event->type)
	{
	case SDL_WINDOWEVENT:
		{
			switch (event->window.event)
			{
			case SDL_WINDOWEVENT_RESIZED:
				{
					resize(event->window.data1, event->window.data2);
				}break;

			case SDL_WINDOWEVENT_CLOSE:
				{
					window.set_quit(true);
				}break;
			}
		}break;

	case SDL_KEYDOWN:
		{
			if (event->key.keysym.sym == SDLK_ESCAPE)
				window.set_quit(true);
            
		}break;
            
        case SDL_QUIT:
        {
            window.set_quit(true);
        }break;
	
	}
}

void App::resize(int w, int h)
{
	glViewport(0, 0, w, h);
    
    float half_width = w / 2.0f;
    float half_height = h / 2.0f;
    
    float left = -half_width;
    float right = half_width;
    
    float bottom = -half_height;
    float top = half_height;
    
    float near = 0.10f;
    float far = 100.0f;
    
    orthographic_matrix = matrix4f{ 2.0f / (right - left), 0.0f, 0.0f, 0.0f,
                                    0.0f, 2.0f / (top - bottom), 0.0f, 0.0f,
                                    0.0f, 0.0f, 2.0f / (near - far), 0.0f,
        (left + right)/(left - right), (bottom + top) / (bottom - top), (near + far) / (far - near), 1.0f};
    
    perspective_matrix = matrix4f { (2.0f * near) / (right - left), 0.0f, 0.0f, 0.0f,
        0.0f, (2.0f * near) / (top - bottom), 0.0f, 0.0,
        (right + left) / (right - left), (top + bottom) / (top - bottom), (near + far) / (near - far), -1.0f,
        0.0f, 0.0f, (2.0f * near * far) / (near - far), 0.0f};
}

void App::get_window_size(int &w, int &h)
{
    window.get_window_size(w, h);
}

int App::window_width()
{
	int w, h;
	get_window_size(w, h);
	return w;
}

int App::window_height()
{
	int w, h;
	get_window_size(w, h);
	return h;
}
App::App():
	window(1024, 768, MAJOR_VERSION, MINOR_VERSION, false, 24, 0)
{
	window.set_event_callback(std::bind(&App::process_messages, this, std::placeholders::_1));
	clear_color[0] = 0.1f; clear_color[1] = 0.2f; clear_color[2] = 0.4f; clear_color[3] = 1.0f;
	clear_depth = 1.0f;
}

int App::run()
{
	last_time = current_time = std::chrono::steady_clock::now();
	initialize_graphics();
    general_setup();

	while (window.is_active())
	{
		current_time = std::chrono::steady_clock::now();
		window.poll_events();

        process_inputs();
		update(current_time - last_time);
		draw_scene();

        last_time = current_time;
		window.swap_buffers();
	}

	return 0;
}

void App::initialize_graphics()
{
#ifdef WIN32
	glDebugMessageCallback(&debug_output1, nullptr);
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
#endif
	int w, h; window.get_window_size(w, h);	resize(w, h);
    
    std::cout << glGetString(GL_VERSION) << "\n";
    int ext = 0;
    glGetIntegerv(GL_NUM_EXTENSIONS, &ext);
    
    for(int i = 0; i < ext; ++i) { std::cout << glGetStringi(GL_EXTENSIONS, i) << "\n";};
}

void APIENTRY debug_output1(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const char *message, const void *userParam)
{
	std::string msg = std::string("source: ") + std::to_string(source) + "\n type: " + std::to_string(type)
		+ "\n id: " + std::to_string(id) + "\n severity: " + std::to_string(severity)
		+ "\n " + std::string(message) + "\n";

#ifdef WIN32
	OutputDebugStringA(msg.c_str());
#endif
	std::cerr << msg << std::endl;
}
