#ifndef _PONG_H_
#define _PONG_H_

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Physics.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
/*Main Game Class
    Initializes SDL and Creates Window
    Houses Game loop
*/
class Player;
class Ball;
class ANNAITrainer;

class Pong 
{
private:
    static int              m_SCREEN_WIDTH;
    static int              m_SCREEN_HEIGHT;

    static SDL_Window*      m_window;
    static SDL_Surface*     m_screenSurface;
    static PhysicsHandler*  m_physicsHandler;
    static Player*          m_player1;
    static Player*          m_player2;
    static Ball*            m_ball;
    static ANNAITrainer*    m_trainer;
    static bool             m_slow;
    static TTF_Font*        m_sans;

    static bool             m_quit;

    static void             GetInput();
    
    static void             Initialize();
    static void             CleanUp();
    
    static void             CheckWinCondition();
public:
    static void Run();
    static SDL_Window* getWindow() { return m_window; }
    static SDL_Surface* getSurface() { return m_screenSurface; }
    static PhysicsHandler* getPhysicsHandler() { return m_physicsHandler; }
    static Player* GetPlayer1() { return m_player1; }
    static Player* GetPlayer2() { return m_player2; }
    static Ball* getBall() { return m_ball; }
    static TTF_Font* getFont() { return m_sans; }
    
};

#endif
