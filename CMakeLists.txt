project(SDLHelloWorld)

cmake_minimum_required(VERSION 2.6)

set(PONG_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include" CACHE INTERNAL "Pong includes")
include_directories(${PONG_INCLUDE_DIR})

find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})


set(INCLUDES    include/Pong.h
                include/Ball.h
                include/Vector2.h
                include/Physics.h
                include/Paddle.h
                include/Player.h
                include/HumanPlayer.h
                include/BasicAI.h
                include/Wall.h
                include/ANN.h
                include/ANNAI.h
                include/ANNAITrainer.h
                include/Optimizer.h
                include/DifferentialEvolution.h)

set(SOURCES     src/main.cpp
                src/Paddle.cpp
                src/Pong.cpp
                src/Ball.cpp
                src/Physics.cpp
                src/Vector2.cpp
                src/Player.cpp
                src/BasicAI.cpp
                src/HumanPlayer.cpp
                src/Wall.cpp
                src/ANN.cpp
                src/ANNAI.cpp
                src/ANNAITrainer.cpp
                src/Optimizer.cpp
                src/DifferentialEvolution.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -lSDL2_ttf")

add_executable(${PROJECT_NAME} ${SOURCES})

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

#find_package(sdl2_ttf REQUIRED)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES}
                                      ${ARMADILLO_LIBRARIES})
