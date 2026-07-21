#pragma once

#include "CGObject.h"

class CarController
{
private:

    CGObject* car;

    float speed;
    float distance;

    float maxSpeed;

    float laneOffset;

public:

    CarController(CGObject* c, float lane);

    void Update(float dt);

    void Accelerate();

    void Brake();

    float GetDistance() const;

    float GetLaneOffset() const;

    CGObject* GetCar() const;
};
