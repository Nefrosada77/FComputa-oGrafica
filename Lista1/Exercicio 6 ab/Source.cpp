/* Hello Triangle - c�digo adaptado de https://learnopengl.com/#!Getting-started/Hello-Triangle 
 *
 * Adaptado por Rossana Baptista Queiroz
 * para a disciplina de Processamento Gr�fico - Unisinos
 * Vers�o inicial: 7/4/2017
 * �ltima atualiza��o em 14/08/2023
 *
 */

#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

// GLAD
#include <glad/glad.h>

// GLFW
#include <GLFW/glfw3.h>

//Classe que gerencia os shaders
#include "Shader.h"

//GLM
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Prot�tipo da fun��o de callback de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Protótipos das funções
int exercicio8();

// Dimens�es da janela (pode ser alterado em tempo de execu��o)
const GLuint WIDTH = 600, HEIGHT = 600;

// Fun��o MAIN
int main()
{
	// Inicializa��o da GLFW
	glfwInit();

	//Muita aten��o aqui: alguns ambientes n�o aceitam essas configura��es
	//Voc� deve adaptar para a vers�o do OpenGL suportada por sua placa
	//Sugest�o: comente essas linhas de c�digo para desobrir a vers�o e
	//depois atualize (por exemplo: 4.5 com 4 e 5)
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

	//Essencial para computadores da Apple
//#ifdef __APPLE__
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif

	// Cria��o da janela GLFW
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Exercico ¨- A / B! -- Gabriel", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Fazendo o registro da fun��o de callback para a janela GLFW
	glfwSetKeyCallback(window, key_callback);

	// GLAD: carrega todos os ponteiros d fun��es da OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	// Obtendo as informa��es de vers�o
	const GLubyte* renderer = glGetString(GL_RENDERER); /* get renderer string */
	const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	// Definindo as dimens�es da viewport com as mesmas dimens�es da janela da aplica��o
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);


	// Compilando e buildando o programa de shader

	Shader shader("HelloTriangle.vs","HelloTriangle.fs");

	// Gerando um buffer simples, com a geometria de um tri�ngulo
	// Exercicio 8
	GLuint VAO = exercicio8();
	
	//Habilita o shader que sera usado (glUseProgram)
	shader.Use();

	//Matriz de projeção (paralela ortográfica)
	// Exercício 1 da Lista 2
	glm::mat4 projection = glm::ortho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	// Exercício 2 da Lista 2
	//glm::mat4 projection = glm::ortho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
	//Enviando para o shader via variável do tipo uniform (glUniform....)
	shader.setMat4("projection",glm::value_ptr(projection));
	
	// Loop da aplica��o - "game loop"
	while (!glfwWindowShouldClose(window))
	{
		// Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as fun��es de callback correspondentes
		glfwPollEvents();

		// Limpa o buffer de cor
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //cor de fundo
		glClear(GL_COLOR_BUFFER_BIT);

		glLineWidth(8);
		glPointSize(20);

		glBindVertexArray(VAO); //Conectando ao buffer de geometria

		/*//OCTAGONO / Exercicio A)
		glDrawArrays(GL_TRIANGLE_FAN, 0, 10);
		glDrawArrays(GL_POINTS, 0, 9);*/

		/*//PENTAGONO / Exercicio B)
		glDrawArrays(GL_TRIANGLE_FAN, 0, 7);
		glDrawArrays(GL_POINTS, 0, 6);*/
		

		glBindVertexArray(0); //Desconectando o buffer de geometria

		// Troca os buffers da tela
		glfwSwapBuffers(window);
	}
	// Pede pra OpenGL desalocar os buffers
	glDeleteVertexArrays(1, &VAO);
	// Finaliza a execu��o da GLFW, limpando os recursos alocados por ela
	glfwTerminate();
	return 0;
}

// Fun��o de callback de teclado - s� pode ter uma inst�ncia (deve ser est�tica se
// estiver dentro de uma classe) - � chamada sempre que uma tecla for pressionada
// ou solta via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int exercicio8()
{
	// Aqui setamos as coordenadas x, y e z do tri�ngulo e as armazenamos de forma
	// sequencial, j� visando mandar para o VBO (Vertex Buffer Objects)
	// Cada atributo do v�rtice (coordenada, cores, coordenadas de textura, normal, etc)
	// Pode ser arazenado em um VBO �nico ou em VBOs separados
	GLfloat vertices[] = {
		//x   y    z    r    g    b

		/*//OCTAGONO / Exercicio A)
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, //M
		-0.2, 0.6, 0.0, 1.0, 1.0, 1.0, //J
		-0.6, 0.2, 0.0, 1.0, 0.0, 1.0, //K
		-0.6, -0.2, 0.0, 1.0, 1.0, 1.0, //L  
		-0.2, -0.6, 0.0, 0.0, 1.0, 1.0, //E
		0.2, -0.6, 0.0, 1.0, 1.0, 1.0, //F
		0.6, -0.2, 0.0, 0.5, 0.5, 0.5, //G
		0.6, 0.2, 0.0, 1.0, 1.0, 1.0, //H
		0.2, 0.6, 0.0, 1.0, 1.0, 0.0, //I
		-0.2, 0.6, 0.0, 1.0, 1.0, 1.0, //J*/

		/*//PENTAGONO / Exercicio B)
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, //J
		0.0, 0.6, 0.0, 1.0, 1.0, 1.0, //E
		-0.6, 0.2, 0.0, 1.0, 1.0, 1.0, //F
		-0.4, -0.5, 0.0, 1.0, 1.0, 1.0, //H
		0.4, -0.5, 0.0, 1.0, 1.0, 1.0, //I
		0.6, 0.2, 0.0, 1.0, 1.0, 1.0, //G
		0.0, 0.6, 0.0, 1.0, 1.0, 1.0 //E*/
	

	};

	GLuint VBO, VAO;
	//Gera��o do identificador do VBO
	glGenBuffers(1, &VBO);
	//Faz a conex�o (vincula) do buffer como um buffer de array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Envia os dados do array de floats para o buffer da OpenGl
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Gera��o do identificador do VAO (Vertex Array Object)
	glGenVertexArrays(1, &VAO);
	// Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de v�rtices
	// e os ponteiros para os atributos 
	glBindVertexArray(VAO);
	//Para cada atributo do vertice, criamos um "AttribPointer" (ponteiro para o atributo), indicando: 
	// Localiza��o no shader * (a localiza��o dos atributos devem ser correspondentes no layout especificado no vertex shader)
	// Numero de valores que o atributo tem (por ex, 3 coordenadas xyz) 
	// Tipo do dado
	// Se est� normalizado (entre zero e um)
	// Tamanho em bytes 
	// Deslocamento a partir do byte zero 

	//Atributo layout 0 - Posição - 3 valores dos 6 que descrevem o vértice
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Atributo layout 1 - Cor - 3 valores dos 6 que descrevem o vértice
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Observe que isso � permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de v�rtice 
	// atualmente vinculado - para que depois possamos desvincular com seguran�a
	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	// Desvincula o VAO (� uma boa pr�tica desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0); 

	return VAO;
}