#pragma comment(linker, "/subsystem:windows /entry:mainCRTStartup")

#include "common/m_window.h"
#include "common/m_shader.h"
#include "common/m_camera.h"
#include "common/m_shape.h"
#include "utils/m_img.h"
#include "utils/m_fun.h"
#include "app/m_maze.h"
#include "m_configture.h"

using namespace morisa;

m_window window(3, 3, WINDOW_WIDTH, WINDOW_HEIGHT, "moirsa");
m_camera camera;

int main()
{
	m_shader wall_shader("shader/wall.vert", "shader/wall.frag");
	m_shader skybox_shader("shader/skybox.vert", "shader/skybox.frag");
	m_shader floor_shader("shader/floor.vert", "shader/floor.frag");
	m_shader roof_shader("shader/roof.vert", "shader/roof.frag");
	m_shader grass_shader("shader/grass.vert", "shader/grass.frag");

	m_maze maze{ MAZE_SIZE };
	auto wall{ maze.get_wall() };
	auto wall_models{ generater_wall_models(wall) };
	auto floor_models{ generater_floor_models() };
	auto roof_models{ generater_roof_models() };
	auto grass_models{ generater_grass_models() };

	unsigned textureWall = m_load_img2D(WALL_TEXTURE);
	unsigned texturefloor = m_load_img2D(FLOOR_TEXTURE);
	unsigned skyboxCubemap = m_load_img3D(skybox_paths);
	unsigned textureRoof = m_load_img2D(ROOF_TEXTURE);
	unsigned textureGrass = m_load_img2D(GRASS_TEXTURE);

	m_shape wall_obj{ 0x0001 , SHAPE_CUBE, VA_POSITION | VA_NORMAL | VA_TEXCOORD };
	m_shape floor_obj{ 0x0002, SHAPE_PLANE, VA_POSITION_NORMAL_TEXCOORD };
	m_shape skybox_obj{ 0x0003, SHAPE_CUBE, VA_POSITION };
	m_shape roof_obj{ 0x0004, SHAPE_PLANE, VA_POSITION_NORMAL_TEXCOORD };
	m_shape grass_obj{ 0x0005, SHAPE_QUAD, VA_POSITION_NORMAL_TEXCOORD };

	float cur_frame_time = 0.0f;
	float last_frame_time = 0.0f;

    window.disableCursor();

    window.bindMouseCallBack([](GLFWwindow* _window, double posX, double posY)
    { camera.mouseCallBack(_window, (float)posX, (float)posY); });

    window.bindScrollCallBack([](GLFWwindow* _window, double offsetX, double offsetY)
	{ camera.scrollCallBack(_window, (float)offsetX, (float)offsetY); });

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	wall_obj.instance(wall_models);
	floor_obj.instance(floor_models);
	roof_obj.instance(roof_models);
	grass_obj.instance(grass_models);

	unsigned UBO;
	glGenBuffers(1, &UBO);
	glBindBuffer(GL_UNIFORM_BUFFER, UBO);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, UBO, 0, 2 * sizeof(glm::mat4));
	wall_shader.seUniformBlockBinding("MAT", 0);
	floor_shader.seUniformBlockBinding("MAT", 0);
	roof_shader.seUniformBlockBinding("MAT", 0);
	grass_shader.seUniformBlockBinding("MAT", 0);

	wall_shader.active();
	wall_shader.setInt("texture1", 0);
	floor_shader.active();
	floor_shader.setInt("texture1", 0);
	roof_shader.active();
	roof_shader.setInt("texture1", 0);
	grass_shader.active();
	grass_shader.setInt("texture1", 0);

	while (!glfwWindowShouldClose(*window))
	{
		cur_frame_time = (float)glfwGetTime();
		camera.keyEvent(*window, cur_frame_time - last_frame_time , wall);
		last_frame_time = cur_frame_time;

		glm::mat4 projection = glm::perspective(glm::radians(camera.getFov()), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);
		glBindBuffer(GL_UNIFORM_BUFFER, UBO);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		glm::mat4 view = camera.getViewMat();
		glBindBuffer(GL_UNIFORM_BUFFER, UBO);
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		wall_shader.active();
		wall_obj.bind();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureWall);
		glDrawArraysInstanced(GL_TRIANGLES, 0, 36, (GLsizei)wall_models.size());
		wall_obj.bind(false);

		floor_shader.active();
		floor_obj.bind();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texturefloor);
		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, (GLsizei)floor_models.size());
		floor_obj.bind(false);

		grass_shader.active();
		grass_obj.bind();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureGrass);
		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, (GLsizei)grass_models.size());
		grass_obj.bind(false);

		glDepthFunc(GL_LEQUAL);
		skybox_shader.active();
		skybox_shader.setMat4("view", glm::mat4(glm::mat3(camera.getViewMat())));
		skybox_shader.setMat4("projection", glm::perspective(glm::radians(camera.getFov()), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f));
		skybox_obj.bind();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxCubemap);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		skybox_obj.bind(false);
		glDepthFunc(GL_LESS);

		roof_shader.active();
		roof_obj.bind();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureRoof);
		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, (GLsizei)roof_models.size());
		roof_obj.bind(false);

		glfwSwapBuffers(*window);
		glfwPollEvents();
	}


    glfwTerminate();

    return 0;
}

