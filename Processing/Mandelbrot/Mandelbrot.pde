double x_l = -2.5, x_r = 1.5;
double y_u = -1.5, y_d = 1.5;
int max_iterations = 100;
int cnt = 0;

void zoom() {

  double dist_x = (x_r - x_l) / 4.0f;
  double dist_y = (y_d - y_u) / 4.0f;

  double poz_of_x = map_this(mouseX, 0, 1080, x_l, x_r);
  double poz_of_y = map_this(mouseY, 0, 720, y_u, y_d);

  x_l = poz_of_x - dist_x;
  x_r = poz_of_x + dist_x;
  y_u = poz_of_y - dist_y;
  y_d = poz_of_y + dist_y;
  max_iterations += 10;
  print(x_l, x_r, y_u, y_d, cnt, '\n');
}

double map_this(double k, double st, double fin, double end_st, double end_fin) {

  double a = end_fin - end_st;
  a /= fin;
  a *= k;
  a += end_st;
  return a;
}

void mousePressed() {

  if (mouseButton == LEFT) {
    zoom();
    cnt ++;
  }
}

void show_mandelbrot() {
  loadPixels();

  for (int i = 0; i < height; i ++) {
    for (int j = 0; j < width; j ++) {
      
      int index = i * width + j;

      double cur_x = map_this(j, 0, width - 1, x_l, x_r);
      double cur_y = map_this(i, 0, height - 1, y_u, y_d);
      
      Complex_nr c = new Complex_nr(cur_x, cur_y);
      Complex_nr z = new Complex_nr(0, 0);
 
      int it;
      for (it = 0; it < max_iterations; it ++) {
        z.sq();
        z.add(c);
        if (z.modulo() > 4) {
          break;
        }
      }

      if (it == max_iterations) {
        pixels[index] = color(0);
        continue;
      }
      
      double hu = map_this(it, 0, max_iterations, 0, 255);
      hu += 127;
      hu %= 256;
      pixels[index] = color((int)hu, 255, 255);
      
    }
  }
  updatePixels();
}



void setup() {
  colorMode(HSB);
  size(1280, 720);
  background(0);
}

void draw() {
  show_mandelbrot();
}