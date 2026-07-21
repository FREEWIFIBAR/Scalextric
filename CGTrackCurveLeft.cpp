#include "CGTrackCurveLeft.h"

#include <cmath>
#include <glm/glm.hpp>

CGTrackCurveLeft::CGTrackCurveLeft(float radioInterior, float radioExterior, float anguloDeg, float altura)
{
    const int segmentos = 32;

    float h = altura * 0.5f;
    float anguloRad = glm::radians(anguloDeg);

    numVertices = (segmentos + 1) * 2;
    numFaces = segmentos * 2;

    vertices = new GLfloat[numVertices * 3];
    normals = new GLfloat[numVertices * 3];
    textures = new GLfloat[numVertices * 2];
    indexes = new GLushort[numFaces * 3];

    //----------------------------------
    // VERTICES
    //----------------------------------

    for (int i = 0; i <= segmentos; i++)
    {
        float t = (float)i / segmentos;

        float a = t * anguloRad;

        float radioMedio = (radioInterior + radioExterior) * 0.5f;

        float xIn = radioInterior * sin(a);
        float zIn = radioInterior * cos(a) - radioMedio;

        float xOut = radioExterior * sin(a);
        float zOut = radioExterior * cos(a) - radioMedio;

        int v = i * 2;

        //--------------------------------
        // Interior
        //--------------------------------

        vertices[v * 3 + 0] = xIn;
        vertices[v * 3 + 1] = h;
        vertices[v * 3 + 2] = zIn;

        normals[v * 3 + 0] = 0.0f;
        normals[v * 3 + 1] = 1.0f;
        normals[v * 3 + 2] = 0.0f;

        textures[v * 2 + 0] = 0.0f;
        textures[v * 2 + 1] = t;

        //--------------------------------
        // Exterior
        //--------------------------------

        vertices[(v + 1) * 3 + 0] = xOut;
        vertices[(v + 1) * 3 + 1] = h;
        vertices[(v + 1) * 3 + 2] = zOut;

        normals[(v + 1) * 3 + 0] = 0.0f;
        normals[(v + 1) * 3 + 1] = 1.0f;
        normals[(v + 1) * 3 + 2] = 0.0f;

        textures[(v + 1) * 2 + 0] = 1.0f;
        textures[(v + 1) * 2 + 1] = t;
    }

    //----------------------------------
    // INDICES
    //----------------------------------

    int k = 0;

    for (int i = 0; i < segmentos; i++)
    {
        int v0 = i * 2;
        int v1 = v0 + 1;
        int v2 = v0 + 2;
        int v3 = v0 + 3;

        indexes[k++] = v0;
        indexes[k++] = v1;
        indexes[k++] = v2;

        indexes[k++] = v1;
        indexes[k++] = v3;
        indexes[k++] = v2;
    }

    InitBuffers();
}
