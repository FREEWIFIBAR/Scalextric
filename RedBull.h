#pragma once

#include <GL/glew.h>
#include "CGObject.h"
#include "CGPiece.h"

class RedBull : public CGObject {
private:
	CGMaterial* mtl[7];
	CGPiece* pieces[68];

public:
	RedBull();
	~RedBull();
	virtual int GetNumPieces();
	virtual CGPiece* GetPiece(int i);
};

