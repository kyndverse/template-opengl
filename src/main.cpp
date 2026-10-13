// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "external/stb_image.h"
// clang-format on

#include <iostream>

#include "ShaderManager.h"

constexpr int WINDOW_WIDTH = 1080;
constexpr int WINDOW_HEIGHT = 720;

int main() {
  // Initialize GLFW
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW\n";
    return -1;
  }

  // Configure OpenGL
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create Window
  GLFWwindow* window =
      glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Project", nullptr, nullptr);

  if (!window) {
    std::cerr << "Failed to create GLFW window\n";
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  // Initialize GLAD
  int version = gladLoadGL((GLADloadfunc)glfwGetProcAddress);

  if (version == 0) {
    std::cerr << "Failed to initialize GLAD\n";
    glfwDestroyWindow(window);
    glfwTerminate();
    return -1;
  }

  // Configure Viewport
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

  // Shader Config
  ShaderManager::GetInstance()->compileAndLink("assets/shaders/shader.vert",
                                               "assets/shaders/shader.frag");

  // clang-format off
  float vertices[] = {
    //posisi           //warna              //uv koordinat teksture
    0.0f,-0.5f,0.0f,   1.0f, 0.0f, 0.0f,    0.0f,0.0f,
    0.0f,0.5f,0.0f,    0.0f, 1.0f, 0.0f,    0.0f,1.0f,
    0.5f,-0.5f,0.0f,   0.0f, 0.0f, 1.0f,    1.0f,0.0f,
    0.5f,0.5f,0.0f,    1.0f, 0.0f, 0.0f,    1.0f,1.0f,
  };

  unsigned int indices[] = {
    0, 1, 2,
    1, 2, 3,  
  };
  // clang-format on

  // declaration
  GLuint VBO, VAO, EBO, texture;

  // generate buffer
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  glGenTextures(1, &texture);
  
  // texture wraping
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  // texture filtering
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // load texture image
  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true);
  std::string fileTex = "assets/textures/basecolor.png";
  unsigned char* data = stbi_load(fileTex.c_str(), &width, &height, &nrChannels, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cerr << "Failed to load texture\n";
  }

  stbi_image_free(data);

  // bind VBO to VAO
  glBindVertexArray(VAO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  // bind texture
  GLuint shaderProgram = ShaderManager::GetInstance()->getShaderProgram();

  float curAngle = 0.0f;
  const float toRadians = 3.14159265f / 180.0f;

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);

    float timeValue = glfwGetTime();
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    int vertexColorLocation = glGetUniformLocation(shaderProgram, "mycolor");
    glUniform1f(vertexColorLocation, greenValue);

    // Transformasi
    glm::mat4 model = glm::mat4(1.0f);
    int modelLocacation = glGetUniformLocation(shaderProgram, "model");
    // Scaling
    model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
    // Translasi
    model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));
    // Rotate
    curAngle += 0.01f;
    if (curAngle >= 360) {
      curAngle -= 360;
    }
    model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));

    glUniformMatrix4fv(modelLocacation, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(VAO);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Cleanup
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteVertexArrays(1, &VAO);
  glDeleteTextures(1, &texture);

  ShaderManager::GetInstance()->destroy();

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}