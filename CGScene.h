#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "CGShaderProgram.h"
#include "CGLight.h"
#include "CGMaterial.h"
#include "CGFigure.h"
#include "CGTrackStraight.h"
#include "CGTrackCurveLeft.h"
#include "CircuitBuilder.h"
#include "CGObject.h"
#include "CarController.h"

class CGScene {
public:
    CGScene();
    ~CGScene();
    void Draw(CGShaderProgram* program, glm::mat4 proj, glm::mat4 view);
    void Update(float dt);

    void AccelerateCar1();
    void BrakeCar1();
    void AccelerateCar2();
    void BrakeCar2();

    glm::mat4 GetCar1Transform() const;
    glm::mat4 GetCar2Transform() const;

private:
    CGLight* light;
    CGMaterial* matTrack;
    CircuitBuilder* circuito;
    CGMaterial* matg;
    CGFigure* ground;

    CGObject* rb;
    CGObject* rn;
    CarController* car1;
    CarController* car2;
};
