Star star[] = new Star[1000];
boolean running = false;

void init() {
  for (int i = 0 ; i < star.length; i ++) {
    star[i] = new Star();
  }
}

void show() {
  background(27);
  translate(width / 2, height / 2);
  for (Star x : star) {
    x.update();
    x.show();
  }
}

void setup() {
  size(700, 700);
  for (int i = 0; i < star.length; i ++) {
    star[i] = new Star();
  }
}

void draw() { 
  show();
}