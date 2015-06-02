#include "game_of_life.h"

GameOfLife::GameOfLife(QWidget* parent) : QWidget(parent), scene_size_(INITIAL_SCENE_SIZE) {

    // Main Window
    main_layout_ = new QHBoxLayout();
    tools_layout_ = new QVBoxLayout();
    tools_layout_->setAlignment(Qt::AlignTop);
    tools_widget_ = new QWidget();
    tools_widget_->setLayout(tools_layout_);
    tools_widget_->setMaximumWidth(250);

    // Draw Area
    draw_scene_ = new GameOfLifeScene(this, &engine_);
    draw_view_ = new QGraphicsView();
    draw_view_->setScene(draw_scene_);
    draw_view_->setSceneRect(0, 0, scene_size_, scene_size_);

    // Timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(TimeStep()));
    timer->setInterval(INITIAL_LATENCY);

    // Commands UI
    g_commands_ = new QGroupBox("Commandes");
    l_commands_ = new QHBoxLayout();
    lv_commands_ = new QVBoxLayout();
    g_commands_->setLayout(lv_commands_);

    b_start_ = new QPushButton("Démarrer");
    b_clear_ = new QPushButton("Effacer");
    b_color_ = new QPushButton("Couleur");
    connect(b_start_, SIGNAL(clicked()), this, SLOT(StartPause()));
    connect(b_clear_, SIGNAL(clicked()), this, SLOT(ClearBoard()));
    connect(b_color_, SIGNAL(clicked()), this, SLOT(ChangeColor()));

    l_commands_->addWidget(b_start_);
    l_commands_->addWidget(b_clear_);
    lv_commands_->addLayout(l_commands_);
    lv_commands_->addWidget(b_color_);


    // Speed UI
    g_speed_ = new QGroupBox("Lantence (en ms)");
    l_speed_ = new QVBoxLayout();
    g_speed_->setLayout(l_speed_);
    l_speed_value_ = new QLabel();
    l_speed_value_->setNum(INITIAL_LATENCY);
    s_speed_ = new QSlider(Qt::Horizontal);
    s_speed_->setRange(MIN_LATENCY, MAX_LATENCY);
    s_speed_->setValue(INITIAL_LATENCY);
    connect(s_speed_, SIGNAL(valueChanged(int)), this, SLOT(ChangeSpeed(int)));
    connect(s_speed_, SIGNAL(valueChanged(int)), l_speed_value_, SLOT(setNum(int)));
    l_speed_->addWidget(l_speed_value_);
    l_speed_->addWidget(s_speed_);

    // GridSize UI
    g_grid_size_ = new QGroupBox("Taille de grille");
    l_grid_size_ = new QVBoxLayout();
    g_grid_size_->setLayout(l_grid_size_);
    l_grid_size_value_ = new QLabel();
    l_grid_size_value_->setNum(INITIAL_GRID_SIZE);
    s_grid_size_ = new QSlider(Qt::Horizontal);
    s_grid_size_->setRange(MIN_GRID, MAX_GRID);
    s_grid_size_->setValue(INITIAL_GRID_SIZE);
    connect(s_grid_size_, SIGNAL(valueChanged(int)), l_grid_size_value_, SLOT(setNum(int)));
    connect(s_grid_size_, SIGNAL(valueChanged(int)), this, SLOT(ChangeGridSize(int)));
    l_grid_size_->addWidget(l_grid_size_value_);
    l_grid_size_->addWidget(s_grid_size_);

    // SceneSize UI
    g_scene_size_ = new QGroupBox("Taille de la zone de dessin");
    l_scene_size_ = new QVBoxLayout();
    g_scene_size_->setLayout(l_scene_size_);
    l_scene_size_value_ = new QLabel();
    l_scene_size_value_->setNum(INITIAL_SCENE_SIZE);
    s_scene_size_ = new QSlider(Qt::Horizontal);
    s_scene_size_->setRange(MIN_SCENE, MAX_SCENE);
    s_scene_size_->setValue(INITIAL_SCENE_SIZE);
    connect(s_scene_size_, SIGNAL(valueChanged(int)), l_scene_size_value_, SLOT(setNum(int)));
    connect(s_scene_size_, SIGNAL(valueChanged(int)), this, SLOT(ChangeSceneSize(int)));
    l_scene_size_->addWidget(l_scene_size_value_);
    l_scene_size_->addWidget(s_scene_size_);

    tools_layout_->addWidget(g_commands_);
    tools_layout_->addWidget(g_speed_);
    tools_layout_->addWidget(g_grid_size_);
    tools_layout_->addWidget(g_scene_size_);

    main_layout_->addWidget(draw_view_);
    main_layout_->addWidget(tools_widget_);
    setLayout(main_layout_);
}

void GameOfLife::TimeStep() {
    engine_.TimeStep();
    draw_scene_->DrawMatrix();
}

void GameOfLife::ClearBoard() {
    engine_.ClearBoard();
    draw_scene_->DrawMatrix();
}

void GameOfLife::ChangeSpeed(int speed) {
    timer->setInterval(speed);
}

void GameOfLife::StartPause() {
    if(timer->isActive()) {
        b_start_->setText("Démarrer");
        timer->stop();
    }
    else {
        b_start_->setText("Pause");
        timer->start();
    }
}

void GameOfLife::ChangeColor() {
    QColorDialog *dlg = new QColorDialog(draw_scene_->square_background->color(), this);
    draw_scene_->square_background->setColor(dlg->getColor());
    delete dlg;
    draw_scene_->DrawMatrix();
}

void GameOfLife::ChangeGridSize(int size) {
    engine_.grid_size = size;
    draw_scene_->square_size = scene_size_ / size;
    engine_.ClearBoard();
    draw_scene_->DrawMatrix();
}

void GameOfLife::ChangeSceneSize(int size) {
    scene_size_ = size;
    draw_view_->setSceneRect(0, 0, scene_size_, scene_size_);
    draw_scene_->square_size = scene_size_ / engine_.grid_size;
    draw_scene_->DrawMatrix();
}

GameOfLife::~GameOfLife() {
    delete main_layout_;
}
