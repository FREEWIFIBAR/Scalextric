#include "CGTrackStraight.h"

CGTrackStraight::CGTrackStraight(float width, float length, float height)
{
    float w = width * 0.5f;
    float l = length;
    float h = height * 0.5f;

    numFaces = 12;
    numVertices = 24;

    GLfloat p_vertices[24][3] =
    {
        { +w,+h,l }, { +w,-h,l }, { +w,-h,0 }, { +w,+h,0 },
        { -w,+h,l }, { +w,+h,l }, { +w,+h,0 }, { -w,+h,0 },
        { -w,-h,l }, { -w,+h,l }, { -w,+h,0 }, { -w,-h,0 },
        { +w,-h,l }, { -w,-h,l }, { -w,-h,0 }, { +w,-h,0 },
        { +w,+h,l }, { -w,+h,l }, { -w,-h,l }, { +w,-h,l },
        { +w,+h,0 }, { +w,-h,0 }, { -w,-h,0 }, { -w,+h,0 }
    };

    GLfloat p_normals[24][3] =
    {
        { 1,0,0 },{ 1,0,0 },{ 1,0,0 },{ 1,0,0 },
        { 0,1,0 },{ 0,1,0 },{ 0,1,0 },{ 0,1,0 },
        {-1,0,0 },{-1,0,0 },{-1,0,0 },{-1,0,0 },
        { 0,-1,0},{ 0,-1,0},{ 0,-1,0},{ 0,-1,0},
        { 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },
        { 0,0,-1},{ 0,0,-1},{ 0,0,-1},{ 0,0,-1}
    };

    GLfloat p_textures[24][2] =
    {
        {0,0},{1,0},{1,1},{0,1},
        {0,0},{1,0},{1,1},{0,1},
        {0,0},{1,0},{1,1},{0,1},
        {0,0},{1,0},{1,1},{0,1},

        {0,0},
        {1,0},
        {1,4},
        {0,4},

        {0,0},{1,0},{1,1},{0,1}
    };

    GLushort p_indexes[12][3] =
    {
        {0,1,2},{0,2,3},
        {4,5,6},{4,6,7},
        {8,9,10},{8,10,11},
        {12,13,14},{12,14,15},
        {16,17,18},{16,18,19},
        {20,21,22},{20,22,23}
    };

    vertices = new GLfloat[numVertices * 3];
    normals = new GLfloat[numVertices * 3];
    textures = new GLfloat[numVertices * 2];
    indexes = new GLushort[numFaces * 3];

    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            vertices[3 * i + j] = p_vertices[i][j];
            normals[3 * i + j] = p_normals[i][j];
        }

        for (int j = 0; j < 2; j++)
            textures[2 * i + j] = p_textures[i][j];
    }

    for (int i = 0; i < numFaces; i++)
        for (int j = 0; j < 3; j++)
            indexes[3 * i + j] = p_indexes[i][j];

    InitBuffers();
}
