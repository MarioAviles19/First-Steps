#pragma once

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
inline std::string LoadShaderFromFile(const std::string& filePath){
  std::ifstream shaderFile;
  std::string shaderSource;

  shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    
    shaderFile.open(filePath);

    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();

    shaderFile.close();

    shaderSource = shaderStream.str();

  } catch (std::ifstream::failure& e){

    std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ:" << e.what() << std::endl;
    return "";

  }
  return shaderSource;
}

class Shader{

  public:
    unsigned int ID;
    Shader(const char* vertexPath, const char* fragmentPath){


      std::string vertexCode = LoadShaderFromFile(vertexPath);
      std::string fragmentCode = LoadShaderFromFile(fragmentPath);
      const char* vertexShaderSource = vertexCode.c_str();
      const char* fragShaderSource = fragmentCode.c_str();


      unsigned int fragmentShader;
      fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(fragmentShader, 1, &fragShaderSource, NULL);
      glCompileShader(fragmentShader);

      unsigned int vertexShader;

      vertexShader = glCreateShader(GL_VERTEX_SHADER);
      glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
      glCompileShader(vertexShader);

      int success;
      char infoLog[512];
      glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

      if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
      }
      glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
      if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
          << infoLog << std::endl;
      }
      ID = glCreateProgram();

      glAttachShader(ID, vertexShader);
      glAttachShader(ID, fragmentShader);
      glLinkProgram(ID);

      glGetProgramiv(ID, GL_LINK_STATUS, &success);

      if(!success){
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::LINK::PROGRAM::COMPILATION_FAILED\n"<< infoLog << std::endl;
      }

      glDeleteShader(vertexShader);
      glDeleteShader(fragmentShader);

    }

    void use(){

      glUseProgram(ID);

    }

    void setBool(const std::string &name, bool value) const{

      glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);

    }
    void setInt(const std::string &name, int value) const{

      glUniform1i(glGetUniformLocation(ID, name.c_str()), value);

    }
    void setFloat(const std::string &name, float value) const{

      glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    void setMatrix4(const std::string &name, glm::mat4 value)
    {
      glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }
    void setVector3f(const std::string &name, glm::vec3 value)
    {
      glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
    }

};
