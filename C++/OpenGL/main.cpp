#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main () {

  GLFWwindow *window;
  
  if (not glfwInit ()) {
    std::cerr << "glfw not initialized\n";
    return -1;
  }
  
  window = glfwCreateWindow (800, 600, "wow", nullptr, nullptr);
 
  if (not window) {
    glfwTerminate ();
    std::cerr << "no window\n";
    return -1;
  }

  glfwMakeContextCurrent (window);

  while (not glfwWindowShouldClose (window)) {

    glClear (GL_COLOR_BUFFER_BIT);

    glBegin (GL_TRIANGLES);
    glVertex2d (-0.5f, 0.5f);
    glVertex2d (0.5f, 0.5f);
    glVertex2d (0.0f, -0.5f);
    glEnd ();

    glfwSwapBuffers (window);

    glfwPollEvents ();
  }

  glfwTerminate ();
  return 0;
}
