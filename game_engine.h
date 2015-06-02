#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <vector>

// Constants
#define INITIAL_LATENCY 200
#define MIN_LATENCY 50
#define MAX_LATENCY 5000

#define INITIAL_SCENE_SIZE 500
#define MIN_SCENE 100
#define MAX_SCENE 1000

#define INITIAL_GRID_SIZE 50
#define MIN_GRID 10
#define MAX_GRID 400

// This is the game engine, it processes the game of life mechanics.

class GameEngine {
public:
    // ctor
    GameEngine();
    // dtor
    ~GameEngine();
    // Process the new game state
    void TimeStep();
    // Empty the board
    void ClearBoard();
    // Toggle the state of a particular square of the matrix
    void ToggleSquare(int x, int y);

    // The data structure representing the board
    std::vector<std::vector<bool> >* matrix;

    // The size of the grid
    int grid_size;
};

#endif // GAME_ENGINE_H

