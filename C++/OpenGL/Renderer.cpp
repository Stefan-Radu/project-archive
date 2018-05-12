#include <iostream>

#include "Renderer.h"

void GLClearError () {

  while (glGetError ());
}

bool GLLogCall (const char *function, const char *file, const int line) {

  if (GLenum error = glGetError ()) {
    std::cerr << function << ' ' << file << " at line " << line
      << " EROOR NAME: " << error << std::endl;
    return false;
  }
  return true;
}
