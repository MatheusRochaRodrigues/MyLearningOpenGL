#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void Wireframe(GLFWwindow* window);

const unsigned int WIDHT = 800;
const unsigned int HEIGHT = 600;

const char* vertexShaderSOURCE = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
	"layout (location = 1) in vec3 ourColor;\n"
	"out vec3 outColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
	"	outColor = ourColor;\n"
    "}\0";

const char* fragmentShaderSOURCE = "#version 330 core\n"
    "out vec4 FragColor;\n"
	"in vec3 outColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(outColor, 1.0);\n"
	"}\n\0";

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "MyLearning^^", NULL, NULL);

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

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSOURCE, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSOURCE, NULL);
	glCompileShader(fragmentShader);

	unsigned int shaderPROGRAM = glCreateProgram();
	glAttachShader(shaderPROGRAM, vertexShader);
	glAttachShader(shaderPROGRAM, fragmentShader);
	glLinkProgram(shaderPROGRAM);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
	};


	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	

	while (!glfwWindowShouldClose(window))
	{
		//INPUT
		processInput(window);
		Wireframe(window);

		//RENDER
		glClearColor(0.1f, 0.2f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//DRAW OUR PRIMITIVES
		glUseProgram(shaderPROGRAM);

		float timeRange = glfwGetTime();
		//std::cout << "seconds " << timeRange;
		float VaryColor = sin(timeRange) / 2.0f + 0.5f;
		//system("clear||cls");
		//system("clear"); (linux)
		//system("cls"); 
		//(windows);

		int outColorLocation = glGetUniformLocation(shaderPROGRAM, "outColor");
		glUniform4f(outColorLocation, 0.0f, VaryColor, 0.0f, 1.0f);

		//render triangule
		glBindVertexArray(VAO);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderPROGRAM);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{

	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{

	if ((glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS))
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void Wireframe(GLFWwindow* window) {

	if (glfwGetKey(window, GLFW_KEY_Z)) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

}