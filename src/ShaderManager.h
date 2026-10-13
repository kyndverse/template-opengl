#ifndef __SHADERMANAGER_H__
#define __SHADERMANAGER_H__

#pragma once
// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <fstream>
#include <iostream>
#include <string>

class ShaderManager
{
private:
  static ShaderManager *instance;
  unsigned int shaderProgram;

public:
  static ShaderManager *GetInstance();
  void compileAndLink(const char *vertexFile, const char *framgnetFile);
  unsigned int getShaderProgram();
  void destroy();
};

#endif