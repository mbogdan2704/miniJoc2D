#include "Laborator3.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"

using namespace std;
float tx = 0;
float ty = 0;
float l = 50;
float lungimeMediana;
float angle;
float angle2 = AI_MATH_PI/2;
float mousex;
float mousey;
int ok = 1;
int lock = 0;
int atins = 0;
float go =0;
float stop = 0;
glm::ivec2 resolution;
int numberOfSteps = 0;
float deltax, deltay;
glm::vec3 corner = glm::vec3(0, 0, 0);
glm::vec3 corner_asteroid1 = glm::vec3(0, 0, 0);
glm::vec3 corner_platforma_stationare = glm::vec3(200, 400, 0);
glm::vec3 corner_platforma_reflexie = glm::vec3(700, 500, 0);
glm::vec3 corner_platforma_finala = glm::vec3(900, 100, 0);
glm::vec3 corner_asteroid2 = glm::vec3(700, 200, 0);
glm::vec3 corner_asteroid3 = glm::vec3(-(l/2/1.8), -(2*l/1.8*0.8), 0);
float ast2x, ast2y;
int flag = 0;
float sx = 1;
float sy = 1;
float xup, yup;
int step = 2;
int flag2 = 1;
int asteroid1 = 1;
int asteroid2 = 1;	
int asteroid3 = 1;
Laborator3::Laborator3()
{
}

Laborator3::~Laborator3()
{
}

void Laborator3::Init()
{
	resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	float squareSide = 100;

	// compute coordinates of square center
	float cx = corner.x + squareSide / 2;
	float cy = corner.y + squareSide / 2;

	// initialize tx and ty (the translation steps)
	translateX = 0;
	translateY = 0;

	// initialize sx and sy (the scale factors)
	scaleX = 1;
	scaleY = 1;

	// initialize angularStep
	angularStep = 0;
    lungimeMediana = sqrt(pow(l, 2) - pow(l / 2, 2));
     yup = (2 * lungimeMediana / 3);
	 xup = 0;
	float x_leftCorner = (0 - l / 2);
	float x_rightCorner = (0 + l / 2);
	float y_leftCorner = -(1 * lungimeMediana / 3);
	float y_rightCorner = -(1 * lungimeMediana / 3);

	glm::vec3 leftCorner = glm::vec3(x_leftCorner, y_leftCorner, 0);
	glm::vec3 rightCorner = glm::vec3(x_rightCorner, y_rightCorner, 0);
	glm::vec3 upCorner = glm::vec3(xup, yup, 0);
	Mesh* triangle = Object2D::CreateTriangle("triangle", leftCorner,
		 rightCorner, upCorner, l, glm::vec3(1, 0, 0), true);
	AddMeshToList(triangle);
	Mesh* asteroid1 = Object2D::CreateAsteroid("asteroid1", corner_asteroid1, l, glm::vec3(1, 1, 0), true);
	AddMeshToList(asteroid1);
	Mesh* asteroid2 = Object2D::CreateAsteroid("asteroid2", corner_asteroid2, l, glm::vec3(1, 1, 1), true);
	AddMeshToList(asteroid2);
	Mesh* asteroid3 = Object2D::CreateAsteroid("asteroid3", corner_asteroid3, l, glm::vec3(1, 1, 1), true);
	AddMeshToList(asteroid3);
	
	Mesh* platforma_stationare = Object2D::CreatePlatforma("platforma_stationare", corner_platforma_stationare, l, glm::vec3(1, 0, 0), true);
	AddMeshToList(platforma_stationare);
	Mesh* platforma_reflexie = Object2D::CreatePlatforma("platforma_reflexie", corner_platforma_reflexie, l, glm::vec3(0, 1, 0), true);
	AddMeshToList(platforma_reflexie);
	Mesh* platforma_finala = Object2D::CreatePlatforma("platforma_finala", corner_platforma_finala, l, glm::vec3(0, 0, 1), true);
	AddMeshToList(platforma_finala);
	

}

void Laborator3::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}


