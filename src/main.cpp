#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>

int main()
{
  if (!glfwInit())
  {
    std::cerr << "Failed to initialize GLFW\n";
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(
      640,
      480,
      "OpenGL Project",
      nullptr,
      nullptr);

  if (!window)
  {
    std::cerr << "Failed to create GLFW window\n";
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  int version = gladLoadGL((GLADloadfunc)glfwGetProcAddress);

  if (version == 0)
  {
    std::cerr << "Failed to initialize GLAD\n";

    glfwDestroyWindow(window);
    glfwTerminate();

    return -1;
  }

  std::cout
      << "OpenGL "
      << GLAD_VERSION_MAJOR(version)
      << "."
      << GLAD_VERSION_MINOR(version)
      << '\n';

  // Create viewport
  glViewport(0, 0, 640, 480);

  // Create vertex
  float vertices[] = {
      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.0f, 0.5f, 0.0f};

  const char *vertexShaderSource =
      "#version 460 core\n"
      "layout (location = 0) in vec3 aPos;\n"
      "void main()\n"
      "{\n"
      "    gl_Position = vec4(aPos, 1.0);\n"
      "}\n";

  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);

  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  const char *fragmentShaderSource =
      "#version 460 core\n"
      "out vec4 fragColor;\n"
      "void main()\n"
      "{\n"
      "    fragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
      "}\n";

  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // kita butuh deklarasi unsigned int untuk diteruskan pada pemanggilan fungsi kemudian
  GLuint VBO;
  // bangkitkan buffers. kita butuh 1 id buffer.
  glGenBuffers(1, &VBO);
  // Kita pilih VBO buffer
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // Letakkan data vertices pada buffer. Mirip dengan fungsi memcpy di bahasa C.
  glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
  // atau
  // glBufferData(GL_ARRAY_BUFFER,
  // sizeof(vertices), vertices, GL_STATIC_DRAW);

  GLuint VAO;
  // bangkitkan array dari vertek.
  glGenVertexArrays(1, &VAO);
  // Ikat/Bind VAO.
  glBindVertexArray(VAO);
  // glVertexAttribPointer.
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (GLfloat)0, (GLvoid *)0);
  // berikan atribut vertek dengan nilai nilai default 0
  glEnableVertexAttribArray(0);

  while (!glfwWindowShouldClose(window))
  {
    glClearColor(
        0.1f,
        0.1f,
        0.15f,
        1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}