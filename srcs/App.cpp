#include "../includes/Includes.h"

App::App(uint32_t width, uint32_t height, std::string title)
    : window(width, height, title) {}

App::~App() {}

void App::run() { window.init(); }
