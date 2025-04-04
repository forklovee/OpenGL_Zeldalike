#include <cstdio>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    // Update viewport size
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

int main(int argc, char* argv[])
{
    printf("Hello GLFW!\n");

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL ZeldaLike [WIP]", NULL, NULL);
    if (window == NULL){
        printf("Failed to create GLFW window!\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        printf("Failed to initialize GLAD!\n");
        return -1;
    }

    glViewport(0, 0, 800, 600);
    // bind window size chages to viewport size change
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // Set polygon mode
    bool bWireframeMode = false;
    glPolygonMode(GL_FRONT_AND_BACK, (bWireframeMode) ? GL_LINE : GL_FILL);

    float vertices[] = {
        0.5f, 0.5f, 0.0f, // top right
        1.0f, 0.0f, 0.0f, // color 1
        0.5f, -0.5f, 0.0f, // bottom right
        0.0f, 1.0f, 0.0f, // color 2
        -0.5f, -0.5f, 0.0f, // bottom left
        0.0f, 0.0f, 1.0f, // color 3
        -0.5f, 0.5f, 0.0f, // top left
        1.0f, 1.0f, 0.0f // color 4
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3 // second triangle
    };

    // Generate and bind Vertex Array Object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate and bind Vertex Buffer Object, and copy vertices to it
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Generate and bind Element Buffer Object, and copy indices to it
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Set Vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(0*sizeof(float)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // Define and compile Vertex Shader
    const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 vertexColorData;"
    "out vec4 vertexColor;"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "   vertexColor = vec4(vertexColorData, 1.0);"
    "}\0";
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int vertexShaderCompileSuccess;
    char vertexShaderCompileInfoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShaderCompileSuccess);
    if (!vertexShaderCompileSuccess)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, vertexShaderCompileInfoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED: %s\n", vertexShaderCompileInfoLog);
    }

    // Define and compile Fragment Shader
    const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 modulate;"
    "in vec4 vertexColor;"
    "void main()\n"
    "{\n"
    "    FragColor = vertexColor * modulate;\n"
    "}\0";
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    int fragmentShaderCompileSuccess;
    char fragmentShaderCompileInfoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentShaderCompileSuccess);
    if (!fragmentShaderCompileSuccess)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, fragmentShaderCompileInfoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED: %s\n", fragmentShaderCompileInfoLog);
    }

    //Combine Vertex and Fragment shader to one program.
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    int shaderProgramCompileSuccess;
    char shaderProgramCompileInfoLog[512];
    glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &shaderProgramCompileSuccess);
    if (!shaderProgramCompileSuccess)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, shaderProgramCompileInfoLog);
        printf("ERROR::SHADER::PROGRAM::COMPILATION_FAILED: %s\n", shaderProgramCompileInfoLog);
    }
    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Bind currently used VAO
    glBindVertexArray(VAO);

    // render loop
    while(!glfwWindowShouldClose(window)){
        processInput(window);


        glClearColor(0.4f, 0.2f, 0.15f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        float timeValue = glfwGetTime();
        float brightness = (std::sin(timeValue) / 2.f) + .5f;
        int modulateLocation = glGetUniformLocation(shaderProgram, "modulate");
        if (modulateLocation > -1)
        {
            glUseProgram(shaderProgram);
            glUniform4f(modulateLocation, brightness, brightness, brightness, 1.0);
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Unbind VAO
    glBindVertexArray(0);

    glfwTerminate();
    return 1;
}