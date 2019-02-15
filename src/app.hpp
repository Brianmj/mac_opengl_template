#ifndef KNU_APP
#define KNU_APP

#include <chrono>
#include <knu/window2.hpp>
#include <knu/gl_utility.hpp>
#include <knu/mathlibrary6.hpp>
#include "knu/knu_texture.hpp"

#ifdef _WIN32
#define MAJOR_VERSION 4
#define MINOR_VERSION 6
#endif
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#define MAJOR_VERSION 3         // In sdl, for the time being, the only way to request a 4.1 context is
#define MINOR_VERSION 2         // to request a 3.2 context on mac
#endif

using knu_time = std::chrono::duration<float, std::ratio<1, 1000>>;

class main_app
{
    window_class window;
    std::vector<std::uint8_t> keyboard_state;
    std::chrono::steady_clock::time_point current_time, last_time;
    float clearColorVal[4];
    float clearDepthVal;
    knu::math::matrix4f perspective_matrix;
    knu::math::matrix4f orthographic_matrix;
    
private:
    void general_setup();
    void draw_scene();
    void process_inputs(knu_time seconds);
    void update(knu_time seconds);
    void load_shaders();
    void initialize_graphics();
    void process_messages(SDL_Event *event);
    void resize(int w, int h);
    void get_window_size(int &w, int &h);
    int window_width();
    int window_height();
    
public:
    main_app();
    int run();
};

#endif
