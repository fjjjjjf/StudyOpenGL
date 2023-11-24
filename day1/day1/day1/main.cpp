
#define GLEW_STATIC 
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include <iostream>
//注意先引入glad再引入glfw


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwWindowShouldClose(window);//判断点击esc 关闭窗口
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//设置版号为 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//说明使用核心模式

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to Create glfw window " << std::endl;
		glfwTerminate();
		return -1;

	}
	glfwMakeContextCurrent(window);//能够使用线程

	//用来调用opengl函数指针
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		
	}
	glViewport(0, 0, 800, 600); //渲染窗口大小
	//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	while (!glfwWindowShouldClose(window))
	{
		//Input
		processInput(window);

		//Render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//颜色缓冲  （R,G,B,A）
		glClear(GL_COLOR_BUFFER_BIT);//清空屏幕颜色缓冲

		//Event
		glfwSwapBuffers(window);//会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上
		glfwPollEvents();//检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）。
	}

	glfwTerminate();//结束释放资源
	return 0;
}

