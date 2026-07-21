#pragma once

#include <vector>

#include "CGTrackStraight.h"
#include "CGTrackCurveLeft.h"
#include "CGMaterial.h"

struct TrackSegment
{
    glm::mat4 transform;
    float length;

    enum Type
    {
        STRAIGHT,
        CURVE_LEFT
    };

    Type type;

    float radius;
    float angle;
};

class CircuitBuilder
{
private:

    std::vector<CGFigure*> pieces;

    glm::mat4 currentTransform;

    CGMaterial* straightMaterial;
    CGMaterial* curveMaterial;

    std::vector<TrackSegment> segments;

public:

    CircuitBuilder(
        CGMaterial* straightMat,
        CGMaterial* curveMat
    );

    void AddStraight();
    void AddHalfStraight();
    void AddQuarterStraight();

    void AddCurveLeft();

    void Draw(
        CGShaderProgram* program,
        glm::mat4 projection,
        glm::mat4 view
    );

    float GetTotalLength() const;
    glm::mat4 GetTransform(float distance, float laneOffset);
};
