#pragma once

#include <GL/glew.h>
#include "CGObject.h"
#include "CGPiece.h"

class Renault : public CGObject {
private:
	CGMaterial* mtl[7];
	CGPiece* pieces[69];

public:
	Renault();
	~Renault();
	virtual int GetNumPieces();
	virtual CGPiece* GetPiece(int i);
};

