#include "CircuitBuilder.h"
#include <glm/ext/matrix_transform.hpp>

CircuitBuilder::CircuitBuilder(CGMaterial* straightMat, CGMaterial* curveMat)
{
    currentTransform = glm::mat4(1.0f);

    straightMaterial = straightMat;
    curveMaterial = curveMat;
}

void CircuitBuilder::AddStraight()
{
    const float L = 0.350f;

    CGTrackStraight* piece =
        new CGTrackStraight(
            0.156f,
            L,
            0.001f
        );

    piece->SetMaterial(straightMaterial);

    piece->SetLocation(currentTransform);

    pieces.push_back(piece);

    glm::mat4 step(1.0f);

    step = glm::translate(
        step,
        glm::vec3(
            0.0f,
            0.0f,
            L
        )
    );

    TrackSegment s;

    s.transform = currentTransform;
    s.length = 0.350f;
    s.type = TrackSegment::STRAIGHT;

    segments.push_back(s);

    currentTransform = currentTransform * step;
}

void CircuitBuilder::AddHalfStraight()
{
    const float L = 0.175f;

    CGTrackStraight* piece =
        new CGTrackStraight(
            0.156f,
            L,
            0.01f
        );

    piece->SetMaterial(straightMaterial);

    piece->SetLocation(currentTransform);

    pieces.push_back(piece);

    glm::mat4 step(1.0f);

    step = glm::translate(
        step,
        glm::vec3(0.0f, 0.0f, L)
    );

    currentTransform = currentTransform * step;
}

void CircuitBuilder::AddQuarterStraight()
{
    const float L = 0.0875f;

    CGTrackStraight* piece =
        new CGTrackStraight(
            0.156f,
            L,
            0.01f
        );

    piece->SetMaterial(straightMaterial);

    piece->SetLocation(currentTransform);

    pieces.push_back(piece);

    glm::mat4 step(1.0f);

    step = glm::translate(
        step,
        glm::vec3(0.0f, 0.0f, L)
    );

    currentTransform = currentTransform * step;
}

void CircuitBuilder::AddCurveLeft()
{
    CGTrackCurveLeft* piece =
        new CGTrackCurveLeft(
            0.214f,
            0.370f,
            45.0f,
            0.001f
        );

    piece->SetMaterial(curveMaterial);

    glm::mat4 m = currentTransform;

    m = glm::rotate(
        m,
        glm::radians(-90.0f),
        glm::vec3(0, 1, 0)
    );

    piece->SetLocation(m);

    pieces.push_back(piece);

    glm::mat4 step(1.0f);

    step = glm::translate(
        step,
        glm::vec3(0.085525f, 0.0f, 0.206475f)
    );

    step = glm::rotate(
        step,
        glm::radians(45.0f),
        glm::vec3(0, 1, 0)
    );

    TrackSegment s;

    s.transform = m;
    s.type = TrackSegment::CURVE_LEFT;
    s.radius = 0.292f;
    s.angle = glm::radians(45.0f);
    s.length = s.radius * s.angle;

    segments.push_back(s);

    currentTransform = currentTransform * step;
}

void CircuitBuilder::Draw(CGShaderProgram* program, glm::mat4 projection, glm::mat4 view)
{
    for (auto p : pieces)
    {
        p->Draw(program, projection, view);
    }
}

float CircuitBuilder::GetTotalLength() const
{
    float total = 0.0f;

    for (const auto& s : segments)
        total += s.length;

    return total;
}

glm::mat4 CircuitBuilder::GetTransform(float distance, float laneOffset)
{
    float total = GetTotalLength();

    while (distance < 0.0f)
        distance += total;

    while (distance >= total)
        distance -= total;

    for (const auto& s : segments)
    {
        if (distance <= s.length)
        {
            if (s.type == TrackSegment::STRAIGHT)
            {
                glm::mat4 m = s.transform;

                m = glm::translate(
                    m,
                    glm::vec3(laneOffset, 0.01f, distance)
                );

                return m;
            }

            if (s.type == TrackSegment::CURVE_LEFT)
            {
                float t = distance / s.length;
                float a = t * s.angle;
                float r = (laneOffset > 0.0f) ? 0.253f : 0.331f;

                const float centerOffset = 0.292f;
                float x = r * sin(a);
                float z = r * cos(a) - centerOffset;

                glm::mat4 m = s.transform;

                m = glm::translate(
                    m,
                    glm::vec3(x, 0.01f, z)
                );

                m = glm::rotate(
                    m,
                    a + glm::radians(90.0f),
                    glm::vec3(0, 1, 0)
                );

                return m;
            }
        }

        distance -= s.length;
    }

    return glm::mat4(1.0f);
}
