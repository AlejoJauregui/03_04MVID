#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cstdint>

//CALLBACK EXECUTED WHEN WINDOW SIZE CHANGES
void onChangeFrameBufferSize(GLFWwindow* window, const int32_t width, const int32_t height) noexcept
{
    glViewport(0, 0, width, height);
    std::cout << width << " " << height << std::endl;   
}
//This is the HandleInput method to the Inputs taht we could use
void handleInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //Verification of the esc button on the keyboard to close the window
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void render()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int, char*[]) 
{
    if (!glfwInit()) //Initialize the library GLFW 
    {
        std::cout << "Error Initializing GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Use OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Core Profile

    GLFWwindow* window = glfwCreateWindow(800, 600, "Testing OpenGL", nullptr, nullptr); // Create a windowned mode window and its OpenGL context
    if (!window)
    {
        std::cout << "Error Creating Window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); //Make the Window's context current

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Error Initializing GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, onChangeFrameBufferSize);
    glClearColor(0.0f, 0.3f, 0.6f, 1.0f);
    /*if (!gladLoadGL()) //Before to initialize OpenGL, we need to initialize GLAD
    {
        std::cout << "Error Initializing GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }*/

    



    //Main Loop
    while(!glfwWindowShouldClose(window)) //Loop until user closes the window
    {
        handleInput(window);

        render();

        glfwSwapBuffers(window); 
        glfwPollEvents();
    }

    //End GLFW systems
    glfwTerminate();
    return 0;
}


