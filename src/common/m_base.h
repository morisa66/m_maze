#ifndef  __M_BASE_H__
#define  __M_BASE_H__

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

#include "../_morisa.h"
#include "../utils/m_define.h"
#include "../utils/m_log.h"

MORISA_NAMESPACE_BEGIN

class m_base
{
public:
	m_base() {}

	m_base(const unsigned ID):_ID(ID){}

	virtual ~m_base()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		if (is_instance)
		{
			glDeleteBuffers(1, &instanceVBO);
		}
#ifdef USE_LOG
		m_log("the _ID of the delete object is ", true, false);
		m_log(_ID, false, true);
#endif 
	}

	virtual void init(unsigned type, shape_choice shape, vertex_attribute v_a) = 0;

	virtual void instance(std::vector<glm::mat4>& models) = 0;

	virtual void bind(bool is_bind) = 0;

protected:
	unsigned VAO{ 0 };
	unsigned VBO{ 0 };
	// there is no use of EBO.
	unsigned EBO{ 0 };
	unsigned instanceVBO{ 0 };
	bool is_instance{ false };
	// for debug
	unsigned _ID{0};
};


MORISA_NAMESPACE_END
#endif