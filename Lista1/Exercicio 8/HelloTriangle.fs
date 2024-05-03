//Código fonte do Fragment Shader (em GLSL)

#version 400

in vec3 vertexColor;
out vec4 color;

void main()
{
	color = vec4(vertexColor,1.0);
}