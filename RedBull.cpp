#include "RedBull.h"
#include "RedBull_pieces.h"
#include <GL/glew.h>
#include "CGObject.h"
#include "CGPiece.h"

RedBull::RedBull()
{
	model = glm::mat4(1.0f);

	mtl[0] = new CGMaterial();
	mtl[0]->SetAmbientReflect(1.0f, 1.0f, 1.0f);
	mtl[0]->SetDifusseReflect(1.0f, 1.0f, 1.0f);
	mtl[0]->SetSpecularReflect(0.0f, 0.0f, 0.0f);
	mtl[0]->SetShininess(2.0f);
	mtl[0]->InitTexture("textures/RedBull/rb0_main.tga");

	mtl[1] = new CGMaterial();
	mtl[1]->SetAmbientReflect(1.0f, 1.0f, 1.0f);
	mtl[1]->SetDifusseReflect(1.0f, 1.0f, 1.0f);
	mtl[1]->SetSpecularReflect(0.0f, 0.0f, 0.0f);
	mtl[1]->SetShininess(2.0f);
	mtl[1]->InitTexture("textures/RedBull/generic_main.tga");

	mtl[2] = new CGMaterial();
	mtl[2]->SetAmbientReflect(1.0f, 1.0f, 1.0f);
	mtl[2]->SetDifusseReflect(1.0f, 1.0f, 1.0f);
	mtl[2]->SetSpecularReflect(0.0f, 0.0f, 0.0f);
	mtl[2]->SetShininess(2.0f);
	mtl[2]->InitTexture("textures/RedBull/rb0_wheel.tga");

	mtl[3] = new CGMaterial();
	mtl[3]->SetAmbientReflect(1.0f, 1.0f, 1.0f);
	mtl[3]->SetDifusseReflect(1.0f, 1.0f, 1.0f);
	mtl[3]->SetSpecularReflect(0.0f, 0.0f, 0.0f);
	mtl[3]->SetShininess(2.0f);
	mtl[3]->InitTexture("textures/RedBull/light_glow.tga");

	mtl[4] = new CGMaterial();
	mtl[4]->SetAmbientReflect(1.0f, 1.0f, 1.0f);
	mtl[4]->SetDifusseReflect(1.0f, 1.0f, 1.0f);
	mtl[4]->SetSpecularReflect(0.0f, 0.0f, 0.0f);
	mtl[4]->SetShininess(2.0f);
	mtl[4]->InitTexture("textures/RedBull/tyre.tga");

	mtl[5] = new CGMaterial();
	mtl[5]->SetAmbientReflect(1.0f, 1.0f, 1.0f);
	mtl[5]->SetDifusseReflect(1.0f, 1.0f, 1.0f);
	mtl[5]->SetSpecularReflect(0.0f, 0.0f, 0.0f);
	mtl[5]->SetShininess(2.0f);
	mtl[5]->InitTexture("textures/RedBull/tread_slick.tga");

	mtl[6] = new CGMaterial();
	mtl[6]->SetAmbientReflect(1.0f, 1.0f, 1.0f);
	mtl[6]->SetDifusseReflect(1.0f, 1.0f, 1.0f);
	mtl[6]->SetSpecularReflect(0.0f, 0.0f, 0.0f);
	mtl[6]->SetShininess(2.0f);
	mtl[6]->InitTexture("textures/RedBull/glass.tga");

	pieces[0] = new RedBull_0(mtl[0]);
	pieces[1] = new RedBull_1(mtl[1]);
	pieces[2] = new RedBull_2(mtl[1]);
	pieces[3] = new RedBull_3(mtl[1]);
	pieces[4] = new RedBull_4(mtl[1]);
	pieces[5] = new RedBull_5(mtl[1]);
	pieces[6] = new RedBull_6(mtl[1]);
	pieces[7] = new RedBull_7(mtl[1]);
	pieces[8] = new RedBull_8(mtl[1]);
	pieces[9] = new RedBull_9(mtl[1]);
	pieces[10] = new RedBull_10(mtl[1]);
	pieces[11] = new RedBull_11(mtl[1]);
	pieces[12] = new RedBull_12(mtl[1]);
	pieces[13] = new RedBull_13(mtl[1]);
	pieces[14] = new RedBull_14(mtl[1]);
	pieces[15] = new RedBull_15(mtl[0]);
	pieces[16] = new RedBull_16(mtl[0]);
	pieces[17] = new RedBull_17(mtl[0]);
	pieces[18] = new RedBull_18(mtl[2]);
	pieces[19] = new RedBull_19(mtl[2]);
	pieces[20] = new RedBull_20(mtl[2]);
	pieces[21] = new RedBull_21(mtl[2]);
	pieces[22] = new RedBull_22(mtl[0]);
	pieces[23] = new RedBull_23(mtl[0]);
	pieces[24] = new RedBull_24(mtl[0]);
	pieces[25] = new RedBull_25(mtl[3]);
	pieces[26] = new RedBull_26(mtl[1]);
	pieces[27] = new RedBull_27(mtl[1]);
	pieces[28] = new RedBull_28(mtl[1]);
	pieces[29] = new RedBull_29(mtl[1]);
	pieces[30] = new RedBull_30(mtl[0]);
	pieces[31] = new RedBull_31(mtl[0]);
	pieces[32] = new RedBull_32(mtl[0]);
	pieces[33] = new RedBull_33(mtl[0]);
	pieces[34] = new RedBull_34(mtl[0]);
	pieces[35] = new RedBull_35(mtl[0]);
	pieces[36] = new RedBull_36(mtl[1]);
	pieces[37] = new RedBull_37(mtl[1]);
	pieces[38] = new RedBull_38(mtl[1]);
	pieces[39] = new RedBull_39(mtl[1]);
	pieces[40] = new RedBull_40(mtl[0]);
	pieces[41] = new RedBull_41(mtl[1]);
	pieces[42] = new RedBull_42(mtl[1]);
	pieces[43] = new RedBull_43(mtl[1]);
	pieces[44] = new RedBull_44(mtl[1]);
	pieces[45] = new RedBull_45(mtl[4]);
	pieces[46] = new RedBull_46(mtl[5]);
	pieces[47] = new RedBull_47(mtl[4]);
	pieces[48] = new RedBull_48(mtl[5]);
	pieces[49] = new RedBull_49(mtl[4]);
	pieces[50] = new RedBull_50(mtl[5]);
	pieces[51] = new RedBull_51(mtl[4]);
	pieces[52] = new RedBull_52(mtl[5]);
	pieces[53] = new RedBull_53(mtl[0]);
	pieces[54] = new RedBull_54(mtl[0]);
	pieces[55] = new RedBull_55(mtl[1]);
	pieces[56] = new RedBull_56(mtl[0]);
	pieces[57] = new RedBull_57(mtl[0]);
	pieces[58] = new RedBull_58(mtl[0]);
	pieces[59] = new RedBull_59(mtl[0]);
	pieces[60] = new RedBull_60(mtl[0]);
	pieces[61] = new RedBull_61(mtl[0]);
	pieces[62] = new RedBull_62(mtl[0]);
	pieces[63] = new RedBull_63(mtl[6]);
	pieces[64] = new RedBull_64(mtl[0]);
	pieces[65] = new RedBull_65(mtl[0]);
	pieces[66] = new RedBull_66(mtl[0]);
	pieces[67] = new RedBull_67(mtl[1]);
}

RedBull::~RedBull()
{
	for (int i = 0; i < 68; i++) delete pieces[i];
	delete[] pieces;
	for (int i = 0; i < 7; i++) delete mtl[i];
	delete[] mtl;
}

int RedBull::GetNumPieces()
{
	return 68;
}

CGPiece* RedBull::GetPiece(int index)
{
	return pieces[index];
}

