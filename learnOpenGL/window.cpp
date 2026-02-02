#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// ------------- This file is tied to <Hello Window> Unit of Getting Started ------------------


// This callback function is intended to be used as a callback function 
// when the window screen size gets resized. 
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// This glfwCreateWindow will specify the size of the window;
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Tells the CPU: From now on, any OpenGL command issued by this threafd should be executed on teh context associated with this specific window.
	glfwMakeContextCurrent(window);


	// We need to make the GLAD actually exists before we call any openGL functions.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Viewport
	// The first 2 paramters sets the location of the lower left corner of the window.
	// The third and fourth paramter sets the width and height of hte rendering window in pixels. 
	// This is actually a state setting inside OpenGL. It tells the GPU how to map its internal math to the viewport's pixels.
	glViewport(0, 0, 800, 600);
	// Some cool rendering knowledge:
	// Behind the scenes, OpenGL uses the data specified via glViewport to transform the 2D coordinates it processed to 
	// coordinates on your screen. For example, a processed point of location (-0.5, 0.5) would have its final. These coordinates are also known as NPC (Normalized Device Coordinates).
	// transformation be mapped to (200, 450) give viewport size of (800, 600). Note that processed coordinates in OpenGL are between -1 and 1 so we effectively mapp from the range (-1 to 1) to (0, 800) and (0, 600). 
	
	
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/*glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);*/

	// We don't want our application to just draw and quit immediately. We want to the application to keep drawing images and 
	// handling user input until the program has been explicitlyl told to stop. We thus create a while loop, 
	// which we call the render loop, that keeps on running until we tell GLFW to stop. 
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		// We will add rendering commands here.

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// Function Docs:
	// glfwWindowShouldClose: checks at the start of each loop iteration if GLFW has been instructed to close. if so, true returns and render loop stops running. 
	// glfwPollEvents: checks if any events are triggered (such as keyboard input or mouse movement events.), updates the window state, and call the registered function 
	//      that we can register via a callback.
	// glfwSwapBuffers: This is the line that swaps the front and back buffers. Your window has 2 images(buffers), in each frame, your program will draw a new frame, the screen
	//      keeps showign the old one. This avoids flickering and half-drawn frames. 
	//      And this function is what does the swapping. 
	glfwTerminate();

	return 0;
}