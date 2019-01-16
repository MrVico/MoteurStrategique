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

    app.setApplicationName("Projet");
    app.setApplicationVersion("1.0");
#ifndef QT_NO_OPENGL

    /*
    MainWidget widget;
    widget.setFixedWidth(1080);
    widget.setFixedHeight(720);
    widget.show();
    */

    game = new Game();
    game->adjustSize();
    game->move(QApplication::desktop()->screen()->rect().center() - game->rect().center());
    game->show();
    game->displayMainMenu();
    /*
    // test a*
    map m;
    point s;
    point e(7, 7);
    astar a;

    std::list<point> path;
    a.search(s, e, m);
    int c = a.path(path);

    std::cout << "path cost " << c << std::endl;

    for( std::list<point>::iterator i = path.begin(); i != path.end(); i++ ) {
        std::cout << "(" << ( *i ).x << ", " << ( *i ).y << ") ";
    }

    std::cout << std::endl;
    */
#else
    QLabel note("OpenGL Support required");
    note.show();
#endif
    return app.exec();
}
