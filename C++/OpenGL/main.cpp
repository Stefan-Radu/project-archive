#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

int main() {

  GLFWwindow* window;

  if (not glfwInit()) {
    cout << "Error\n";
    return -1;
  }

  window = glfwCreateWindow(600, 400, "wow", NULL, NULL);

  if (not window) {
    glfwTerminate();
    cout << "Error\n";
    return -1;
  }

  glfwMakeContextCurrent(window);
  if(not glewInit() == GLEW_OK) {
    cout << "Error\n";
    return -1;
  }
  
  float positions[6] = {
    -0.5f, 0.5f,
    0.5f, 0.5f,
    0.0f, -0.5f
  };

  unsigned int buffer;
  glGenBuffers(1, &buffer); 
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);
  
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

  while (not glfwWindowShouldClose(window)) {

    glClear(GL_COLOR_BUFFER_BIT);
  
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
