#include "terrain.h"

#include <QVector2D>
#include <QVector3D>
#include <QImage>

#include <iostream>

struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};

Terrain::Terrain(int w, int h) :
    indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // The terrain's size
    width = w;
    height = h;

    // Initializes cube geometry and transfers it to VBOs
    init();
}

Terrain::~Terrain()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}

void Terrain::init() {
    nbOfVertices = 2;

    // Init vertices
    VertexData *vertices = new VertexData[nbOfVertices*nbOfVertices] ;

    vertices[0] = {QVector3D(-width/2, -height/2, 0) , QVector2D(0, 0)} ;
    vertices[1] = {QVector3D(-width/2, height/2, 0) , QVector2D(0, 1)} ;
    vertices[2] = {QVector3D(width/2, -height/2, 0) , QVector2D(1, 0)} ;
    vertices[3] = {QVector3D(width/2, height/2, 0) , QVector2D(1, 1)} ;

    GLushort indices[] = { 2, 1, 0, 2, 1, 3 };

    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, nbOfVertices*nbOfVertices * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, 6 * sizeof(GLushort));
}

void Terrain::draw(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1

    glDrawElements(GL_TRIANGLE_STRIP,(nbOfVertices-1)*(nbOfVertices*2+4), GL_UNSIGNED_SHORT, 0);
}
