#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

// Qt includes
#include <QWidget>
#include <QGraphicsView>
#include <QTimer>
#include <QPushButton>
#include <QSlider>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QColorDialog>
#include <QLabel>

#include "game_of_life_scene.h"
#include "game_engine.h"

// This class is the main window, it manages the draw area and the game engine.

class GameOfLife : public QWidget {
    Q_OBJECT

public:
    // ctor
    GameOfLife(QWidget* parent = 0);
    // dtor
    ~GameOfLife();

public slots:
    // Called every time the timer ticks
    void TimeStep();
    // Start or pause the timer
    void StartPause();
    // Change the speed at which TimeStep is called
    void ChangeSpeed(int speed);
    // Empty the board
    void ClearBoard();
    // Change squares color
    void ChangeColor();
    // Resizing the grid
    void ChangeGridSize(int size);
    // Resizing the scene
    void ChangeSceneSize(int size);

private:
    // Timer managing time steps
    QTimer* timer;

    // The game engine of the game of life
    GameEngine engine_;

    // Scene size in px
    int scene_size_;

    // Main Widow
    QHBoxLayout* main_layout_;
    QVBoxLayout* tools_layout_;
    QWidget* tools_widget_;

    // Draw Area
    QGraphicsView* draw_view_;
    GameOfLifeScene* draw_scene_;

    // Commands UI
    QPushButton* b_start_;
    QPushButton* b_clear_;
    QPushButton* b_color_;
    QGroupBox* g_commands_;
    QHBoxLayout* l_commands_;
    QVBoxLayout* lv_commands_;

    // Speed UI
    QLabel* l_speed_value_;
    QGroupBox* g_speed_;
    QVBoxLayout* l_speed_;
    QSlider* s_speed_;

    // GridSize UI
    QGroupBox* g_grid_size_;
    QVBoxLayout* l_grid_size_;
    QLabel* l_grid_size_value_;
    QSlider* s_grid_size_;

    // SceneSize UI
    QGroupBox* g_scene_size_;
    QVBoxLayout* l_scene_size_;
    QLabel* l_scene_size_value_;
    QSlider* s_scene_size_;



};

#endif // GAME_OF_LIFE_H

