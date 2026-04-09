//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include "stb_image.h"
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include "shader.h"
//#include "model.h"
//#include "camera.h"
//
//#include <iostream>
//
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//// camera
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//float lastX = (float)SCR_WIDTH / 2.0f;
//float lastY = (float)SCR_HEIGHT / 2.0f;
//bool firstMouse = true;
//
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//	glViewport(0, 0, width, height);
//}
//
//void mouse_callback(GLFWwindow * window, double xposIn, double yposIn) {
//	float xpos = static_cast<float>(xposIn);
//	float ypos = static_cast<float>(yposIn);
//	if (firstMouse) {
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos;
//
//	lastX = xpos;
//	lastY = ypos;
//
//	camera.ProcessMouseMovement(xoffset, yoffset);
//
//}
//
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
//	camera.ProcessMouseScroll(yoffset);
//}
//
//void processInput(GLFWwindow* window) {
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//		glfwSetWindowShouldClose(window, true);
//	}
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
//		camera.ProcessKeyboard(FORWARD, deltaTime);
//	}
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
//		camera.ProcessKeyboard(BACKWARD, deltaTime);
//	}
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
//		camera.ProcessKeyboard(LEFT, deltaTime);
//	}
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
//		camera.ProcessKeyboard(RIGHT, deltaTime);
//	}
//	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
//		camera.ProcessKeyboard(UP, deltaTime);
//	}
//	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
//		camera.ProcessKeyboard(DOWN, deltaTime);
//	}
//}
//
//unsigned int loadCubemap(vector<std::string> faces) 
//{
//	unsigned int textureID;
//	glGenTextures(1, &textureID);
//	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
//
//	int width, height, nrComponents;
//	for (unsigned int i = 0; i < faces.size(); i++) {
//		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
//		if (data) {
//			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//			stbi_image_free(data);
//		}
//		else {
//			std::cout << "Cubemap texture failed to load at path: " << faces[i] << endl;
//			stbi_image_free(data);
//		}
//	}
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//
//	return textureID;
//}
//
//unsigned int loadTexture(char const *path) {
//	unsigned int textureID;
//	glGenTextures(1, &textureID);
//
//	int width, height, nrComponents;
//	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
//	if (data) {
//		GLenum format;
//		if (nrComponents == 1) {
//			format = GL_RED;
//		}
//		else if (nrComponents == 3) {
//			format = GL_RGB;
//		}
//		else if (nrComponents == 4) {
//			format = GL_RGBA;
//		}
//
//		glBindTexture(GL_TEXTURE_2D, textureID);
//		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
//
//		stbi_image_free(data);
//	}
//	else {
//		std::cout << "" << endl;
//		stbi_image_free(data);
//	}
//	
//	return textureID;
//}
//
//int main() {
//	
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//	// glfw window creation
//	// --------------------
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Reflections with Skybox", NULL, NULL);
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//	// glad
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//	
//	// configure global opengl state
//	// ---------------------------
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//	Shader shader("6.2.cubemaps.vs", "6.2.cubemaps.fs");
//	Shader skyboxShader("6.2.skybox.vs", "6.2.skybox.fs");
//	Shader transparentShader("6.2.transparent.vs", "6.2.transparent.fs");
//
//	// This is the backpack shader that we try to render
//	Model ourModel("backpack/backpack.obj");
//
//	// we can also choose to render a cube instread
//	float cubeVertices[] = {
//		// positions          // normals
//		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//
//		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//
//		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//
//		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//
//		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//
//		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
//	};
//
//	float transparentVertices[] = {
//	    // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
//	    0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
//	    0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
//	    1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
//	
//	    0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
//	    1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
//	    1.0f,  0.5f,  0.0f,  1.0f,  0.0f
//	};
//
//	float skyboxVertices[] = {
//		// positions          
//		-1.0f,  1.0f, -1.0f,
//		-1.0f, -1.0f, -1.0f,
//		 1.0f, -1.0f, -1.0f,
//		 1.0f, -1.0f, -1.0f,
//		 1.0f,  1.0f, -1.0f,
//		-1.0f,  1.0f, -1.0f,
//
//		-1.0f, -1.0f,  1.0f,
//		-1.0f, -1.0f, -1.0f,
//		-1.0f,  1.0f, -1.0f,
//		-1.0f,  1.0f, -1.0f,
//		-1.0f,  1.0f,  1.0f,
//		-1.0f, -1.0f,  1.0f,
//
//		 1.0f, -1.0f, -1.0f,
//		 1.0f, -1.0f,  1.0f,
//		 1.0f,  1.0f,  1.0f,
//		 1.0f,  1.0f,  1.0f,
//		 1.0f,  1.0f, -1.0f,
//		 1.0f, -1.0f, -1.0f,
//
//		-1.0f, -1.0f,  1.0f,
//		-1.0f,  1.0f,  1.0f,
//		 1.0f,  1.0f,  1.0f,
//		 1.0f,  1.0f,  1.0f,
//		 1.0f, -1.0f,  1.0f,
//		-1.0f, -1.0f,  1.0f,
//
//		-1.0f,  1.0f, -1.0f,
//		 1.0f,  1.0f, -1.0f,
//		 1.0f,  1.0f,  1.0f,
//		 1.0f,  1.0f,  1.0f,
//		-1.0f,  1.0f,  1.0f,
//		-1.0f,  1.0f, -1.0f,
//
//		-1.0f, -1.0f, -1.0f,
//		-1.0f, -1.0f,  1.0f,
//		 1.0f, -1.0f, -1.0f,
//		 1.0f, -1.0f, -1.0f,
//		-1.0f, -1.0f,  1.0f,
//		 1.0f, -1.0f,  1.0f
//	};
//
//	// cube VAO
//	unsigned int cubeVAO, cubeVBO;
//	glGenVertexArrays(1, &cubeVAO);
//	glGenBuffers(1, &cubeVBO);
//	glBindVertexArray(cubeVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//
//	// window VAO
//	unsigned int transparentVAO, transparentVBO;
//	glGenVertexArrays(1, &transparentVAO);
//	glGenBuffers(1, &transparentVBO);
//	glBindVertexArray(transparentVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, transparentVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//
//	// skybox VAO
//	unsigned int skyboxVAO, skyboxVBO;
//	glGenVertexArrays(1, &skyboxVAO);
//	glGenBuffers(1, &skyboxVBO);
//	glBindVertexArray(skyboxVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//
//	// load textures
//	// --------------
//	vector<std::string> faces{
//		"skybox/right.jpg",
//		"skybox/left.jpg",
//		"skybox/top.jpg",
//		"skybox/bottom.jpg",
//		"skybox/front.jpg",
//		"skybox/back.jpg"
//	};
//	unsigned int cubemapTexture = loadCubemap(faces);
//	
//	// load window textures
//	
//	unsigned int transparentTexture = loadTexture("window.png");
//
//	vector<glm::vec3> windows{
//	    glm::vec3(-1.5f, 0.0f, -0.48f),
//	    glm::vec3(1.5f, 0.0f, 0.51f),
//	    glm::vec3(0.0f, 0.0f, 0.7f),
//	    glm::vec3(-0.3f, 0.0f, -2.3f),
//	    glm::vec3(0.5f, 0.0f, -0.6f)
//	};
//
//	// shader configuration
//	// ----------------------
//	shader.use();
//	shader.setInt("skybox", 0);
//
//	skyboxShader.use();
//	skyboxShader.setInt("skybox", 0);
//
//	transparentShader.use();
//	transparentShader.setInt("texture1", 0); // setting the semi-transparent shader
//
//	// render loop
//	while (!glfwWindowShouldClose(window)) {
//		// per-frame time logic
//		float currentFrame = static_cast<float>(glfwGetTime());
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		// input
//		// -----
//		processInput(window);
//
//		// created sorted window layers
//		std::map<float, glm::vec3> sorted;
//		for (unsigned int i = 0; i < windows.size(); i++) {
//			float distance = glm::length(camera.Position - windows[i]);
//			sorted[distance] = windows[i];
//		}
//
//		// render
//		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		// draw scene as normal
//		shader.use();
//		glm::mat4 model = glm::mat4(1.0f);
//		glm::mat4 view = camera.GetViewMatrix();
//		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);
//		shader.setMat4("model", model);
//		shader.setMat4("view", view);
//		shader.setMat4("projection", projection);
//		shader.setVec3("cameraPos", camera.Position);
//
//		// cubes
//		glBindVertexArray(cubeVAO);
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
//		//glDrawArrays(GL_TRIANGLES, 0, 36);
//		ourModel.Draw(shader);
//		glBindVertexArray(0);
//
//		// draw the windows
//		transparentShader.use();
//		transparentShader.setMat4("view", view);
//		transparentShader.setMat4("projection", projection);
//		transparentShader.setVec3("cameraPos", camera.Position);
//
//		glBindVertexArray(transparentVAO);
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, transparentTexture);
//		for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); it++) {
//			model = glm::mat4(1.0f);
//			model = glm::translate(model, it->second);
//			transparentShader.setMat4("model", model);
//			glDrawArrays(GL_TRIANGLES, 0, 6);
//		}
//
//		glBindVertexArray(0);
//
//		// draw skybox as last
//		glDepthFunc(GL_LEQUAL);
//		skyboxShader.use();
//		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
//		skyboxShader.setMat4("view", view);
//		skyboxShader.setMat4("projection", projection);
//		glBindVertexArray(skyboxVAO);
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		glBindVertexArray(0);
//		glDepthFunc(GL_LESS);
//
//		// glfw: swap buffers and pill IO events
//		// -------------------------------------
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//
//	}
//	glDeleteVertexArrays(1, &cubeVAO);
//	glDeleteVertexArrays(1, &skyboxVAO);
//	glDeleteBuffers(1, &cubeVBO);
//	glDeleteBuffers(1, &skyboxVBO);
//
//	glfwTerminate();
//	return 0;
//}
