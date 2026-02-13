// This file is related to the Shader unit of OpenGL.
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"

// EXERCISES:
// 1. Adjust the vertex shader so that the triangle is upside down:
// We know an example of set of vertices would be
float vertices[] = {
    0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    0.0f,  0.5f, 0.0f,
};
// if we want to invert the triangle, we have to invert all the y components
// thus in the shader code, we need to set the gl_Position to have the y component inverted

// as you can see, we set the shader source to be taking -aPos.y
//  #version 330 core
//  layout(location = 0) in vec3 aPos;
//  layout(location = 1) in vec3 aColor;
//  out vec3 ourColor;
//  void main() {
//      gl_Position = vec4(aPos.x, -aPos.y, aPos.z, 1.0);
//      ourColor = aColor;
//  }


// 2. Specify a horizontal offset via a uniform and move the triangle to the right side of the screen in the vertex shader using this offset value.
// IN CPP FILE:
//float offset = 0.5f;
//ourShader.setFloat(offset);

// IN VERTEX SHADER SOURCE CODE:

//#version 330 core
//layout(location = 0) in vec3 aPos;
//layout(location = 1) in vec3 aColor;
//out vec3 ourColor;
//
//uniform float offset;
//
//void main() {
//    gl_Position = vec4(aPos.x + offset, aPos.y, aPos.z, 1.0);
//    ourColor = aColor
//}


// 3. Output the vertex position to the fragment shader using the out keyword and set the fragment's color equal to this vertex position (see how even the vertex position values are interpolated across the triangle). Once you managed to do this; try to answer the following question: why is the bottom-left side of our triangle black?
// VERTEX SHADER
//#version 330 core
//layout(location = 0) in vec3 aPos;
//
//out vec3 ourPos;
//void main() {
//    gl_Position = vec4(aPos, 1.0);
//    ourPos = aPos;
//}

// FRAGMENT SHADER
//#version 330 core
//out vec4 FragColor;
//
//in vec3 ourPos;
//void main() {
//    FragColor = vec4(ourPos, 1.0f);
//}

// Since we notice that the bottom left value we pass in is (-0.5f, -0.5f, 0.0f),
// this gets capped to (0f, 0f, 0f), which is black in rgb colors.
