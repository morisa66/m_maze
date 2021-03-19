#ifndef  __M_SHAPE_H__
#define  __M_SHAPE_H__

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

#include "../_morisa.h"
#include "../utils/m_define.h"
#include "m_base.h"


MORISA_NAMESPACE_BEGIN


constexpr const static float cube[] =
{
	// position          // normal             //texture Coord    
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,   0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,   1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,   1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,   0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,   1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,   0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,   0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,   0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,   1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,   0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,   0.0f, 1.0f
};

constexpr const static float quad[] =
{
	// positions           // normal                // texture Coords 
	0.0f,  0.5f,  0.0f,    0.0f,  0.0f,  1.0f,      0.0f,  1.0f,
	0.0f, -0.5f,  0.0f,    0.0f,  0.0f,  1.0f,      0.0f,  0.0f,
	1.0f, -0.5f,  0.0f,    0.0f,  0.0f,  1.0f,      1.0f,  0.0f,

	0.0f,  0.5f,  0.0f,    0.0f,  0.0f,  1.0f,      0.0f,  1.0f,
	1.0f, -0.5f,  0.0f,    0.0f,  0.0f,  1.0f,      1.0f,  0.0f,
	1.0f,  0.5f,  0.0f,    0.0f,  0.0f,  1.0f,      1.0f,  1.0f
};


constexpr const static float plane[] =
{
	// positions           // normal              // texture Coords 
   	-0.5f,  0.0f, -0.5f,    0.0f,  1.0f,	 0.0f,    0.0f,  1.0f,
   	-0.5f,  0.0f,  0.5f,    0.0f,  1.0f,	 0.0f,    0.0f,  0.0f,
	0.5f,  0.0f,  0.5f,    	0.0f,  1.0f,	 0.0f,    1.0f,  0.0f,

   	-0.5f,  0.0f, -0.5f,    0.0f,  1.0f,	 0.0f,    0.0f,  1.0f,
	0.5f,  0.0f,  0.5f,    	0.0f,  1.0f,	 0.0f,    1.0f,  0.0f,
    	0.5f,  0.0f, -0.5f,    	0.0f,  1.0f,  	 0.0f,    1.0f,  1.0f
};

class m_shape : protected m_base
{
public:
	// 0 : positions
	// 1 : normals
	// 2 : texCoords
	m_shape(const unsigned ID, shape_choice shape, vertex_attribute v_a, unsigned draw_type = GL_STATIC_DRAW)
	{
		_ID = ID;
		init(draw_type, shape, v_a);
	}
	
	// 3 4 5 6 : matrix4 * 4
	void instance(std::vector<glm::mat4>& models)
	{
		is_instance = true;
		glBindVertexArray(VAO);
		glGenBuffers(1, &instanceVBO);
		glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * models.size(), models.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(sizeof(glm::vec4)));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(2 * sizeof(glm::vec4)));
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(3 * sizeof(glm::vec4)));
		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void bind(bool is_bind = true) { glBindVertexArray(is_bind ? VAO : 0); }

private:
	void init(unsigned draw_type, shape_choice shape, vertex_attribute v_a)
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		switch (shape)
		{
		case SHAPE_CUBE:
			glBufferData(GL_ARRAY_BUFFER, sizeof(cube), &cube, draw_type);
			break;
		case SHAPE_QUAD:
			glBufferData(GL_ARRAY_BUFFER, sizeof(quad), &quad, draw_type);
			break;
		case SHAPE_PLANE:
			glBufferData(GL_ARRAY_BUFFER, sizeof(plane), &plane, draw_type);
			break;
		}
		if (v_a & VA_POSITION)
		{
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		}
		if (v_a & VA_NORMAL)
		{
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		}
		if (v_a & VA_TEXCOORD)
		{
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}


};

MORISA_NAMESPACE_END

#endif
