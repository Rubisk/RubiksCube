#include <iostream>
#include <queue>

#include "Renderer.h"
#include "Shader.h"
#include "InputHandler.h"
#include "CubeOrientation.h"

#include "GL/glew.h"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

const std::time_t animationTime = 400;

glm::mat4 OrientationToMatrix__(CubeOrientation orientation) {
	glm::mat4 matrix;
	std::queue<Rotation> rotations = orientation.GetRotations();
	while (!rotations.empty()) {
		Rotation r = rotations.front();
		glm::vec3 axis = glm::vec3(0, 0, 0);
		if (r.axis == X) axis[0] = 1;
		if (r.axis == Y) axis[1] = 1;
		if (r.axis == Z) axis[2] = 1;
		axis = glm::vec3(matrix * glm::vec4(axis, 0));
		matrix = glm::rotate(matrix, glm::radians(r.angle), axis);
		rotations.pop();
	}
	return matrix;
}

const GLfloat cubeVertices[] = {
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f,  0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f,  0.5f,

	-0.51f, -0.45f, -0.45f,
	-0.51f, -0.45f,  0.45f,
	-0.51f,  0.45f, -0.45f,
	-0.51f,  0.45f,  0.45f,

	 0.51f, -0.45f, -0.45f,
	 0.51f, -0.45f,  0.45f,
	 0.51f,  0.45f, -0.45f,
	 0.51f,  0.45f,  0.45f,

	-0.45f, -0.51f, -0.45f,
	-0.45f, -0.51f,  0.45f,
	 0.45f, -0.51f, -0.45f,
	 0.45f, -0.51f,  0.45f,

	-0.45f,  0.51f, -0.45f,
	-0.45f,  0.51f,  0.45f,
	 0.45f,  0.51f, -0.45f,
	 0.45f,  0.51f,  0.45f,

	-0.45f, -0.45f, -0.51f,
	-0.45f,  0.45f, -0.51f,
	 0.45f, -0.45f, -0.51f,
	 0.45f,  0.45f, -0.51f,

	-0.45f, -0.45f,  0.51f,
    -0.45f,  0.45f,  0.51f,
	 0.45f, -0.45f,  0.51f,
	 0.45f,  0.45f,  0.51f,
};

const GLuint cubeIndices[] = {
	// Outer Cube
	0, 1, 3,
	0, 2, 3,
	0, 1, 5,
	0, 4, 5,
	0, 2, 6,
	0, 4, 6,
	7, 1, 3,
	7, 1, 5,
	7, 2, 3,
	7, 2, 6,
	7, 4, 5,
	7, 4, 6,

	// Face 1
	8, 9, 11,
	8, 10, 11,

	// Face 2
	12, 13, 15,
	12, 14, 15,

	// Face 3
	16, 17, 19,
	16, 18, 19,

	// Face 4
	20, 21, 23,
	20, 22, 23,

	// Face 5
	24, 25, 27,
	24, 26, 27,

	// Face 6
	28, 29, 31,
	28, 30, 31,
};

const GLfloat colorVertices[] = {
	// BLACK INNER CUBE
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,

	// Red
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	// Orange
	1.0f, 0.5f, 0.0f,
	1.0f, 0.5f, 0.0f,
	1.0f, 0.5f, 0.0f,
	1.0f, 0.5f, 0.0f,

	// White
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,

	// Yellow
	1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,

	// Blue
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,

	// Green
	0.0f, 0.7f, 0.0f,
	0.0f, 0.7f, 0.0f,
	0.0f, 0.7f, 0.0f,
	0.0f, 0.7f, 0.0f,
};

Renderer::Renderer(std::weak_ptr<Cube> cube, std::weak_ptr<Camera> camera) {
	cube_ = cube;
	camera_ = camera;

	// Setup GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);


	shaderProgram = CreateShaderProgram("shaders/shader.vs", "shaders/shader.frag");
	LoadCubeVertices();
}

void Renderer::LoadCubeVertices() {
	glGenVertexArrays(1, &vertexArray);
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &elementBuffer);
	glGenBuffers(1, &colorBuffer);

	glBindVertexArray(vertexArray);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorVertices), colorVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);

	glBindVertexArray(0);
}

