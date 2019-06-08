void show_mandelbrot() {
  loadPixels();
  
  float x = map(mouseX, 0, width - 1, -1.5, 1.5);
  float y = map(mouseY, 0, height - 1, -1.5, 1.5);

  Complex_nr c = new Complex_nr(x, y);

  for (int i = 0; i < height; i ++) {
    for (int j = 0; j < width; j ++) {
      
      int index = i * width + j;

      float cur_x = map(j, 0, width - 1, -1.5, 1.5);
      float cur_y = map(i, 0, height - 1, -1.5, 1.5);
      
      Complex_nr z = new Complex_nr(cur_x, cur_y);
 
      int max_iterations = 100;
      int it;
      for (it = 0; it < max_iterations; it ++) {
        z.sq();
        z.add(c);
        if (z.modulo() > 2) {
          break;
        }
      }

      if (it == max_iterations) {
        pixels[index] = color(0);
        continue;
      }
      
      float hu = map(it, 0, max_iterations, 0, 255);
      hu += 155;
      hu %= 256;
      pixels[index] = color(hu, 255, 255);
      
    }
  }
  updatePixels();
}



void setup() {
  colorMode(HSB);
  size(720, 720);
  background(0);
}

void draw() {
  show_mandelbrot();
}