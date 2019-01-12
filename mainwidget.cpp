#include "mainwidget.h"
#include "terrain.h"
#include "megaman.h"

#include <QMouseEvent>
#include <QDebug>
#include <math.h>
#include <iostream>

MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    geometries(0),
    megaman(0),
    grassTexture(0),
    megamanTexture(0),
    cam(0.0,0.0,-20),
    camMove(0.0,0.0),
    xMargin(50),
    yMargin(40),
    maxSpeed(0.025)
{
    setMouseTracking(true);
}

MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete grassTexture;
    delete megamanTexture;
    delete geometries;
    delete megaman;
    doneCurrent();
}

QVector2D MainWidget::getWorldCoordinates(QVector2D viewportCoordinates){
    // Get the viewport
    QRect viewport = QRect(0, 0, width(), height());
    // We need to find the good ratio for the far vector (takes into account the camera Z I guess)
    QVector3D Z = Z.project(model, projection, viewport);
    // Compute the far vector witht the above computed z
    QVector3D farr = QVector3D(viewportCoordinates[0], height() - viewportCoordinates[1], Z.z());
    // Compute the world coordinates
    QVector3D worldPosition = farr.unproject(model, projection, viewport);
    return QVector2D(worldPosition[0], worldPosition[1]);
}

void MainWidget::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
    //std::cout << "MousePosition " << mousePressPosition[0] << " " << mousePressPosition[1] << std::endl;
    //megaman = new Megaman("../HMIN317-Projet/megaman.png", getWorldCoordinates(mousePressPosition));
    megaman->moveTo(getWorldCoordinates(mousePressPosition));
}

QVector3D MainWidget::Raycast(int mouse_x, int mouse_y)
{
    QMatrix4x4 view_matrix ;
    view_matrix.translate(cam[0], cam[1], cam[2]);
    // Set modelview-projection matrix
    program.setUniformValue("mvp_matrix", projection * view_matrix);

    // Normalized Device Coordinates
    float x = (2.0f * mouse_x) / this->width() - 1.0f;
    float y = 1.0f - (2.0f * mouse_y) / this->height();
    float z = 1.0f;
    QVector3D normalized_device_coordinates_ray = QVector3D(x, y, z);

    // Homogeneous Clip Coordinates
    QVector4D homogeneous_clip_coordinates_ray = QVector4D(normalized_device_coordinates_ray.x(), normalized_device_coordinates_ray.y(), -1.0f, 1.0f);

    // 4D Eye (Camera) Coordinates
    QVector4D camera_ray = projection.inverted() * homogeneous_clip_coordinates_ray;
    camera_ray = QVector4D(camera_ray.x(), camera_ray.y(), -1.0f, 0.0f);

    // 4D World Coordinates
    QVector3D world_coordinates_ray =(QVector3D) (view_matrix.inverted() * camera_ray);
    world_coordinates_ray.normalize();

    return world_coordinates_ray;
}

QVector3D MainWidget::RayPlaneIntersection(QVector3D ray_origin, QVector3D ray_direction, QVector3D plane_origin, QVector3D plane_normal)
{
    float denominator = QVector3D::dotProduct(plane_origin, -plane_normal);
    float t = -(denominator + ray_origin.z() * plane_normal.z() + ray_origin.y() * plane_normal.y() + ray_origin.x() * plane_normal.x()) / (ray_direction.z() * plane_normal.z() + ray_direction.y() * plane_normal.y() + ray_direction.x() * plane_normal.x());
    return ray_origin + t * ray_direction;
}


QVector2D MainWidget::getWorldCoordinatesByRayCast(QVector2D viewportCoordinates)
{
    QVector3D ray = Raycast(viewportCoordinates[0],viewportCoordinates[1]);
    QVector3D pos = RayPlaneIntersection(cam, ray, QVector3D(0,0,0), QVector3D(0,0,-1));
    return QVector2D(-pos.x(), -pos.y());
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    update();

}

void MainWidget::mouseMoveEvent(QMouseEvent *e){
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());

    camMove = QVector2D(0, 0);
    if(mousePressPosition[0] > this->width()-50){
        camMove[0] = 0.1*1/(this->width()-mousePressPosition[0]);
    }
    else if(mousePressPosition[0] < 50){
        camMove[0] = -0.1*1/(mousePressPosition[0]);
    }

    if(mousePressPosition[1] > this->height()-40){
        camMove[1] = -0.1*1/(this->height()-mousePressPosition[1]);
    }
    else if(mousePressPosition[1] < 40){
        camMove[1] = 0.1*1/(mousePressPosition[1]);
    }

    if(camMove[0] > maxSpeed)
        camMove[0] = maxSpeed;
    else if(camMove[0] < -maxSpeed)
        camMove[0] = -maxSpeed;

    if(camMove[1] > maxSpeed)
        camMove[1] = maxSpeed;
    else if(camMove[1] < -maxSpeed)
        camMove[1] = -maxSpeed;

    update();
}

void MainWidget::timerEvent(QTimerEvent *)
{
    cam[0] += camMove[0];
    cam[1] += camMove[1];
    // Request an update
    update();
}

void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();
    initTextures();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);

    geometries = new Terrain(40, 40);
    megaman = new Megaman("../HMIN317-Projet/megaman.png", QVector2D(0, 0));

    // Use QBasicTimer because its faster than QTimer
    timer.start(10, this);

}

void MainWidget::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}

void MainWidget::initTextures()
{
    // Load grass.png image
    grassTexture = new QOpenGLTexture(QImage("../MoteurStrategique/grass.png"));
    // Set nearest filtering mode for texture minification
    grassTexture->setMinificationFilter(QOpenGLTexture::Nearest);
    // Set bilinear filtering mode for texture magnification
    grassTexture->setMagnificationFilter(QOpenGLTexture::Linear);
    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    grassTexture->setWrapMode(QOpenGLTexture::Repeat);


    // Load megaman.png image
    megamanTexture = new QOpenGLTexture(QImage("../MoteurStrategique/megaman.png"));
    // Set nearest filtering mode for texture minification
    megamanTexture->setMinificationFilter(QOpenGLTexture::Nearest);
    // Set bilinear filtering mode for texture magnification
    megamanTexture->setMagnificationFilter(QOpenGLTexture::Linear);
    // Wrap texture coordinates by repeating
    megamanTexture->setWrapMode(QOpenGLTexture::Repeat);
}

void MainWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 1.0, zFar = 50.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}

void MainWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    grassTexture->bind(0);
    // Use texture unit 0 which contains grass.png
    program.setUniformValue("texture", 0);
    // Draw the terrain
    geometries->draw(&program);

    megamanTexture->bind(1);
    program.setUniformValue("texture", 1);
    megaman->draw(&program);

    // Calculate model view transformation
    model = QMatrix4x4();
    // So that Y+ is upwards and the images are on their head...
    model.rotate(180, 0, 0, 1);
    model.translate(cam[0], cam[1], cam[2]);

    // Set modelview-projection matrix
    program.setUniformValue("mvp_matrix", projection * model);
}
