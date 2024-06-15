#include "Sprite.h"

Sprite::~Sprite()
{
    // Pede pra OpenGL desalocar os buffers
	glDeleteVertexArrays(1, &VAO);
}

void Sprite::inicializar(glm::vec3 pos, glm::vec3 escala, float angulo, glm::vec3 cor)
{
    this->pos = pos;
    this->escala = escala;
    this->angulo = angulo;

    //Especificação da geometria da sprite (quadrado, 2 triangulos)
    GLfloat vertices[] = {
		//x   y    z    r      g      b
		-0.5, 0.5, 0.0, cor.r, cor.g, cor.b, //v0
        -0.5,-0.5, 0.0, cor.r, cor.g, cor.b, //v1
         0.5, 0.5, 0.0, cor.r, cor.g, cor.b, //v2
        -0.5,-0.5, 0.0, cor.r, cor.g, cor.b, //v1
         0.5,-0.5, 0.0, cor.r, cor.g, cor.b, //v3
         0.5, 0.5, 0.0, cor.r, cor.g, cor.b  //v2
	};

	GLuint VBO;
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

}

void Sprite::atualizar()
{
    glm::mat4 model = glm::mat4(1); //matriz identidade
    model = glm::translate(model, pos);
	model = glm::rotate(model,glm::radians(angulo), glm::vec3(0.0, 0.0, 1.0));
    model = glm::scale(model, escala);
    shader->setMat4("model", glm::value_ptr(model));
}

void Sprite::desenhar()
{
    atualizar();

    glBindVertexArray(VAO); //Conectando ao buffer de geometria

	// Poligono Preenchido - GL_TRIANGLES
	glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0); //desconectando o buffer de geometria

}