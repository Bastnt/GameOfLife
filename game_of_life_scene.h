#ifndef GAME_OF_LIFE_SCENE_H
#define GAME_OF_LIFE_SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include "game_engine.h"

// The scene manage the drawing of the matrix and the mouse events to change square states.

class GameOfLifeScene : public QGraphicsScene {
public:
    // ctor
    explicit GameOfLifeScene(QObject* parent = 0, GameEngine* engine = 0);
    // dtor
    ~GameOfLifeScene();
    // Draw the matrix on the scene
    void DrawMatrix();
    // Square Size in px
    int square_size;
    // Square design
    QPen* square_border;
    QBrush* square_background;


private:
    // Mouse events on the scene
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    // Process the position of 1 axis taking care of the boundaries
    int ProcessPosition(qreal a);

    // Members used for mouse interactions
    bool mouse_pressed_;
    int last_x_;
    int last_y_;

    // A watch pointer to draw the matrix
    GameEngine* engine_;

};

#endif // GAME_OF_LIFE_SCENE_H

