
#ifndef __M_FUN_H__
#define __M_FUN_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <random>

#include <vector>

#include "../_morisa.h"
#include "./m_pd.h"

MORISA_NAMESPACE_BEGIN

// scale -> rotate -> translate is the actual sequence.
// 3D_Point * Model * View * Projection
// Model = Scale * Rotate * Translate
// in OpenGl, matrix  is left multiplication.
// Projection * View * Model * 3D_Point
// Translate * Rotate * Scale = Model
 

std::vector<glm::mat4> generater_grass_models()
{
	const size_t grass_num = 4;
	srand(time(NULL));
	std::vector<glm::mat4> models(MAZE_SIZE * MAZE_SIZE * 4);
	for (size_t i = 0; i < MAZE_SIZE; ++i)
	{
		for (size_t j = 0; j < MAZE_SIZE; ++j)
		{
			for (size_t k = 0; k < 4; ++k)
			{
				glm::mat4 model(1.0f);
				float rotatation = glm::radians(180.0f * rand() / RAND_MAX);
				float scaling = (float)rand() / RAND_MAX;
				model = glm::translate(model, glm::vec3(i, -0.10f - 0.40f*(1 - scaling), j));
				model = glm::rotate(model, rotatation, glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::scale(model, glm::vec3(scaling, scaling, scaling));
				models[(i * MAZE_SIZE + j) * grass_num + k] = model;
			}
		}
	}
	return models;
}


std::vector<glm::mat4> generater_roof_models()
{
	std::vector<glm::mat4> models(MAZE_SIZE * MAZE_SIZE);
	for (size_t i = 0; i < MAZE_SIZE; ++i)
	{
		for (size_t j = 0; j < MAZE_SIZE; ++j)
		{
			glm::mat4 model(1.0f);
			model = glm::translate(model, glm::vec3(i, 0.5f, j));
			models[i * MAZE_SIZE + j] = model;
		}
	}
	return models;
}

std::vector<glm::mat4> generater_floor_models()
{
	std::vector<glm::mat4> models(MAZE_SIZE * MAZE_SIZE);
	for (size_t i = 0; i < MAZE_SIZE; ++i)
	{
		for (size_t j = 0; j < MAZE_SIZE; ++j)
		{
			glm::mat4 model(1.0f);
			model = glm::translate(model, glm::vec3(i, -0.55, j));
			model = glm::scale(model, glm::vec3(1.0f, 0.1, 1.0f));
			models[i * MAZE_SIZE + j] = model;
		}
	}
	return models;
}

std::vector<glm::mat4> generater_wall_models(std::vector<m_type>& wall)
{
	glm::vec3 forward = glm::vec3(0, 0, 0.5f);
	glm::vec3 right = glm::vec3(0.5f, 0, 0);
	auto trans = [&](m_position _pos) ->glm::vec3
	{
		return glm::vec3(float(_pos.x), 0, float(_pos.y));
	};
	float scaleRatio = 0.5f;
	std::vector<glm::mat4> models(wall.size());
	size_t idx = 0;
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
		models[idx++] = model;
	}
	return models;
}

MORISA_NAMESPACE_END

#endif 



