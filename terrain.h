#ifndef TERRAIN_H
#define TERRAIN_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

class Terrain : protected QOpenGLFunctions
{
public:
    Terrain(int w, int height);
    virtual ~Terrain();

    void draw(QOpenGLShaderProgram *program);

private:
    void init();

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;

    // 2
    int nbOfVertices;
    int width;
    int height;
};

#endif // TERRAIN_H
