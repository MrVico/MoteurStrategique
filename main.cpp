#include <QApplication>
#include <QLabel>
#include <QSurfaceFormat>

#ifndef QT_NO_OPENGL
#include "mainwidget.h"
#include "game.h"
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("Projet");
    app.setApplicationVersion("0.1");
#ifndef QT_NO_OPENGL

    /*
    MainWidget widget;
    widget.setFixedWidth(1080);
    widget.setFixedHeight(720);
    widget.show();
    */

    Game* game = new Game();
    game->show();
    game->displayMainMenu();

#else
    QLabel note("OpenGL Support required");
    note.show();
#endif
    return app.exec();
}
