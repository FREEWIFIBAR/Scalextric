#pragma once

#include "CGFigure.h"

class CGTrackCurveLeft : public CGFigure
{
public:

    CGTrackCurveLeft(
        float radioInterior,
        float radioExterior,
        float anguloDeg,
        float altura = 0.01f
    );
};
