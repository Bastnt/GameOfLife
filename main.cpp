#include "game_of_life.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameOfLife main_window;
    main_window.show();
    return a.exec();
}
