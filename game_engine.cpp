#include "game_engine.h"

GameEngine::GameEngine() : grid_size(INITIAL_GRID_SIZE) {
    matrix = new std::vector<std::vector<bool> >;
    ClearBoard();
}

GameEngine::~GameEngine() {
    delete matrix;
}

void GameEngine::ClearBoard() {
    auto& m = *matrix;
    m.clear();
    m.reserve(grid_size);
    for(int i = 0; i < grid_size; ++i) {
        std::vector<bool> line;
        line.reserve(grid_size);
        for(int j = 0; j < grid_size; ++j) {
            line.push_back(false);
        }
        m.push_back(std::move(line));
    }
}

void GameEngine::TimeStep() {
    auto& o_matrix = *matrix;
    // We create a new matrix, to keep a snapshot of the old state for all the processing
    std::vector<std::vector<bool> >* new_matrix = new std::vector<std::vector<bool> >;
    auto& n_matrix = * new_matrix;
    // Number of neighbors alive
    int active_neighbors;
    // Limit of the matrix
    size_t const array_boundary = grid_size - 1;

    n_matrix.reserve(grid_size);

    for(size_t i = 0, max_i = o_matrix.size(); i < max_i; ++i) {
        std::vector<bool> n_line;
        n_line.reserve(grid_size);
        for(size_t j = 0, max_j = o_matrix[0].size(); j < max_j; ++j) {
            active_neighbors = 0;

            if(i>0 && o_matrix[i-1][j])
                ++active_neighbors;
            if(i>0 && j > 0 && o_matrix[i-1][j-1])
                ++active_neighbors;
            if(i>0 && j < array_boundary && o_matrix[i-1][j+1])
                ++active_neighbors;
            if(j>0 && o_matrix[i][j-1])
                ++active_neighbors;
            if(j>0 && i < array_boundary && o_matrix[i+1][j-1])
                ++active_neighbors;
            if(i < array_boundary && j < array_boundary && o_matrix[i+1][j+1])
                ++active_neighbors;
            if(i < array_boundary && o_matrix[i+1][j])
                ++active_neighbors;
            if(j < array_boundary && o_matrix[i][j+1])
                ++active_neighbors;

            if(o_matrix[i][j] && active_neighbors != 2 && active_neighbors != 3)
                n_line.push_back(false);
            else if(!o_matrix[i][j] && active_neighbors == 3)
                n_line.push_back(true);
            else
                n_line.push_back(o_matrix[i][j]);
        }
        n_matrix.push_back(std::move(n_line));
    }

    delete matrix;
    matrix = new_matrix;
}

void GameEngine::ToggleSquare(int x, int y) {
    (*matrix)[x][y] = !(*matrix)[x][y];
}
