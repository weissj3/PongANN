project(SDLHelloWorld)

cmake_minimum_required(VERSION 2.6)

set(INCLUDES    Pong.h
                Ball.h
                Vector2.h
                Physics.h
                Paddle.h
                Player.h
                HumanPlayer.h
                BasicAI.h
                Wall.h
                ANN.h
                Matrix.h
                ANNAI.h
                Optimizer.h
                ParticleSwarm.h)

set(SOURCES     main.cpp
                Paddle.cpp
                Pong.cpp
                Ball.cpp
                Physics.cpp
                Vector2.cpp
                Player.cpp
                BasicAI.cpp
                HumanPlayer.cpp
                Wall.cpp
                Matrix.cpp
                ANN.cpp
                ANNAI.cpp
                Optimizer.cpp
                ParticleSwarm.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -g")

add_executable(${PROJECT_NAME} ${SOURCES})

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES})
