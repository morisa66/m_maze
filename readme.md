

# 简绍

> 一个简单的 OpenGL 迷宫小程序。

# 参考

> - [wiki](https://en.wikipedia.org/wiki/Maze_generation_algorithm)
> - [opengl](https://learnopengl.com/)

# 开发软件

> VS 2019 Community

# 工具包

> - glfw64
> - glad
> - glm
> - stb_image

# 如何配置运行

> 参考[这里](https://morisa66.github.io/2021/01/22/OpenGL1/)。

# 一些参数

> 参考 `m_configture.h`
>
> ~~~cpp
> #define WINDOW_WIDTH	1920
> #define WINDOW_HEIGHT	1080
> #define MAZE_SIZE		30
> #define SPEED 3.0f
> #define MOUSE_SENSITIVITY 0.007f
> 
> #define WALL_TEXTURE "asset/marble.jpg"
> #define FLOOR_TEXTURE "asset/wood.png"
> #define ROOF_TEXTURE "asset/window.png"
> #define GRASS_TEXTURE "asset/grass.png"
> 
> const char* skybox_paths[] =
> {
>     "asset/skybox/right.jpg",
>     "asset/skybox/left.jpg",
>     "asset/skybox/top.jpg",
>     "asset/skybox/bottom.jpg",
>     "asset/skybox/front.jpg",
>     "asset/skybox/back.jpg"
> };
> 
> #endif
> ~~~

# 操作方式

> - W/S/A/D：前\后\左\右
> - Left_Control/Space：上\下
> - Z/X：开启/关闭碰撞检测
>   - 开启后高度会限制
>   - 存在个别情况下的穿模
>   - 如果卡在墙里面，建议关闭碰撞检测，走出来后再开启
> - 鼠标移动控制视角方向
> - 鼠标滚轮控制视野