#include <QApplication>
#include <QLabel>
#include <QSurfaceFormat>
#include <QDesktopWidget>

#ifndef QT_NO_OPENGL
#include <list>
#include <algorithm>
#include <iostream>

#include "astar.h"
#include "game.h"

#endif

// External variable
Game* game;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("Nutcracker Empire");
    app.setApplicationVersion("1.0");
#ifndef QT_NO_OPENGL

    game = new Game();
    game->adjustSize();
    game->move(QApplication::desktop()->screen()->rect().center() - game->rect().center());
    game->show();
    game->displayMainMenu();

#else
    QLabel note("OpenGL Support required");
    note.show();
#endif
    return app.exec();
}
