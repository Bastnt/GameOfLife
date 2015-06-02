#include "game_of_life_scene.h"

GameOfLifeScene::GameOfLifeScene(QObject *parent, GameEngine* engine) : QGraphicsScene(parent), engine_(engine), square_size(INITIAL_SCENE_SIZE / INITIAL_GRID_SIZE) {
    DrawMatrix();
    square_border = new QPen(Qt::NoPen);
    square_background = new QBrush(QColor(255, 128, 0));
}

GameOfLifeScene::~GameOfLifeScene() {
    delete square_border;
    delete square_background;
}

void GameOfLifeScene::DrawMatrix() {
    clear();
    auto scene_size = square_size * engine_->grid_size;
    addLine(0,0,0,scene_size);
    addLine(0,0,scene_size, 0);
    addLine(scene_size, 0, scene_size, scene_size);
    addLine(0, scene_size, scene_size, scene_size);

    int ipos = 0, jpos;
    for(auto const& line : *engine_->matrix) {
        jpos = 0;
        for(auto const& square : line) {
            if(square)
                addRect(ipos, jpos, square_size, square_size, *square_border, *square_background);
            jpos += square_size;
        }
        ipos += square_size;
    }
}

void GameOfLifeScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    int new_x = ProcessPosition(event->scenePos().x());
    int new_y = ProcessPosition(event->scenePos().y());
    // We keep track of the click state to allow "mouse hold drawing".
    mouse_pressed_ = true;
    last_x_ = new_x;
    last_y_ = new_y;
    engine_->ToggleSquare(last_x_, last_y_);
    DrawMatrix();
}

void GameOfLifeScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    mouse_pressed_ = false;
}

void GameOfLifeScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    int new_x = ProcessPosition(event->scenePos().x());
    int new_y = ProcessPosition(event->scenePos().y());
    // Check if we are on a new square to toggle. Otherwise we would have multiple toggles
    // on a squaure while "mouse hold drawing".
    if((new_x != last_x_ || new_y != last_y_)) {
        last_x_ = new_x;
        last_y_ = new_y;
        engine_->ToggleSquare(last_x_, last_y_);
        DrawMatrix();
    }
}

int GameOfLifeScene::ProcessPosition(qreal a) {
    a /= square_size;
    if(a < 0)
        a = 0;
    else if(a > engine_->grid_size - 1)
        a = engine_->grid_size - 1;
    return a;
}

