#ifndef  __DATA_H__
#define  __DATA_H__

#include <glm/glm.hpp>

GLfloat cube_vertices[] = 
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


const float plane[] =
{
    // positions          // texture Coords 
 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
 5.0f, -0.5f, -5.0f,  2.0f, 2.0f
};


#define LIGHTHEIGHT		100

glm::vec3 ambient = glm::vec3(0.2f, 0.2f, 0.2f);
glm::vec3 lightColor1 = glm::vec3(0.4f, 0.5f, 0.3f);
glm::vec3 lightColor2 = glm::vec3(0.3f, 0.4f, 0.5f);
glm::vec3 lightColor3 = glm::vec3(0.5f, 0.3f, 0.4f);
glm::vec3 lightColor4 = glm::vec3(0.4f, 0.4f, 0.4f);
glm::vec3 lightPos1 = glm::vec3(0, LIGHTHEIGHT, 0);
glm::vec3 lightPos2 = glm::vec3(WINDOW_WIDTH, LIGHTHEIGHT, 0);
glm::vec3 lightPos3 = glm::vec3(0, LIGHTHEIGHT, WINDOW_HEIGHT);
glm::vec3 lightPos4 = glm::vec3(WINDOW_WIDTH, LIGHTHEIGHT, WINDOW_HEIGHT);


float curTime = 0.0f;
float lastTime = 0.0f;

#endif 