void Renderer::Draw() {
	if (camera_.expired() || cube_.expired()) return;
	std::shared_ptr<Camera> camera = camera_.lock();
	std::shared_ptr<Cube> cube = cube_.lock();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.8f, 0.8f, 0.8f, 1);

	glUseProgram(shaderProgram);
	glBindVertexArray(vertexArray);

	GLuint modelUni = glGetUniformLocation(shaderProgram, "model");
	GLuint cameraUni = glGetUniformLocation(shaderProgram, "camera");
	GLuint projectionUni = glGetUniformLocation(shaderProgram, "projection");
	GLuint sideNotToRenderUni = glGetUniformLocation(shaderProgram, "sideNotToRender");

	glm::mat4 cameraMatrix = camera->GetCameraMatrix();
	glUniformMatrix4fv(cameraUni, 1, GL_FALSE, glm::value_ptr(cameraMatrix));

	glm::mat4 projection = glm::perspective(glm::radians(55.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	glUniformMatrix4fv(projectionUni, 1, GL_FALSE, glm::value_ptr(projection));

	const float size = 0.150f;

	for (int ix = 0; ix < 3; ix++) {
		for (int iy = 0; iy < 3; iy++) {
			for (int iz = 0; iz < 3; iz++) {
				glm::mat4 model;
				model = OrientationToMatrix__(cube->blocks[ix][iy][iz]) * model;
				model = glm::translate(model, glm::vec3(glm::inverse(model) * glm::vec4(size * (ix - 1), size * (iy - 1), size * (iz - 1), 1)));
				model = _GetAnimateBlockMatrix(ix, iy, iz) * model;
				model = glm::scale(model, glm::vec3(size, size, size));

				glUniformMatrix4fv(modelUni, 1, GL_FALSE, glm::value_ptr(model));
				glm::vec3 sideNotToRender = SideNotToRender_(ix, iy, iz, cube);
				glUniform3fv(sideNotToRenderUni, 1, glm::value_ptr(sideNotToRender));

				glDrawElements(GL_TRIANGLES, sizeof(cubeIndices), GL_UNSIGNED_INT, 0);
			}
		}
	}
	if (shouldStopAnimating_) isAnimating_ = false;
	glBindVertexArray(0);
};

bool Renderer::IsAnimating() {
	return isAnimating_;
}

void Renderer::StartTurnAnimation(Axis axis, int side, int direction) {
	animationAxis = axis;
	animationSide = side;
	animationDirection = direction;
	animationStartTime = std::clock();
	isAnimating_ = true;
}

glm::mat4 Renderer::_GetAnimateBlockMatrix(int x, int y, int z) {
	glm::mat4 animateMatrix;

	std::time_t currentTime = (std::clock() > animationStartTime + animationTime) ? animationStartTime + animationTime : std::clock();

	float distance = ((float) currentTime - animationStartTime) / animationTime * glm::pi<float>() / 2;

	if (IsAnimating()) {
		switch (animationAxis) {
		case X:
			if (x == animationSide + 1)
				animateMatrix = glm::rotate(animationDirection * distance, glm::vec3(1, 0, 0));
			break;
		case Y:
			if (y == animationSide + 1)
				animateMatrix = glm::rotate(animationDirection * distance, glm::vec3(0, 1, 0));
			break;
		case Z:
			if (z == animationSide + 1)
				animateMatrix = glm::rotate(animationDirection * distance, glm::vec3(0, 0, 1));
			break;
		}
	}

	shouldStopAnimating_ = (currentTime == animationStartTime + animationTime);
	return animateMatrix;
}

glm::vec3 Renderer::SideNotToRender_(int x, int y, int z, std::shared_ptr<Cube> cube) {
	glm::vec3 side = glm::vec3(0, 0, 0);
	if (IsAnimating()) {
		switch (animationAxis) {
		case X:
			if (x == animationSide + 1) side = glm::vec3(-animationSide * 0.51f, 0, 0);
			if (x == 1) side = glm::vec3(animationSide * 0.51f, 0, 0);
			break;
		case Y:
			if (y == animationSide + 1) side = glm::vec3(0, -animationSide * 0.51f, 0);
			if (y == 1) side = glm::vec3(0, animationSide * 0.51f, 0);
			break;
		case Z:
			if (z == animationSide + 1) side = glm::vec3(0, 0, -animationSide * 0.51f);
			if (z == 1) side = glm::vec3(0, 0, animationSide * 0.51f);
			break;
		}
		glm::mat4 rotation = glm::inverse(OrientationToMatrix__(cube->blocks[x][y][z]));
		side = glm::vec3(rotation * glm::vec4(side, 0.0f));
		// std::cout << side.x << " " << side.y << " " << side.z << std::endl;
	}
	return side;
}

Renderer::~Renderer() {
	glDeleteVertexArrays(1, &vertexArray);
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &elementBuffer);
	glDeleteBuffers(1, &colorBuffer);
}
