#include "Object2D.h"

#include <Core/Engine.h>

Mesh* Object2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Object2D::CreateTriangle(std::string name, glm::vec3 leftBottomCorner,
	glm::vec3 rightButtomCorner, glm::vec3 upCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{

		VertexFormat(leftBottomCorner, glm::vec3(1,0,0)),
		VertexFormat(rightButtomCorner, glm::vec3(0,1,0)),
		VertexFormat(upCorner, glm::vec3(0,0,1)),
	
	};
	
	Mesh* triangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2 };

	if (!fill) {
		triangle->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		//	indices.push_back(0);
		//	indices.push_back(2);
	}

	triangle->InitFromData(vertices, indices);
	return triangle;
}

Mesh* Object2D::CreateAsteroid(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;
	length = length / 1.8;
	float lengthy = length * 0.8;
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner + glm::vec3(length / 2, 2 * lengthy, 0), color), //0
		VertexFormat(corner, color),	// 1
		VertexFormat(corner + glm::vec3(length, 0 , 0), color), // 2
		VertexFormat(corner + glm::vec3(2 * length, lengthy , 0), color), //3
		VertexFormat(corner + glm::vec3(2.2 * length , 2 * lengthy , 0), color),
		VertexFormat(corner + glm::vec3(2 * length , 3 * lengthy , 0), color),
		VertexFormat(corner + glm::vec3(length , 4 * lengthy , 0), color),
		VertexFormat(corner + glm::vec3(0 , 4 * lengthy , 0), color),
		VertexFormat(corner - glm::vec3(1 * length , (-3)*lengthy , 0), color),
		VertexFormat(corner - glm::vec3(1.2 * length , (-2) * lengthy , 0), color),
		VertexFormat(corner - glm::vec3(1 * length , (-1) * lengthy , 0), color),

	};

	Mesh* asteroid = new Mesh(name);
	std::vector<unsigned short> indices = {
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,
		0, 4, 5,
		0, 5, 6,
		0, 6, 7,
		0, 7, 8,
		0, 8, 9,
		0, 9, 10,
		0, 10, 1 };


	if (!fill) {
		asteroid->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		////indices.push_back(0);
		//indices.push_back(2);
	}

	asteroid->InitFromData(vertices, indices);
	return asteroid;
}

Mesh* Object2D::CreatePlatforma(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length*4, 0, 0), color),
		VertexFormat(corner + glm::vec3(length*4, length / 3, 0), color),
		VertexFormat(corner + glm::vec3(0, length / 3, 0), color),



	};

	Mesh* platforma = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2,
		0, 2, 3 };

	if (!fill) {
		platforma->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		////indices.push_back(0);
		//indices.push_back(2);
	}

	platforma->InitFromData(vertices, indices);
	return platforma;
}
