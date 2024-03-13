#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <Shader.h>
#include <Camera.h>
#include <model.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <backend/imgui_impl_glfw.h>
#include <backend/imgui_impl_opengl3.h>

#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void RenderModel(Shader& ourShader, Model& ourModel, float positionx, float positiony, float positionz,float offset,  int VAO, Shader& lightCubeShader);
void RenderImGui();

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;


bool mouseMove = false;

float positionx=0.064f,positiony=-0.129,positionz=0.032f;
float objectOffset=4.0f;

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
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
	stbi_set_flip_vertically_on_load(true);


	glEnable(GL_DEPTH_TEST);


	float vertices[] = {
		// 后面四个顶点
	  -0.5f, -0.5f, -0.5f, // 左下后
	  0.5f, -0.5f, -0.5f, // 右下后
	  0.5f, 0.5f, -0.5f, // 右上后
	  -0.5f, 0.5f, -0.5f, // 左上后
	  // 前面四个顶点
	  -0.5f, -0.5f, 0.5f, // 左下前
	  0.5f, -0.5f, 0.5f, // 右下前
	  0.5f, 0.5f, 0.5f, // 右上前
	  -0.5f, 0.5f, 0.5f // 左上前
	};

	unsigned int indices[] = {
		0, 1, 1, 2, 2, 3, 3, 0,   // 前面四条线
		4, 5, 5, 6, 6, 7, 7, 4,   // 后面四条线
		0, 4, 1, 5, 2, 6, 3, 7    // 连接前后面的八条线
	};

	// build and compile shaders
	// -------------------------
	Shader ourShader("Shader/modelLoading.vs", "Shader/modelLoading.fs");
	Shader lightCubeShader("Shader/light_cube.vs", "Shader/light_cube.fs");

	Model ourModel("E:/Code/VS/asset/Rock1/Rock1.obj");

	

	unsigned int VAO, VBO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 绑定索引缓冲对象，并将索引数据复制到缓冲中
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 解绑 VBO 和 VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;



	ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\msyh.ttc", 18.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());

	IM_ASSERT(font != nullptr);

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		
		RenderImGui();
		RenderModel(ourShader, ourModel, positionx,positiony,positionz,objectOffset,VAO,lightCubeShader);
		RenderModel(ourShader, ourModel, positionx, positiony, positionz,0.0f,VAO,lightCubeShader);


		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}

void RenderModel(Shader& ourShader, Model& ourModel, float positionx,float positiony,float positionz,float offset,int VAO,Shader& lightCubeShader)
{
	ourShader.use();

	//light
	ourShader.setVec3("light.position", camera.Position);
	ourShader.setVec3("light.direction", camera.Front);
	ourShader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
	ourShader.setVec3("viewPos", camera.Position);

	ourShader.setVec3("light.ambient", 0.5f, 0.5f, 0.5f);
	ourShader.setVec3("light.diffuse", 0.8f, 0.8f, 0.8f);
	ourShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
	ourShader.setFloat("light.constant", 1.0f);
	ourShader.setFloat("light.linear", 0.09f);
	ourShader.setFloat("light.quadratic", 0.032f);



	// view/projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = camera.GetViewMatrix();
	ourShader.setMat4("projection", projection);
	ourShader.setMat4("view", view);

	// render the loaded model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, offset)); 
	//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	
	ourShader.setMat4("model", model);
	ourModel.Draw(ourShader);

	lightCubeShader.use();
	model = glm::scale(model, glm::vec3(ourModel.max - ourModel.min));
	model = glm::translate(model, glm::vec3(ourModel.max + ourModel.min) / 2.0f);
	model = glm::translate(model, glm::vec3(positionx,positiony,positionz));
	lightCubeShader.setMat4("model", model);
	lightCubeShader.setMat4("view", view);
	lightCubeShader.setMat4("projection", projection);

	// 绘制立方体线条
	glBindVertexArray(VAO);
	glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);


}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{

	glViewport(0, 0, width, height);
}


void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	if (mouseMove)
		camera.ProcessMouseMovement(xoffset, yoffset);
}
void RenderImGui()
{
	{


		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());


		ImGui::Begin("First Nav");


		ImGui::Checkbox(u8"移动鼠标", &mouseMove);
		ImGui::SliderFloat(u8"x轴", &positionx, -1, 1);
		ImGui::SliderFloat(u8"y轴", &positiony, -1, 1);
		ImGui::SliderFloat(u8"z轴", &positionz, -1, 1);
		ImGui::SliderFloat(u8"物体偏移", &objectOffset, 0, 20);
		//ImGui::SliderInt("hightlighttime", &updateHightLight, 0, 50000);


		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		mouseMove = false;
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
		mouseMove = true;

}



