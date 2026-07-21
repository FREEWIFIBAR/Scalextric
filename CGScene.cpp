#include "CGScene.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "CGShaderProgram.h"
#include "CGFigure.h"
#include "CGLight.h"
#include "CGMaterial.h"
#include "CGObject.h"
#include "RedBull.h"
#include "Renault.h"
#include "CGGround.h"
#include "resource.h"

//
// FUNCIÓN: CGScene::CGScene()
//
// PROPÓSITO: Construye el objeto que representa la escena
//
CGScene::CGScene()
{
    glm::vec3 Ldir = glm::vec3(1.0f, -0.8f, -1.0f);
    Ldir = glm::normalize(Ldir);
    light = new CGLight();
    light->SetLightDirection(Ldir);
    light->SetAmbientLight(glm::vec3(0.2f, 0.2f, 0.2f));
    light->SetDifusseLight(glm::vec3(0.8f, 0.8f, 0.8f));
    light->SetSpecularLight(glm::vec3(1.0f, 1.0f, 1.0f));

    matg = new CGMaterial();
    matg->SetAmbientReflect(1.0f, 1.0f, 1.0f);
    matg->SetDifusseReflect(1.0f, 1.0f, 1.0f);
    matg->SetSpecularReflect(0.0f, 0.0f, 0.0f);
    matg->SetShininess(16.0f);
    matg->InitTexture("textures/grass.jpg");

    ground = new CGGround(2.5f, 2.5f);
    ground->Translate(glm::vec3(1.0f, -0.01f, 1.40f));
    ground->SetMaterial(matg);

    matTrack = new CGMaterial();
    matTrack->SetAmbientReflect(1.0f, 1.0f, 1.0f);
    matTrack->SetDifusseReflect(1.0f, 1.0f, 1.0f);
    matTrack->SetSpecularReflect(0.0f, 0.0f, 0.0f);
    matTrack->SetShininess(16.0f);
    matTrack->InitTexture("textures/RectaStd.png");

    circuito = new CircuitBuilder(matTrack, matTrack);
    
    for (int i = 0; i < 2; i++)
    {
        for (int i = 0; i < 8; i++)
        {
            circuito->AddStraight();
        }
        for (int i = 0; i < 2; i++)
        {
            circuito->AddCurveLeft();
        }
        for (int i = 0; i < 4; i++)
        {
            circuito->AddStraight();
        }
        for (int i = 0; i < 2; i++)
        {
            circuito->AddCurveLeft();
        }
    }

    rb = new RedBull();
    rn = new Renault();

    car1 = new CarController(rb, -0.039f);
    car2 = new CarController(rn, +0.039f);
}

//
// FUNCIÓN: CGScene3:~CGScene()
//
// PROPÓSITO: Destruye el objeto que representa la escena
//
CGScene::~CGScene()
{
    delete light;
    delete matTrack;
    delete circuito;
    delete matg;
    delete ground;
    delete rb;
    delete rn;
    delete car1;
    delete car2;
}

//
// FUNCIÓN: CGScene::Draw()
//
// PROPÓSITO: Dibuja la escena
//
void CGScene::Draw(CGShaderProgram* program, glm::mat4 proj, glm::mat4 view)
{
    light->SetUniforms(program);

    ground->Draw(program, proj, view);

    circuito->Draw(program, proj, view);

    rb->Draw(program, proj, view);

    rn->Draw(program, proj, view);
}

void CGScene::Update(float dt)
{
    car1->Update(dt);
    car2->Update(dt);

    car1->GetCar()->SetLocation(
        circuito->GetTransform(
            car1->GetDistance(),
            car1->GetLaneOffset()
        )
    );

    rb->Rotate(-90.0f, glm::vec3(1, 0, 0));

    car2->GetCar()->SetLocation(
        circuito->GetTransform(
            car2->GetDistance(),
            car2->GetLaneOffset()
        )
    );

    rn->Rotate(-90.0f, glm::vec3(1, 0, 0));
}

void CGScene::AccelerateCar1()
{
    car1->Accelerate();
}

void CGScene::BrakeCar1()
{
    car1->Brake();
}

void CGScene::AccelerateCar2()
{
    car2->Accelerate();
}

void CGScene::BrakeCar2()
{
    car2->Brake();
}

glm::mat4 CGScene::GetCar1Transform() const
{
    return car1->GetCar()->GetLocation();
}

glm::mat4 CGScene::GetCar2Transform() const
{
    return car2->GetCar()->GetLocation();
}
