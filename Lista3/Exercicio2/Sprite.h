#pragma once

//GLM
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

class Sprite
{
    public:
    Sprite() {} //Método construtor padrão
    ~Sprite(); //Método destrutor

    void inicializar(glm::vec3 pos=glm::vec3(0), glm::vec3 escala = glm::vec3(1), float angulo = 0.0, glm::vec3 cor = glm::vec3(1.0, 1.0, 0.0));
    void atualizar();
    void desenhar();
    void finalizar();

    inline void setShader(Shader *shader) { this->shader = shader; }
    inline void setAngulo(float angulo) { this->angulo = angulo; }
    protected:

    GLuint VAO; //Identificador do buffer de geometria VAO

    //Transformações na geometria
    glm::vec3 pos, escala;
    float angulo;

    Shader *shader;
};