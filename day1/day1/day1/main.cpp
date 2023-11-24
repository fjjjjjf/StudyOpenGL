
#define GLEW_STATIC 
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include <iostream>
//ע��������glad������glfw


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwWindowShouldClose(window);//�жϵ��esc �رմ���
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//���ð��Ϊ 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//˵��ʹ�ú���ģʽ

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to Create glfw window " << std::endl;
		glfwTerminate();
		return -1;

	}
	glfwMakeContextCurrent(window);//�ܹ�ʹ���߳�

	//��������opengl����ָ��
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		
	}
	glViewport(0, 0, 800, 600); //��Ⱦ���ڴ�С
	//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	while (!glfwWindowShouldClose(window))
	{
		//Input
		processInput(window);

		//Render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//��ɫ����  ��R,G,B,A��
		glClear(GL_COLOR_BUFFER_BIT);//�����Ļ��ɫ����

		//Event
		glfwSwapBuffers(window);//�ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩��������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ��
		glfwPollEvents();//�����û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬�������ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã���
	}

	glfwTerminate();//�����ͷ���Դ
	return 0;
}

