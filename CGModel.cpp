#include "CGModel.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "CGCamera.h"
#include "CGScene.h"
#include "CGSkybox.h"
#include "resource.h"


//
// FUNCIÓN: CGModel::initialize(int, int)
//
// PROPÓSITO: Initializa el modelo 3D
//
void CGModel::initialize(int w, int h)
{
    // Crea el programa gráfico para la escena
    sceneProgram = new CGShaderProgram(IDR_SHADER1, IDR_SHADER2, -1, -1, -1);
    if (sceneProgram->IsLinked() == GL_FALSE) return;

    // Crea el programa gráfico para el entorno
    // skyboxProgram = new CGShaderProgram("shaders/SkyboxVertexShader.glsl", "shaders/SkyboxFragmentShader.glsl", NULL, NULL, NULL);
    skyboxProgram = new CGShaderProgram(IDR_SHADER3, IDR_SHADER4, -1, -1, -1);
    if (skyboxProgram->IsLinked() == GL_FALSE) return;

    // Crea la cámara
    camera = new CGCamera();
    cameraMode = CAMERA_OVERVIEW;

    // Crea el skybox
    skybox = new CGSkybox();

    // Crea la escena
    scene = new CGScene();

    // Asigna el viewport y el clipping volume
    resize(w, h);

    // Opciones de dibujo
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

//
// FUNCIÓN: CGModel::finalize()
//
// PROPÓSITO: Libera los recursos del modelo 3D
//
void CGModel::finalize()
{
    delete camera;
    delete scene;
    delete skybox;
    delete sceneProgram;
    delete skyboxProgram;
}

//
// FUNCIÓN: CGModel::resize(int w, int h)
//
// PROPÓSITO: Asigna el viewport y el clipping volume
//
void CGModel::resize(int w, int h)
{
    double fov = glm::radians(15.0);
    double sin_fov = sin(fov);
    double cos_fov = cos(fov);
    if (h == 0) h = 1;
    GLfloat aspectRatio = (GLfloat)w / (GLfloat)h;
    GLfloat wHeight = (GLfloat)(sin_fov * 0.2 / cos_fov);
    GLfloat wWidth = wHeight * aspectRatio;

    glViewport(0, 0, w, h);
    projection = glm::frustum(-wWidth, wWidth, -wHeight, wHeight, 0.2f, 400.0f);
}

//
// FUNCIÓN: CGModel::render()
//
// PROPÓSITO: Genera la imagen
//
void CGModel::render()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = camera->ViewMatrix();
    skyboxProgram->Use();
    skybox->Draw(skyboxProgram, projection, view);
    sceneProgram->Use();
    scene->Draw(sceneProgram, projection, view);
}

//
// FUNCIÓN: CGModel::update()
//
// PROPÓSITO: Anima la escena
//
void CGModel::update()
{
    scene->Update(1.0f / 60.0f);

    switch (cameraMode)
    {
    case CAMERA_OVERVIEW:
        camera->SetPosition(
            1.0f,   // centro del circuito en X
            1.3f,   // altura
            -2.0f   // detras del inicio
        );

        camera->LookAt(
            glm::vec3(1.0f, 2.0f, -2.8f),
            glm::vec3(1.0f, 0.0f, 1.4f),   // centro aproximado del circuito
            glm::vec3(0, 1, 0)
        );
        break;

    case CAMERA_CAR1:
        UpdateCamera(scene->GetCar1Transform());
        break;

    case CAMERA_CAR2:
        UpdateCamera(scene->GetCar2Transform());
        break;
    }
}

//
// FUNCIÓN: CGModel::key_pressed(int)
//
// PROPÓSITO: Respuesta a acciones de teclado
//
void CGModel::key_pressed(int key)
{
    switch (key)
    {
    case GLFW_KEY_Q:
        scene->AccelerateCar1();
        break;

    case GLFW_KEY_A:
        scene->BrakeCar1();
        break;

    case GLFW_KEY_O:
        scene->AccelerateCar2();
        break;

    case GLFW_KEY_L:
        scene->BrakeCar2();
        break;

    case GLFW_KEY_F1:
        cameraMode = CAMERA_OVERVIEW;
        break;

    case GLFW_KEY_F2:
        cameraMode = CAMERA_CAR1;
        break;

    case GLFW_KEY_F3:
        cameraMode = CAMERA_CAR2;
        break;
    }
}

//
//  FUNCIÓN: CGModel:::mouse_button(int button, int action)
//
//  PROPÓSITO: Respuesta del modelo a un click del ratón.
//
void CGModel::mouse_button(int button, int action)
{
}

//
//  FUNCIÓN: CGModel::mouse_move(double xpos, double ypos)
//
//  PROPÓSITO: Respuesta del modelo a un movimiento del ratón.
//
void CGModel::mouse_move(double xpos, double ypos)
{
}

//
//  FUNCIÓN: CGModel::CameraConstraints()
//
//  PROPÓSITO: Limita el movimiento de la cámara a una cierta zona
//
void CGModel::CameraConstraints()
{
    glm::vec3 pos = camera->GetPosition();
    int constraint = 0;
    if (pos.y < 1.0f) { pos.y = 1.0f; constraint = 1; }
    if (pos.y > 40.0f) { pos.y = 40.0f; constraint = 1; }
    if (pos.x > 100.0f) { pos.x = 100.0f; constraint = 1; }
    if (pos.x < -100.0f) { pos.x = -100.0f; constraint = 1; }
    if (pos.z > 100.0f) { pos.z = 100.0f; constraint = 1; }
    if (pos.z < -100.0f) { pos.z = -100.0f; constraint = 1; }
    if (constraint == 1)
    {
        camera->SetPosition(pos.x, pos.y, pos.z);
        camera->SetMoveStep(0.0f);
    }

}

void CGModel::UpdateCamera(glm::mat4 carTransform)
{
    glm::vec3 pos = glm::vec3(carTransform[3]);

    // Eje delantero del coche
    glm::vec3 forward =
        -glm::normalize(glm::vec3(carTransform * glm::vec4(0, 1, 0, 0)));

    // Eje vertical del coche
    glm::vec3 up =
        glm::normalize(glm::vec3(carTransform * glm::vec4(0, 0, 1, 0)));

    glm::vec3 eye =
        pos
        - forward * 0.55f
        + up * 0.15f;

    glm::vec3 target =
        pos
        + forward * 0.60f;

    camera->LookAt(eye, target, up);
}
