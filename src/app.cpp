#include "app.hpp"
#include <string>
#include <iostream>

using namespace knu::math;

void main_app::general_setup()
{
    load_shaders();
    glEnable(GL_DEPTH_TEST);
    
}

void main_app::draw_scene()
{
    glClearBufferfv(GL_COLOR, 0, clearColorVal);
    glClearBufferfv(GL_DEPTH, 0, &clearDepthVal);
    
    
}

void main_app::process_inputs(knu_time delta_time)
{
    {
        const std::uint8_t* temp = SDL_GetKeyboardState(nullptr);
        keyboard_state = std::vector<std::uint8_t>(temp, temp + SDL_NUM_SCANCODES);
        temp = nullptr;
    }
    
    if (keyboard_state[SDL_SCANCODE_SPACE])
    {
        
    }
    
}

void main_app::update(knu_time seconds)
{
    
}

void main_app::load_shaders()
{
    
}

void main_app::process_messages(SDL_Event *event)
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

void main_app::resize(int w, int h)
{
    glViewport(0, 0, w, h);
    perspective_matrix = fov_perspective(70.0f, static_cast<float>(w) / h, 0.1f, 100.0f);
    orthographic_matrix = fmake_ortho(-static_cast<float>(w / 2), static_cast<float>(w / 2),
                                      static_cast<float>(-h / 2), static_cast<float>(h / 2), 0.1f, 100.0f);
    
}

void main_app::get_window_size(int &w, int &h)
{
    window.get_window_size(w, h);
}

int main_app::window_width()
{
    int w, h;
    get_window_size(w, h);
    return w;
}

int main_app::window_height()
{
    int w, h;
    get_window_size(w, h);
    return h;
}
main_app::main_app():
window(1024, 768, MAJOR_VERSION, MINOR_VERSION, false, 24, 0),
keyboard_state(SDL_NUM_SCANCODES)
{
    window.set_event_callback(std::bind(&main_app::process_messages, this, std::placeholders::_1));
    clearColorVal[0] = 0.607843f;
    clearColorVal[1] = 0.803921f;
    clearColorVal[2] = 0.992156f;
    clearColorVal[3] = 1.0f;
    clearDepthVal = 1.0f;
}

int main_app::run()
{
    last_time = current_time = std::chrono::steady_clock::now();
    initialize_graphics();
    general_setup();
    
    while (window.is_active())
    {
        current_time = std::chrono::steady_clock::now();
        window.poll_events();
        
        knu_time delta_time = current_time - last_time;
        process_inputs(delta_time);
        update(delta_time);
        draw_scene();
        
        last_time = current_time;
        window.swap_buffers();
    }
    
    return 0;
}

void main_app::initialize_graphics()
{
#ifdef _WIN32
    glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity,
                              GLsizei length, const char *message, const void *user_param) {
        std::string msg = std::string("source: ") + std::to_string(source) + "\n type: " + std::to_string(type)
        + "\n id: " + std::to_string(id) + "\n severity: " + std::to_string(severity)
        + "\n " + std::string(message) + "\n";
        
#ifdef _WIN32
        
#endif
        std::cerr << msg << std::endl;
        
    }, nullptr);
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
#endif
    int w, h; window.get_window_size(w, h);    resize(w, h);
}

/*void APIENTRY debug_output1(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const char *message, const void *userParam)
 {
 std::string msg = std::string("source: ") + std::to_string(source) + "\n type: " + std::to_string(type)
 + "\n id: " + std::to_string(id) + "\n severity: " + std::to_string(severity)
 + "\n " + std::string(message) + "\n";
 #ifdef _WIN32
 OutputDebugStringA(msg.c_str());
 #endif
 std::cerr << msg << std::endl;
 }*/
