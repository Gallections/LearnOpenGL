// 1. Make sure only the happy face looks in the other/reverse direction by changing
// the fragment shader:

// Proposed Solution:

//#version 330 core
//out vec4 FragColor;
//
//in vec3 ourColor;
//in vec2 TexCoord;
//
//uniform sampler2D texture1;
//uniform sampler2D texture2;
//
//void main() {
//	FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.2);
//}


// 2. Experiment with the different texture wrapping methods by specifying texture coordinates in 
// the range 0.0f to 2.0f instead of 0.0f to 1.0f. See if you can display 4 smiley faces on a single 
// container image clamped at its edge: solution, result. See if you can experiment with other wrapping methods as well.


