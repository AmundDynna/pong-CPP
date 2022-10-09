#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
    :window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

    if(window == NULL)
    {
        std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);
    if (texture == NULL)
        std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
    return texture;
}

void RenderWindow::cleanUp()
{
    SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
    SDL_RenderClear(renderer);
}

void RenderWindow::render(int yPlayer, int yBot, int32_t centreX, int32_t centreY)
{
    SDL_Rect playerOne;
    playerOne.x = 10;
    playerOne.y = yPlayer;
    playerOne.w = 20;
    playerOne.h = 80;

    SDL_Rect playerTwo;
    playerTwo.x = 470;
    playerTwo.y = yBot;
    playerTwo.w = 20;
    playerTwo.h = 80;

    SDL_Rect ball;
    ball.x = centreX + 6;
    ball.y = centreY + 6;
    ball.w = 11;
    ball.h = 11;

    SDL_Rect mid;
    mid.x = 245;
    mid.y = 0;
    mid.w = 10;
    mid.h = 20;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // Draw middle
    for (int i = 0; i < 10; i++)
    {
        mid.y = 30 * i;
        SDL_RenderDrawRect(renderer, &mid);
        SDL_RenderFillRect(renderer, &mid);
    }
    // Draw first player
    SDL_RenderDrawRect(renderer, &playerOne);
    SDL_RenderFillRect(renderer, &playerOne);
    // Draw second player
    SDL_RenderDrawRect(renderer, &playerTwo);
    SDL_RenderFillRect(renderer, &playerTwo);
    // Draw ball
    SDL_RenderDrawRect(renderer, &ball);
    SDL_RenderFillRect(renderer, &ball);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);
}

void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}