#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Graphics pipeline is usually divided into 2 large parts: the first transforms your 3D coordinates into 2D coordinates and the 
// second part transforms the 2D coordinates into the actual colored pixels. 

// The graphics pipeline takes as input a set of 3D coordinates and transforms these to colored 2D pixels on your screen. The graphics
// can be divied into several steps where each step requries the output of the previous step as its input. All of these steps are highly 
// specialized (they have one speciific function) and can easily be executed in parallel. Due to the parallel nature, graphics cards of today
// have thousands of small processing cores to quickly process your data within the graphics pipeline. The processing cores run small programs on the GPU
// for each step of the pipeline. These small programs are called "Shaders".

// Shaders are written in OpenGL Shading Language (GLSL).

GLFWwindow* initWindow(int width, int height) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Hello Triangle", NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(window);

	// Load GLAD (OpenGL function pointer)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return nullptr;
	}

	return window;
	// Note that we might be concerned of potential dangling pointer by returning the pointer. But in fact, we are just handling off the <window> that is actually
	// created on the Heap. The local pointer 'window' will indeed get destroyed when it's first created. But the value it creates will be handed off
	// to the varible it gets assigned to. 
}



// OpenGL doesn't simply transform all your 3D coordinates to 2D pixels on your screen; OpenGL only processes 3D coordinates when 
// they are in a specific range between -1.0 and 1.0 on all 3 axes (x, y, and z). All coordinates within this NDC (Normalized Device Coordinates) range 
// will end up visible on your screen.

float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
};


/*
int main() {
	// Initialization of the windows:
	GLFWwindow* myWindow = initWindow(800, 600);

	if (myWindow == nullptr) {
		return -1;
	}

	unsigned int VAO;
	unsigned int VBO;
	glGenBuffers(1, &VBO); // 1 specifies the number of buffer objects to generate. Asks OpenGL to generate a unique ID(name) for a new buffer object, and stores the ID number into the variable.
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// From this point on, any buffer calls we make (on the GL_ARRAY_BUFFER target) will be used to configure the currently bound buffer, which is VBO.
	// Then we can make a call to the glBufferData function that copies the previously defined vertex data into the buffer's memory.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// ========================== Creating a Vertex Shader ========================================
	const char* vertexShaderSource = "#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"void main() {\n"
		"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	// it assigns attribute slot 0 to aPos. This is because OpenGL has a small numbered list of vertex attribute slots. 
	// Then the shader says whaever is in slot 0 call it aPos.


	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// The glShaderSource function takes the shader object to compile to its first argument. The second argument specifies how many strings we're passing as source code, 
	// which is only one. The 3rd parameter is the actual source code of the vertex shader and we can leave the 4th paramter to NULL.
	glCompileShader(vertexShader);

	int success;
	char infoLog[512]; // allocates 512 bytes to the character array.
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	// the glGetShaderiv is an OpenGL function used to query specific information (paramters) about a compiled shader object, such as its compilation status. 

	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	// ==================== Creating a Fragment Shader ====================
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main() {\n"
		"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // glCreateShader only returns the id of the shader. But it allocates a shader object inside OpenGL.
	// OpenGL can then use this id later on to find the right shader. 
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// ===================== Linking Vertex Attributes =========================
	// Define Vertex Attributes:
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);  // This code says for every vertex, read 3 floats from my VBO and put them into slot 0.
	glEnableVertexAttribArray(0); // takes the vertex attribute location as the argument.
	

	// ===================== Creating a shader program =======================
	// This shaderProgram is what actually links all the shaders together. 
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	}

	// The resulting program object can be activated by calling glUseProgram with the id of the shaderProgram
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3); // We specify the type we are drawing, the starting index of the vertex array, and the number of vertices we are drawing. 

	// Delete the shaderObjects once we've linked them into the program object.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader); // the glDelete marks the shader for deletion. It does not immediately delete, but will be destoryed when it gets disconnected.

	return 0;
}

*/