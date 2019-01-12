#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "terrain.h"
#include "megaman.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

class Terrain;

class MainWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

protected:
    void timerEvent(QTimerEvent *e) override;
    void mousePressEvent(QMouseEvent *e) ;
    void mouseMoveEvent(QMouseEvent *e) ;
    void mouseReleaseEvent(QMouseEvent *e);

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void initShaders();
    void initTextures();
    QVector2D getWorldCoordinates(QVector2D viewportCoordinates);
    QVector2D getWorldCoordinatesByRayCast(QVector2D viewportCoordinates);
    QVector3D Raycast(int mouse_x, int mouse_y);
    QVector3D RayPlaneIntersection(QVector3D ray_origin, QVector3D ray_direction, QVector3D plane_origin, QVector3D plane_normal);

private:
    QBasicTimer timer;
    QOpenGLShaderProgram program;

    Terrain *geometries;
    Megaman *megaman;

    QOpenGLTexture *grassTexture;
    QOpenGLTexture *megamanTexture;

    QMatrix4x4 projection;
    QMatrix4x4 model;

    QVector2D mousePressPosition;
    QVector3D cam;
    QVector2D camMove;

    // Window movement
    int xMargin;
    int yMargin;
    float maxSpeed;
};

#endif // MAINWIDGET_H
