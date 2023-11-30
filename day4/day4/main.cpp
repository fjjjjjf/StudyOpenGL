#include <iostream>
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include "Shader/Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float mix = 0.2f;

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
    Shader ourShader("Shader/shader.vs", "Shader/shader.fs");
    float vertices[] = {
        //     ---- λ�� ----       ---- ��ɫ ----     - �������� -
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
           -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
           -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
    };
    unsigned int indices[] = {
       0, 1, 3, // first triangle
       1, 2, 3  // second triangle
    };
  
    //�������ֵ��������ɫ�����ٴ���Ƭ����ɫ��
    //������������ã����������������ᣬs,t,3d���и�r
 //   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);	//�������Ĭ����Ϊ���ظ�����ͼ��
 //   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);GL_CLAMP_TO_BORDER	����������Ϊ�û�ָ���ı�Ե��ɫ��
    //�������������ģ�Ͷ������õ��Ǹ����飬OpenGL����������������������ȥ��������ͼ���ϵ����أ�Ȼ����в�����ȡ�������ص���ɫ��

 //�༶��Զ���� ԽԶ��ֵ����1/2�Ĳ������� glGenerateMipmaps

    unsigned int texture1,texture2;
   
  
    glGenTextures(1, &texture1);
    glActiveTexture(GL_TEXTURE0); // �ڰ�����֮ǰ�ȼ�������Ԫ��Ĭ�ϼ���texture0�� opengl�ܱ�֤16�������ܼ��� ����8��GL_TEXTURE0 + 8
    glBindTexture(GL_TEXTURE_2D, texture1);

    //��һ������ָ������Ŀ�꣬�������뵱ǰ�����������ͳһĿ������ ���ڶ�����ʾ�༶��Զ�����𣬵��������������ʽ�����ߵڰ˸�����������Դͼ�ĸ�ʽ���������͡�����ʹ��RGBֵ�������ͼ�񣬲������Ǵ���Ϊchar(byte)���飬���ǽ��ᴫ���Ӧֵ��
   // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);//�����ͼ������
   // glGenerateMipmap(GL_TEXTURE_2D);  ���ɶ�mipmap

    // Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
  //  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    
  //  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//���÷�Χ
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//���Բ�ֵ
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
   
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    //��תͼƬ
  
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
   
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    //EBOԪ�ػ������
    unsigned int VBO, VAO,EBO;
    glGenVertexArrays(1, &VAO);//����VAO����ID
    //����Ҫʹ�� VAOʱ����glBindVertexArray�󶨣�֮����������ӦVBO������ָ�룬֮����VAO��֮��ʹ��
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    glGenBuffers(1, &EBO);
  

    //���ƶ������鵽��������openglʹ��
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

     //����Ǹ�6��float
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //��ʼλ���ǵ�����
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //���ö��ⶥ������
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    ourShader.use();// don't forget to activate/use the shader before setting uniforms!
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0); // �ֶ�����
    ourShader.setInt("texture2", 1); // ����ʹ����ɫ��������

    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

       

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);//������
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);//������
          // draw our first triangleda's

        ourShader.setFloat("mix", mix);
        ourShader.use();

        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

      //  glDrawArrays(GL_TRIANGLES, 0, 4);

        glBindVertexArray(0); // no need to unbind it every time 

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
 


    glfwTerminate();
    return 0;
}







// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && mix < 1)
    {
        mix += 0.001f;
        if (mix >= 1.0f)
            mix = 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && mix > 0)
    {
        mix -= 0.001f;
        if (mix <= 0.0f)
            mix = 0.0f;
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}



