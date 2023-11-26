#include <iostream>
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include "Shader.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout(location = 1) in vec3 aColor;\n" // 颜色变量的属性位置值为 1
"out vec4 vertexColor; \n" // 新增颜色属性
//"uniform vec4 triangleColor; \n"// 新增颜色 uniform
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"    vertexColor =  vec4(aColor, 1.0f);\n" // 将颜色传递给片段着色器
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"in vec4 vertexColor;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vertexColor;\n"
"}\n\0";

//GLSL 向量 vecn 包含n个gloat分量的默认向量 bvecn n个bool分量的向量
	
	//打算从一个着色器向另一个着色器发送数据 ，要对发送方进行输出声明 ，接收方输入声明，名字相同才可以发送数据

	//uniform 是一种从cpu中的应用向gpu着色器发送数据的方式。uniform是全局的，会保存数据直到重置或修改
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
int main()
{
	
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    Shader ourShader("./shader.vs", "./shader.fs");
    float vertices[] = {
        // 位置              // 颜色
	0.0f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
   -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
	0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
    };

    unsigned int indices[] = {
        0,1,2,//第一个三角形
        1,2,3//第二个三角形
    };


    //EBO元素缓冲对象
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);//生成VAO，给ID
    //当想要使用 VAO时，用glBindVertexArray绑定，之后考研设置响应VBO和属性指针，之后解绑VAO供之后使用
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glGenBuffers(1, &EBO);

    //复制顶点数组到缓冲区供opengl使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

   // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

   // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //跨度是隔6个float
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //起始位置是第三个
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangleda's
        ourShader.use();
        
       
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
      
        
        float timeValue = glfwGetTime();
        
        ////定位到该color
        ourShader.setFloat("xOffset", sin(timeValue) * 0.5f);
        ourShader.setFloat("yOffset", cos(timeValue) * 0.5f);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0); // no need to unbind it every time 

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);


    glfwTerminate();
	return 0;
}







// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}