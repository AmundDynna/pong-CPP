#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <cmath>
#include "RenderWindow.hpp"

int main(int argc, char* args[])
{
    if(SDL_Init(SDL_INIT_VIDEO) > 0)
        std::cout << "HEY.. SDL_INIT HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
    
    if(!(IMG_Init(IMG_INIT_PNG)))
        std::cout << "IMG_INIT has failed. Error: " << SDL_GetError() << std::endl;

    RenderWindow window("GAME v1.0", 500, 300);
    /*
    RenderWindow::Paddle player1;
    player1.paddle();
    */
    
    bool gameRunning = true;
    SDL_Event event;
    int yPlayer{0};
    int yBot{0};
    int xBall{250};
    int yBall{150};
    int ballAngle{-90};
    double ballVelo{5};

    while (gameRunning)
    {
        
        Uint64 start = SDL_GetPerformanceCounter();
        while (SDL_PollEvent(&event))  
        {                     
            if(event.type == SDL_QUIT)  
                gameRunning = false;
        }

        const Uint8* keystates = SDL_GetKeyboardState(NULL);
        if(keystates[SDL_SCANCODE_UP]) {
            if (yPlayer > 0)
                yPlayer -= 8;
        }
        if(keystates[SDL_SCANCODE_DOWN]) {
            if (yPlayer < 220)
                yPlayer += 8;
        }
        // game logic for hitting player paddle
        if ((xBall < 30) && ((yBall < yPlayer + 80) && (yBall > yPlayer)))
        {
            ballAngle += 180;
            xBall = 31;
            double distance = yPlayer + 40 - yBall;
            ballAngle += distance * 2;
            ballVelo += 0.5;
        }
        // game logic for hitting bot paddle
        if ((xBall > 470) && ((yBall < yBot + 80) && (yBall > yBot)))
        {
            ballAngle += 180;
            xBall = 469;
            double distance = yBot- yBall;
            ballAngle += distance * 2;
            ballVelo += 0.5;
        }

        while (ballAngle > 360)
        {
            ballAngle -= 360;
        }

        // ball movement
        xBall += ballVelo * cos(ballAngle*(M_PI/180));
        yBall += ballVelo * sin(ballAngle*(M_PI/180));

        // Bot movement
        if (abs((yBot - yBall - 30)) > 8)
        {
            if (yBot > yBall - 30)
                yBot -= 7;
            else if (yBot < yBall - 30)
                yBot += 7;
        }
        if (yBot < 0)
            yBot = 0;
        else if(yBot > 220)
            yBot = 220;


        // game logic for how the ball bonces of walls and paddle
        if (yBall < 1)
        {
            ballAngle *= -1;
            yBall = 2;
        }
        else if (yBall > 289)
        {
            ballAngle *= -1;
            yBall = 288;
        }
        // ball spawns in middle after losing point
        if ((xBall < -5) || (xBall > 499))
        {
            xBall = 250;
            yBall = 150;
            ballVelo = 5;
        }
        // adding score and middle line to render function
        if ((abs(ballAngle) > 70 && abs(ballAngle) < 110) || (abs(ballAngle) > 250 && abs(ballAngle) < 290))
            ballAngle += 90;
        if (ballAngle == 0)
            ballAngle = 90;
        
        // done

        window.clear();
        window.render(yPlayer, yBot, xBall, yBall);
        window.display();

        Uint64 end = SDL_GetPerformanceCounter();
        float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
        if (gameRunning)
            SDL_Delay(floor(16.666f - elapsedMS));
        
    }

    window.cleanUp();
    SDL_Quit();

    return 0;
}