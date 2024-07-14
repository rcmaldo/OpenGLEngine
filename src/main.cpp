// std
#include <iostream>

// GL (glad needs to be included before glfw)
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const char* kVertexShaderSrc = "#version 460 core\n"
                                "layout (location = 0) in vec3 aPos;\n"
                                "void main()\n"
                                "{\n"
                                "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
"}\0";

const char* kFragmentShaderSrc = "#version 460 core\n"
                                "out vec4 fragColor;\n"
                                "void main()\n"
                                "{\n"
                                "    fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                "}\0";

void FramebufferSizeCallback(GLFWwindow* window, int newWidth, int newHeight);
void ProcessInput(GLFWwindow* window);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // enable on Mac only


    /* --v GLFW Window Initialization v-- */
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
    /* --^ GLFW Window Initialization ^-- */


    /* --v GLAD initialization v-- */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Cannot initialize GLAD" << std::endl;
        return -1;
    }
    /* --^ GLAD initialization ^-- */


    /* --v OpenGL Viewport Initialization v-- */
    int viewportWidth = 800;
    int viewportHeight = 600;
    glViewport(0, 0, viewportWidth, viewportHeight);
    /* --^ OpenGL Viewport Initialization ^-- */


    /* --v OpenGL Shader Compilations v-- */
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &kVertexShaderSrc, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &kFragmentShaderSrc, NULL);
    glCompileShader(fragmentShader);

    // Optional error checkers:
    int vertexSuccess;
    char vertexInfoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexSuccess);
    if (!vertexSuccess)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, vertexInfoLog);
        std::cout << "ERROR: Vertex shader compilation failed.\n" << vertexInfoLog << std::endl;
    }
    int fragmentSuccess;
    char fragmentInfoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentSuccess);
    if (!fragmentSuccess)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, fragmentInfoLog);
        std::cout << "ERROR: Fragment shader compilation failed.\n" << fragmentInfoLog << std::endl;
    }
    /* --^ OpenGL Shader Compilations ^-- */


    /* --v OpenGL Shader Attachment v-- */
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Optional error checkers:
    int linkSuccess;
    char linkInfoLog[512];
    glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &linkSuccess);
    if (!linkSuccess)
    {
        glGetShaderInfoLog(shaderProgram, 512, NULL, linkInfoLog);
        std::cout << "ERROR: Shader program linking failed.\n" << linkInfoLog << std::endl;
    }

    glUseProgram(shaderProgram);
    /* --^ OpenGL Shader Attachment ^-- */


    /* --v OpenGL Shader Cleanup v-- */
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    /* --^ OpenGL Shader Cleanup ^-- */


    /* --v OpenGL Vertex Buffer Object Initialization v-- */
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f
    };
    unsigned int vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    /* --^ OpenGL Vertex Buffer Object Initialization ^-- */

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