#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class RenderWindow
{
public:
    RenderWindow(const char* p_title, int p_w, int p_h);
    SDL_Texture* loadTexture(const char* p_filePath);
    void cleanUp();
    void clear();
    void render(int yPlayer, int yBot, int32_t centreX, int32_t centreY);
    void display();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

