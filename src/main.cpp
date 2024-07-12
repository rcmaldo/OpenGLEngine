// std
#include <iostream>

// GL (glad needs to be included before glfw)
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void FramebufferSizeCallback(GLFWwindow* window, int newWidth, int newHeight);
void ProcessInput(GLFWwindow* window);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // enable on Mac only

    constexpr int kWindowWidth = 800;
    constexpr int kWindowHeight = 600;
    GLFWwindow* window = glfwCreateWindow(kWindowWidth, kWindowHeight, "HelloOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Cannot create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Cannot initialize GLAD" << std::endl;
        return -1;
    }

    int viewportWidth = 800;
    int viewportHeight = 600;
    glViewport(0, 0, viewportWidth, viewportHeight);

    while (!glfwWindowShouldClose(window))
    {
        ProcessInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}

void FramebufferSizeCallback(GLFWwindow* window, int newWidth, int newHeight)
{
    glViewport(0, 0, newWidth, newHeight);
}

void ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}