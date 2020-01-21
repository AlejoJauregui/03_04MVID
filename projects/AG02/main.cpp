#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "engine/window.hpp"
#include "engine/input.hpp"

#include <iostream>
#include <cstdint>

void HandleInput()
{
    std::vector<std::pair<int, int>> keys = Input::instance()->GetKeys();
    for (auto& key : keys)
    {
        std::cout << key.first << " - " << key.second << std::endl;
    }
}

bool CheckShader(uint32_t shader)
{
    int success;
    char infolog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, nullptr, infolog);
            std::cout << "Error Compiling Shader" << infolog << std::endl;
            return false;
        }
    return true;
}
bool CheckProgram(uint32_t program)
{
    int success;
    char infolog[512];
    glGetShaderiv(program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(program, 512, nullptr, infolog);
            std::cout << "Error Linking Program" << infolog << std::endl;
            return false;
        }
    return true;
}

void Render(uint32_t VAO, uint32_t program)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 0, GL_UNSIGNED_INT, nullptr);
}

uint32_t CreateProgram()
{
    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main(){\n"
        "    gl_Position = vec4(aPos, 1.0);\n"
        "}\0";
    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main(){\n"
        "     FragColor = vec4(0.6, 0.6, 0.1, 1.0);\n"
        "}\0";
    const uint32_t  vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    CheckShader(vertexShader);

    const uint32_t  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    CheckShader(fragmentShader);

    const uint32_t program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    CheckProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}
uint32_t CreateVertexData(uint32_t* VBO, uint32_t* EBO)
{
    float vertices[] =
    {
        //Frist Triangle
         0.2f, 0.2f, 0.0f, //top right point
         0.2f, -0.2f, 0.0f, //bottom right point
         -0.5f, -0.5f, 0.0f, //bottom left point 
         -0.5f, 0.5f, 0.0f //top left point
    };
    uint32_t indexes[] =
    {
        0, 3, 1, //First triangle
        1, 3, 2 //Second Triangle
    };
    uint32_t VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, VBO);
    glGenBuffers(1, EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
     glEnableVertexAttribArray(0);

     glBindBuffer(GL_ARRAY_BUFFER, 0); //Unbind VBO

     glBindVertexArray(0);  //Unbind VAO

     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

     return VAO;
}

int main(int, char*[]) 
{
    Window* window = Window::instance();
    glClearColor(0.0f, 0.3f, 0.6f, 1.0f);

    uint32_t VBO, EBO;
    const uint32_t VAO = CreateVertexData(&VBO, &EBO);
    const uint32_t program = CreateProgram();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    //Main Loop
    while(window -> alive()) //Loop until user closes the window
    {
        HandleInput();

        Render(VAO, program);
        
        window->frame();
    }
    //delete BUFFERS methods for the VAO, VBO and EBO
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glDeleteProgram(program);
    return 0;
}


