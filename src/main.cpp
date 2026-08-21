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
      1280,
      720,
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

  int version = gladLoadGL(glfwGetProcAddress);

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

  while (!glfwWindowShouldClose(window))
  {
    glClearColor(
        0.1f,
        0.1f,
        0.15f,
        1.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}