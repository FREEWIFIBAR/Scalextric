#include "CarController.h"

CarController::CarController(CGObject* c, float lane)
{
    car = c;

    speed = 0.0f;
    distance = 0.0f;

    maxSpeed = 2.0f;

    laneOffset = lane;
}

void CarController::Update(float dt)
{
    distance += speed * dt;
}

void CarController::Accelerate()
{
    speed += maxSpeed / 10.0f;

    if (speed > maxSpeed)
        speed = maxSpeed;
}

void CarController::Brake()
{
    speed -= maxSpeed / 10.0f;

    if (speed < 0.0f)
        speed = 0.0f;
}

float CarController::GetDistance() const
{
    return distance;
}

float CarController::GetLaneOffset() const
{
    return laneOffset;
}

CGObject* CarController::GetCar() const
{
    return car;
}
