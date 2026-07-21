#pragma once

#include <GL/glew.h>
#include "CGShaderProgram.h"
#include "CGScene.h"
#include "CGSkybox.h"
#include "CGCamera.h"

enum CameraMode
{
	CAMERA_OVERVIEW,
	CAMERA_CAR1,
	CAMERA_CAR2
};

class CGModel
{
public:
	void initialize(int w, int h);
	void finalize();
	void render();
	void update();
	void key_pressed(int key);
	void mouse_button(int button, int action);
	void mouse_move(double xpos, double ypos);
	void resize(int w, int h);
	void UpdateCamera(glm::mat4 carTransform);

private:
	CGShaderProgram* sceneProgram;
	CGShaderProgram* skyboxProgram;
	CGScene* scene;
	CGCamera* camera;
	CGSkybox* skybox;
	glm::mat4 projection;
	CameraMode cameraMode;
	void CameraConstraints();
};
