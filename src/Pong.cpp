#include "Pong.h"
#include "HumanPlayer.h"
#include "Ball.h"
#include "Wall.h"
#include "BasicAI.h"
#include "ANNAI.h"
#include "ANNAITrainer.h"


//Initialize static class
int              Pong::m_SCREEN_WIDTH;
int              Pong::m_SCREEN_HEIGHT;
SDL_Window*      Pong::m_window;
SDL_Surface*     Pong::m_screenSurface;
bool             Pong::m_quit;   
PhysicsHandler*  Pong::m_physicsHandler;
Player*          Pong::m_player1;
Player*          Pong::m_player2;
Ball*            Pong::m_ball;
ANNAITrainer*    Pong::m_trainer;
bool             Pong::m_slow;

void Pong::Initialize()
{
    m_slow = false;
    //INITIALIZE SDL
    m_window = nullptr;
    m_screenSurface = nullptr;

    m_quit = false;
    m_physicsHandler = new PhysicsHandler;
    
    
    m_SCREEN_WIDTH = SCREEN_WIDTH;    
    m_SCREEN_HEIGHT = SCREEN_HEIGHT;
    
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cerr << "SDL failed to initialize! SDL_Error: " << SDL_GetError() << std::endl;
        m_quit = true;
        return;    
    }
    
    //Make a window and fill with white rectange

    m_window = SDL_CreateWindow( "PANN", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_SCREEN_WIDTH, m_SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    
    if( m_window == nullptr )
    {
        std::cerr << "Windows could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        m_quit = true;
        return;
    }

    m_screenSurface = SDL_GetWindowSurface( m_window );
    
    m_player1 = new ANNAI(1);
    m_player2 = new ANNAI(2);
    

    m_trainer = new ANNAITrainer((ANNAI*)m_player1, (ANNAI*)m_player2, "DE_Iteration.xml");
    
    m_ball = new Ball(Vector2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2), Vector2(3, 3), 3);
    m_ball->setRandVel(5.0);
    m_physicsHandler->RegisterPhysicsObject( (PhysicsObject*) m_ball);
}


void Pong::Run()
{
    Initialize();
    SDL_FillRect( m_screenSurface, NULL, SDL_MapRGB( m_screenSurface->format, 0xff, 0xff, 0xff ) );
    
    //TO DO:  Fix weird collisions between ball and paddle
    //        Make Collision off of Paddle Slightly curved
    
    Wall topWall(Vector2(0,0));
    Wall botWall(Vector2(0,SCREEN_HEIGHT+10));
    
    //Add walls into the physics handler
    m_physicsHandler->RegisterPhysicsObject( (PhysicsObject*) &topWall);
    m_physicsHandler->RegisterPhysicsObject( (PhysicsObject*) &botWall);
    
    while(!m_quit)
    {        
        CheckWinCondition();
        GetInput();
        if(m_player1->GetType() == Player::PlayerType::HUMAN || m_player2->GetType() == Player::PlayerType::HUMAN || m_slow)
        {
            SDL_Delay(5);  //Probably want to make this tunable to speed learning
        }
        SDL_FillRect( m_screenSurface, NULL, SDL_MapRGB( m_screenSurface->format, 0xff, 0xff, 0xff ) );
        m_ball->Render();
        m_player1->Update();
        m_player2->Update();
        
        //To Do: Add Renderable List?
        SDL_UpdateWindowSurface( m_window );
        //Update Physics for the Game
        m_physicsHandler->UpdatePhysics();
    }
    CleanUp();
}

void Pong::CheckWinCondition()
{
    //Maybe break up a little better
    if(m_ball->getPos().x > SCREEN_WIDTH || m_ball->getPos().x < 0)
    {

        if(m_ball->getPos().x > SCREEN_WIDTH)
        {
            m_player1->ScorePoint();
        }
        else
        {
            m_player2->ScorePoint();
        }
        m_player1->ResetPaddle();
        m_player2->ResetPaddle();
        m_ball->setPos(Vector2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2));
        m_ball->setRandVel(5.0);
        SDL_FillRect( m_screenSurface, NULL, SDL_MapRGB( m_screenSurface->format, 0xff, 0xff, 0xff ) );
        m_ball->Render();
        m_player1->Update();
        m_player2->Update();
        SDL_UpdateWindowSurface( m_window );
        if(m_player1->GetScore() + m_player2->GetScore() == 10)
        {
            std::cout << "Score:  " << m_player1->GetScore() << " to " << m_player2->GetScore() << std::endl;
            m_trainer->Update();
            m_player1->ResetScore();
            m_player2->ResetScore();
        }
    }
}

void Pong::CleanUp()
{
    SDL_DestroyWindow( m_window );
    
    delete m_player1;
    delete m_player2;
    delete m_physicsHandler;
    delete m_ball;
    
    SDL_Quit();
}

void Pong::GetInput()
{
    //Handles input from the user to effect application state
    //Maybe deserves its own class in the future?

    SDL_Event e;
    while( SDL_PollEvent( &e ) )
    {
        switch( e.type )
        {        
            case SDL_KEYDOWN:
                if(m_player1->GetType() == Player::PlayerType::HUMAN)
                {
                    ((HumanPlayer*) m_player1)->KeyDown(e.key.keysym.sym);
                }
                if(m_player2->GetType() == Player::PlayerType::HUMAN)
                {
                    ((HumanPlayer*) m_player2)->KeyDown(e.key.keysym.sym);
                }
                if(m_slow)
                {
                    m_slow = false;
                }
                else
                {
                    m_slow = true;
                }
                break;
            case SDL_KEYUP:
                if(m_player1->GetType() == Player::PlayerType::HUMAN)
                {
                    ((HumanPlayer*) m_player1)->KeyUp(e.key.keysym.sym);
                }
                if(m_player2->GetType() == Player::PlayerType::HUMAN)
                {
                    ((HumanPlayer*) m_player2)->KeyUp(e.key.keysym.sym);
                }
                break;
            case SDL_QUIT:
                m_quit = true;
                break;
            default:
                break;
        }
    }
}
