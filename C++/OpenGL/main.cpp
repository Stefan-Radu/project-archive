#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>
#include <string>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

static std::string ParseShader (const std::string &filePath) {

  std::ifstream fin (filePath);
 
  std::string shader, aux;
  while (getline (fin, aux, '\n')) {
    shader += aux; 
    shader += '\n';
  }

  fin.close ();
  return shader;
}

static unsigned int CompileShader (unsigned int type, const std::string &source) {
  
  unsigned int id = glCreateShader (type);
  const char *src = source.c_str ();
  glShaderSource (id, 1, &src, nullptr);
  glCompileShader (id);
 
  int result;
  glGetShaderiv (id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    int length;
    glGetShaderiv (id, GL_INFO_LOG_LENGTH, &length);
    char message[length];
    glGetShaderInfoLog (id, length, &length, message);

    std::cerr << "Failed to compile " << 
      (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;

    std::cerr << message << std::endl;

    glDeleteShader (id);
    return 0;
  }

  return id;
}

static unsigned int CreateShader (const std::string &vertexShader, const std::string &fragmentShader) {

  unsigned int program = glCreateProgram ();
  unsigned int vs = CompileShader (GL_VERTEX_SHADER, vertexShader);
  unsigned int fs = CompileShader (GL_FRAGMENT_SHADER, fragmentShader);

  glAttachShader (program, vs);
  glAttachShader (program, fs);
  glLinkProgram (program);
  glValidateProgram (program);

  glDeleteShader (vs);
  glDeleteShader (fs);

  return program;
}

int main () {

  GLFWwindow *window;

  if (not glfwInit ()) {
    std::cerr << "glfw not initialized\n";
    return -1;
  }
  
  glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint (GLFW_RESIZABLE, GL_FALSE);

  window = glfwCreateWindow (800, 600, "wow", nullptr, nullptr);

  if (not window) {
    glfwTerminate ();
    std::cerr << "no window\n";
    return -1;
  }

  glfwMakeContextCurrent (window);
  glfwSwapInterval (1);

  if (glewInit () != GLEW_OK) {
    std::cerr << "glew not initialized\n";
    return -1;
  }
  
  std::cerr << "glVersion: " << glGetString (GL_VERSION) << std::endl; 
  
  {
    float positions[] = {
      -0.5f, -0.5f,
      0.5f, -0.5f, 
      0.5f,  0.5f,
      -0.5f,  0.5f
    };

    unsigned int indices[] = {
      0, 1, 2,
      2, 3, 0
    };

    unsigned int vao;
    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);

    VertexBuffer vb (positions, 4 * 2 * sizeof (float));
    
    glEnableVertexAttribArray (0);
    glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, sizeof (float) * 2, 0);

    IndexBuffer ib (indices, 6);

    std::string vertexShader = ParseShader ("res/shaders/shader.vs");
    std::string fragmentShader = ParseShader ("res/shaders/shader.fs");

    unsigned int shader = CreateShader (vertexShader, fragmentShader);
    glUseProgram (shader);

    int location = glGetUniformLocation (shader, "u_Color");
    ASSERT (location != -1);

    glBindVertexArray (0);
    glUseProgram (0);
    glBindBuffer (GL_ARRAY_BUFFER, 0);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);

    float r = 0.0f, inc = 0.03f;

    while (not glfwWindowShouldClose (window)) {

      glClear (GL_COLOR_BUFFER_BIT);
    
      if (r > 1.0f or r < 0.0f) {
        inc = -inc;
      }
      r += inc;

      glUseProgram (shader);
      glUniform4f (location, r, 0.3f, 0.8f, 1.0f);

      glBindVertexArray (vao); 
      ib.Bind ();

      GLCall (glDrawElements (GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

      glfwSwapBuffers (window);

      glfwPollEvents ();
    }

    glDeleteProgram (shader);
  }

  glfwTerminate ();
  return 0;
}
