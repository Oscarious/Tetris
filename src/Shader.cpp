#include "Shader.h"
#include <iostream>

Shader::Shader(const std::string& vs_fn, const std::string& fs_fn) {
  // read vs file
  std::ifstream ifs(vs_fn, std::ifstream::in);
  std::stringstream vs_ss;
  vs_ss << ifs.rdbuf();
  ifs.close();

  // read fs file
  std::stringstream fs_ss;
  ifs.open(fs_fn, std::ifstream::in);
  fs_ss << ifs.rdbuf();
  Init(vs_ss.str(), fs_ss.str());
}

void Shader::Init(const std::string& vs, const std::string& fs) {
  // 1. retrieve the vertex/fragment source code from filePath
  const char* vShaderCode = vs.c_str();
  const char* fShaderCode = fs.c_str();
  // 2. compile shaders
  unsigned int vertex{}, fragment{};
  // vertex shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);
  CheckCompileErrors(vertex, "VERTEX");
  // fragment Shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);
  CheckCompileErrors(fragment, "FRAGMENT");
  // shader Program
  id_ = glCreateProgram();
  glAttachShader(id_, vertex);
  glAttachShader(id_, fragment);
  glLinkProgram(id_);
  CheckCompileErrors(id_, "PROGRAM");
  // delete the shaders as they're linked into our program now and no longer necessery
  glDeleteShader(vertex);
  glDeleteShader(fragment);

}

void Shader::CheckCompileErrors(GLuint shader, std::string type)
{
  GLint success{};
  GLchar infoLog[1024];
  if (type != "PROGRAM")
  {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderInfoLog(shader, 1024, NULL, infoLog);
      std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
      throw std::runtime_error("Shaders Compilation error");
    }
  }
  else
  {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success)
    {
      glGetProgramInfoLog(shader, 1024, NULL, infoLog);
      std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
      throw std::runtime_error("Shaders Linkage error");
    }
  }
}