void Laborator3::Update(float deltaTimeSeconds)
{
	
	if (ok == 1) {


		modelMatrix = glm::mat3(1);
		float mediana = sqrt(pow(l, 2) - pow(l / 2, 2));
		float raza = (2 * mediana / 3);
		numberOfSteps++;



		if (go == 0) {

			deltax = mousex - tx;
			deltay = mousey - ty;
			go = 1;
			deltax = deltax / 120 * (resolution.x / resolution.y);
			deltay = deltay / 120;
		}

		if (lock == 1)
		{

			tx += deltax;
			ty += deltay;
			xup += deltax;
			yup += deltay;


		}

		if (tx + deltax > resolution.x  && numberOfSteps > 100)
		{
			lock = 0;
			atins = 1;
			angle = AI_MATH_PI / 2;
			xup = resolution.x - mediana;
			yup = ty;


		}
		if (ty + deltay > resolution.y && numberOfSteps > 100)
		{

			lock = 0;
			atins = 1;
			angle = AI_MATH_PI;
			xup = tx;
			yup = resolution.y - mediana;
		}
		if (tx - deltax < 0 && atins == 1 && numberOfSteps > 100)
		{
			lock = 0;
			angle = -AI_MATH_PI / 2;
			xup = mediana;
			yup = ty;

		}
		if (ty - deltay < 0 && atins == 1 && numberOfSteps > 100)
		{

			lock = 0;
			angle = 0;
			xup = tx;
			yup = mediana;
		}



		if (xup >= 200 && xup <= (200 + l * 4) && yup >= 400 && yup <= (400 + l / 3)) //Intersectia cu platforma de stationare
		{
			lock = 0;
			if (yup <= (400 + l / 6))
			{

				angle = AI_MATH_PI;
				ty += 400 - ty - mediana / 3;
				xup = tx;
				yup = ty - 2 * mediana / 3;
				atins = 1;
			}

			if (yup >= (400 + l / 6))
			{

				angle = 0;

				ty -= (ty - (400 + l / 3));
				ty += 1 * mediana / 3;

				xup = tx;
				yup = ty + 2 * mediana / 3;
				atins = 1;
			}
		}
		if (tx + raza >= 200 && (tx + raza) <= (200 + l * 4) && ty >= 400 && ty <= (400 + l / 3))
		{
			lock = 0;
			angle = AI_MATH_PI;
			ty += 400 - ty - mediana / 3;
			xup = tx;
			yup = ty - 2 * mediana / 3;
			atins = 1;

		}

		if (tx - raza >= 200 && (tx - raza) <= (200 + l * 4) && ty >= 400 && ty <= (400 + l / 3))
		{
			lock = 0;
			angle = AI_MATH_PI;
			ty += 400 - ty - mediana / 3;
			xup = tx;
			yup = ty - 2 * mediana / 3;
			atins = 1;

		}
		if ((xup >= 700 && xup <= (700 + l * 4) && yup >= 500 && yup <= (500 + l / 3)) //Intersectia cu platforma de reflexie
			|| (tx >= 700 && tx <= (700 + l * 4) && ty >= 500 && ty <= (500 + l / 3)))
		{

			if (yup <= (500 + l / 6)) //cand vine de jos in sus
			{
				if (angle < 0) {  //cand vine din stanga

					deltay = -deltay;
					//angle = -(AI_MATH_PI / 2 - angle);
					angle -= AI_MATH_PI / 2;
					atins = 1;
				}
				if (angle > 0) { //cand vine din dreapta
					deltay = -deltay;
					angle += AI_MATH_PI / 2;
					atins = 1;
				}
			}

			if (yup >= (500 + l / 6))
			{
				if (angle > 0) {

					angle -= AI_MATH_PI / 2;
					deltay = -deltay;
					atins = 1;
				}
				if (angle < 0) {

					angle += AI_MATH_PI / 2;
					deltay = -deltay;
					atins = 1;
				}
			}

		}



		modelMatrix *= Transform2D::Translate(tx, ty);
		modelMatrix *= Transform2D::Rotate(angle);




		RenderMesh2D(meshes["triangle"], shaders["VertexColor"], modelMatrix);
		//Platforma de stationare
		modelMatrix = glm::mat3(1);
		RenderMesh2D(meshes["platforma_stationare"], shaders["VertexColor"], modelMatrix);
	


		modelMatrix = glm::mat3(1);

		modelMatrix *= Transform2D::Translate(400, 100) * Transform2D::Scale(sx, sy);
		RenderMesh2D(meshes["asteroid1"], shaders["VertexColor"], modelMatrix);
		if (sx >= 2)
		{
			flag = 1;
		}
		if (sx <= 0.5)
		{
			flag = 0;
		}
		if (flag == 1) {
			modelMatrix *= Transform2D::Translate(400, 100) * Transform2D::Scale(sx, sy);
			sx -= 0.01;
			sy -= 0.01;
		}

		if (flag == 0) {
			sx += 0.01;
			sy += 0.01;
		}


		float xasteroid1 = (400 + sx*(l / 2 / 1.8));
		float yasteroid1 = (100 + sy * 2 * l / 1.8*0.8);
		float r1 = l / 2;
		float r2 = sy * 2 * l / 1.8*0.8;
		float dx = tx - xasteroid1;
		float dy = ty - yasteroid1;
		float distance = sqrt(dx*dx + dy*dy);
		if (distance < r1 + r2 && asteroid1 == 1)
		{
			lock = 0;
			meshes["asteroid1"] = 0;
			atins = 1;
			asteroid1 = 0;
		}



		modelMatrix = glm::mat3(1);
		RenderMesh2D(meshes["platforma_reflexie"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);

		ast2x += step;
		ast2y += 0;
		if (ast2x == 400 || ast2x == 0)
		{
			step *= (-1);
		}

		modelMatrix *= Transform2D::Translate(ast2x, ast2y);
		RenderMesh2D(meshes["asteroid2"], shaders["VertexColor"], modelMatrix);

		float xasteroid2 = (700 + ast2x + l / 2 / 1.8);
		float yasteroid2 = (200 + ast2y + 2 * l / 1.8*0.8);
		r1 = l / 2;
		r2 = 2 * l / 1.8*0.8;
		dx = tx - xasteroid2;
		dy = ty - yasteroid2;
		distance = sqrt(dx*dx + dy*dy);
		if (distance < r1 + r2 && asteroid2 == 1)
		{
			lock = 0;
			meshes["asteroid2"] = 0;
			atins = 1;
			asteroid2 = 0;
		}

		modelMatrix = glm::mat3(1);
		angle2 += AI_MATH_PI / 50;
		modelMatrix *= Transform2D::Translate(100, 600)*Transform2D::Rotate(angle2);

		float xasteroid3 = (100 + l / 2 / 1.8);
		float yasteroid3 = (600 + 2 * l / 1.8*0.8);
		r1 = l / 2;
		r2 = 2 * l / 1.8*0.8;
		dx = tx - xasteroid3;
		dy = ty - yasteroid3;
		distance = sqrt(dx*dx + dy*dy);
		if (distance < r1 + r2 && asteroid3 == 1)
		{
			lock = 0;
			meshes["asteroid3"] = 0;
			atins = 1;
			asteroid3 = 0;
		}

		RenderMesh2D(meshes["asteroid3"], shaders["VertexColor"], modelMatrix);



		modelMatrix = glm::mat3(1);
		RenderMesh2D(meshes["platforma_finala"], shaders["VertexColor"], modelMatrix);
		if (xup >= 900 && xup <= (900 + l * 4) && yup >= 100 && yup <= (100 + l / 3)) //Intersectia cu platforma finala
		{
			ok = 0 ;
		}
	}


}

void Laborator3::FrameEnd()
{

}

void Laborator3::OnInputUpdate(float deltaTime, int mods)
{

}

void Laborator3::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Laborator3::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
	mousex = mouseX;
    mousey = resolution.y - mouseY;
	angle = atan((mousey - ty) / (mousex - tx));
	if (mouseY >= ty) {
		if (mousex >= tx)
			angle -= AI_MATH_PI / 2;
		else
			angle += AI_MATH_PI / 2;
	}
	else {
		if (mousex >= tx)
			angle -= AI_MATH_PI / 2;
		else
			angle += AI_MATH_PI / 2;
	}
	
	glm::vec3 varfsus = glm::vec3(xup, yup, 0);
	glm::mat3 translate = glm::transpose(glm::mat3(1, 0, translateX,
										 0, 1, translateY,
		                                 0, 0, 1));
	varfsus = translate * varfsus;
	xup = varfsus.x;
	yup = varfsus.y;
	go = 0;
	lock = 1;
	flag2 = 1;
	numberOfSteps = 0;
}

void Laborator3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator3::OnWindowResize(int width, int height)
{
}
