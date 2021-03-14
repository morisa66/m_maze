#pragma comment(linker, "/subsystem:windows /entry:mainCRTStartup")

#include "common/m_window.h"
#include "common/m_shader.h"
#include "common/m_camera.h"
#include "utils/m_img.h"
#include "asset/data.h"
#include "app/m_maze.h"
#include "m_configture.h"


using namespace morisa;

m_window window(3, 3, WINDOW_WIDTH, WINDOW_HEIGHT, "moirsa");
m_camera camera;
m_shader shader("shader/v.vert", "shader/f.frag");
m_maze maze{ MAZE_SIZE };
auto wall{ maze.get_wall() };


int main()
{
    window.EnableZbuffer();
    window.disableCursor();
    window.bindMouseCallBack([](GLFWwindow* _window, double posX, double posY)
    { camera.mouseCallBack(_window, (float)posX, (float)posY); });

    window.bindScrollCallBack([](GLFWwindow* _window, double offsetX, double offsetY) 
	{ camera.scrollCallBack(_window, (float)offsetX, (float)offsetY); });

	unsigned cubeVAO, cubeVBO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), &cube_vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	glBindVertexArray(0);

	unsigned textureWall = m_load_img2D(WALL_TEXTURE);
	unsigned texturePlane = m_load_img2D(PLANE_TEXTURE);

	shader.active();
	shader.setInt("texture", 0);

	shader.setVec3("ambient", ambient);
	shader.setVec3("lightColor1", lightColor1);
	shader.setVec3("lightPos1", lightPos1);
	shader.setVec3("lightColor2", lightColor2);
	shader.setVec3("lightPos2", lightPos2);
	shader.setVec3("lightColor3", lightColor3);
	shader.setVec3("lightPos3", lightPos3);
	shader.setVec3("lightColor4", lightColor4);
	shader.setVec3("lightPos4", lightPos4);

	glm::vec3 forward = glm::vec3(0, 0, 0.5f);
	glm::vec3 right = glm::vec3(0.5f, 0, 0);
	auto trans = [&](m_position _pos) ->glm::vec3
	{
		return glm::vec3(GLfloat(_pos.x), 0, GLfloat(_pos.y));
	};
	float scaleRatio = 0.8f;

	while (!glfwWindowShouldClose(*window))
	{
		curTime = (float)glfwGetTime();
		camera.keyEvent(*window, curTime - lastTime, wall);
		lastTime = curTime;

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.active();
		glm::mat4 view = camera.getViewMat();
		shader.setMat4("view", view);
		glm::mat4 projection = glm::perspective(glm::radians(camera.getFov()), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);
		shader.setMat4("projection", projection);

		glBindVertexArray(cubeVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureWall);
		for (auto&& it : wall)
		{
			glm::mat4 model = glm::mat4(1.0f);
			switch (it.dir)
			{
			case m_direction::forward:
				model = glm::translate(model, trans(it.pos) + forward);
				model = glm::scale(model, glm::vec3(1, 1, scaleRatio * 0.5));
				break;
			case m_direction::backward:
				model = glm::translate(model, trans(it.pos) - forward);
				model = glm::scale(model, glm::vec3(1, 1, scaleRatio * 0.5));
				break;
			case m_direction::right:
				model = glm::translate(model, trans(it.pos) + right);
				model = glm::scale(model, glm::vec3(scaleRatio * 0.5, 1, 1));
				break;
			case m_direction::left:
				model = glm::translate(model, trans(it.pos) - right);
				model = glm::scale(model, glm::vec3(scaleRatio * 0.5, 1, 1));
				break;
			}
			shader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);	
		}
		glBindVertexArray(0);


		glBindVertexArray(cubeVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texturePlane);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(maze.size()/ 2.0f - 0.5f, -0.55, maze.size() / 2.0f - 0.5f));
		model = glm::scale(model, glm::vec3(maze.size() + 1.0f, 0.1, maze.size() + 1.0f));
		shader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);

		glfwSwapBuffers(*window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteBuffers(1, &cubeVBO);

    glfwTerminate();

    return 0;
}

