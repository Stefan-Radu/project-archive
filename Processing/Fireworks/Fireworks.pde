ArrayList < Firework > fireworks;
int type;
boolean auto;
float bright = 0;
String s;

void setup() {
  size(1280, 720);
  colorMode(HSB);
  background(0);
  type = 1;
  auto = true;
  s = "";
  fireworks = new ArrayList < Firework > ();
}

void mousePressed() {
  fireworks.add(new Firework(type, auto));
}

void keyPressed() {
  switch (key) {
    case 'a': {
      bright = 255;
      auto = !auto;
      if (auto) {
        s = "Auto";
      }
      else {
        s = "Manual";
      }
      break;
    }
    case 'h': {
      bright = 255;
      type = 2;
      s = "Hearts";
      break;
    }
    case 'c': {
      bright = 255;
      type = 1;
      s = "Clasic";
      break;
    }
  }
}

void draw() {
  noStroke();
  fill(0, 75);
  rect(0, 0, width, height);
  
  if (auto) { 
    float chance = random (100);
    if (chance <= 1.5) {
      fireworks.add(new Firework(type, auto));
    } 
  }

  for (Firework f : fireworks) {
    f.update();
    f.show();
  }

  for (int i = 0; i < fireworks.size(); i ++) {
    Firework f = fireworks.get(i);

    if (f.has_faded) {
      fireworks.remove(i);
    }
  }

  if (bright >= 0) {
    fill(255, 0, bright);
    textSize(16);
    text(s, 10, 25);
    bright -= 3;
  }
}