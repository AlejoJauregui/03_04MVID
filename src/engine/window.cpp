#include "engine/input.hpp"
#include "engine/window.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

//CALLBACK EXECUTED WHEN WINDOW SIZE CHANGES
void onChangeFrameBufferSize(GLFWwindow* window, const int32_t width, const int32_t height) noexcept
{
    glViewport(0, 0, width, height);
    std::cout << width << " " << height << std::endl;
}
//Input callback Method to recognize the option that a user enter to the game
void OnKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE & action == GLFW_PRESS) //For an unexpected reason if I put the double & the compiler identifies an error in this if
        glfwSetWindowShouldClose(window, true);
    else
        Input::instance()->AddKey(key, action);
}


Window :: Window()
{

    if (!glfwInit()) //Initialize the library GLFW 
    {
        std::cout << "Error Initializing GLFW" << std::endl;
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Use OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Core Profile

    window_ = glfwCreateWindow(800, 600, "Testing OpenGL", nullptr, nullptr); // Create a windowned mode window and its OpenGL context
    if (!window_)
    {
        std::cout << "Error Creating Window" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window_); //Make the Window's context current

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Error Initializing GLAD" << std::endl;
        exit(-1);
    }
    glfwSetFramebufferSizeCallback(window_, onChangeFrameBufferSize);
    glfwSetKeyCallback(window_, OnKeyPress);
}
//Constructort Method
Window :: ~Window()
{
    glfwTerminate();
}
Window* Window :: instance()
{
	static Window instanceWindow;
	return &instanceWindow;
}

bool Window::alive() const
{
    return !glfwWindowShouldClose(window_);
}
void Window::frame() const
{
    Input::instance()->Clear(); //We're gonna clear the inputs that the user press on before frames
    glfwSwapBuffers(window_);
    glfwPollEvents();
}

