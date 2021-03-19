#ifndef __M_SHADER_H__
#define __M_SHADER_H__

#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "../_morisa.h"
#include "../utils/m_log.h"

MORISA_NAMESPACE_BEGIN


class m_shader
{
public:
    m_shader(const char* v_path, const char* f_path, const char* g_path = nullptr)
    {
        using std::string;
        using std::ifstream;
        using std::stringstream;
        ifstream v_f, f_f, g_f;
        stringstream v_ss, f_ss, g_ss;
        try
        {
            v_f.open(v_path);
            f_f.open(f_path);
            if (g_path)
            {
                g_f.open(g_path);
            }

            v_ss << v_f.rdbuf();
            f_ss << f_f.rdbuf();
            if (g_path)
            {
                g_ss << g_f.rdbuf();
            }

            v_f.close();
            f_f.close();
            if (g_path)
            {
                g_f.close();
            }
        }
        catch (std::ifstream::failure&)
        {
#ifdef USE_LOG
            m_log("FILE_NOT_SUCCESFULLY_READ.");
#endif 
        }
        string s1 = v_ss.str();
        string s2 = f_ss.str();
        const char* v_code = s1.c_str();
        const char* f_code = s2.c_str();

        unsigned vertex, geometry, fragment;

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &v_code, NULL);
        glCompileShader(vertex);
        check_and_get_error_info(vertex, v_path);

        if (g_path)
        {
            string s3 = g_ss.str();
            const char* g_code = s3.c_str();
            geometry = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geometry, 1, &g_code, NULL);
            glCompileShader(geometry);
            check_and_get_error_info(geometry, g_path);
        }

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &f_code, NULL);
        glCompileShader(fragment);
        check_and_get_error_info(fragment, f_path);

        _ID = glCreateProgram();
        glAttachShader(_ID, vertex);
        glAttachShader(_ID, fragment);
        if (g_path)
            glAttachShader(_ID, geometry);
        glLinkProgram(_ID);


        check_and_get_error_info(_ID, v_path,  false);

        glDeleteShader(vertex);
        glDeleteShader(fragment);
        if (g_path)
            glDeleteShader(geometry);
    }

    ~m_shader() { glDeleteProgram(_ID); }

    unsigned operator*() const noexcept { return _ID; }

    void active()
    {
        glUseProgram(_ID);
    }

    unsigned get() const noexcept { return _ID; }

    void setBool(const char* name, bool value) const
    {
        glUniform1i(glGetUniformLocation(_ID, name), (int)value);
    }

    void setInt(const char* name, int value) const
    {
        glUniform1i(glGetUniformLocation(_ID, name), value);
    }

    void setVec3(const char* name, glm::vec3 value) const
    {
        glUniform3f(glGetUniformLocation(_ID, name), value.x, value.y, value.z);
    }

    void setFloat(const char* name, float value) const
    {
        glUniform1f(glGetUniformLocation(_ID, name), value);
    }

    void setMat4(const char* name, glm::mat4 value) {
        glUniformMatrix4fv(glGetUniformLocation(_ID, name), 1, GL_FALSE, glm::value_ptr(value));
    }

    void seUniformBlockBinding(const char* name, unsigned bind_point)
    {
        glUniformBlockBinding(_ID, glGetUniformBlockIndex(_ID, name), bind_point);
    }

private:
    unsigned _ID;

    void check_and_get_error_info(unsigned shader,const char* path, bool is_compile = true)
    {
        int success;
        char info[1024];
        if (is_compile)
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
#ifdef USE_LOG
                glGetShaderInfoLog(shader, 1024, NULL, info);
                m_log(path, true, true);
                m_log(info, false, true);
#endif          
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
#ifdef USE_LOG
                glGetProgramInfoLog(shader, 1024, NULL, info);
                m_log(path, true, true);
                m_log(info, false, true);
#endif      
            }
        }
    }
};

MORISA_NAMESPACE_END

#endif
