#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <iostream>


int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;



// shaders

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
void main() {
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)";






int main() {

    // if glfw cant start, handle errors
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return 1;
    }

    // tell glfw what version and profile we want
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create our window and handle errors
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OBJ Loader", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create OpenGL window\n";
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }


    // vertices (0-1 is like 0-100% of the screen's position)
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };  


    
    // create vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER); // set the shader variable to type vertex shader

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // attach the actual shader source code to the vertex shader variable
    glCompileShader(vertexShader);

    // create fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // set the shader variable to type fragment shader

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); // attach the actual shader source code to the fragment shader
    glCompileShader(fragmentShader);

    // create a shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    // attach vertex and fragment shaders to the program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram); // links into one final shader object

    // sets shader as the one to be used during any subsequent shader calls
    glUseProgram(shaderProgram); 

    // clean up shaders since they are no longer needed (attached to the program)
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);  




    // vao code
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);  

    glBindVertexArray(VAO);

    // vbo code

    unsigned int VBO; // create the data where the vbo is
    glGenBuffers(1, &VBO); // generate the buffer id by passing the VBO variable

    glBindBuffer(GL_ARRAY_BUFFER, VBO); // sets vbo as the current array buffer (any changes made to array buffer will happen to vbo)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // reserves data using it's parameters inside the current array buffer (we set it to the vbo object)

    // tell opengl how to read the vertex code (idek)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  

    // main loop (put inside while loop)
    while (!glfwWindowShouldClose(window)) {
        glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);


        // background color and swap buffers
        glClearColor(0.08f, 0.09f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // destroy window and terminate
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
