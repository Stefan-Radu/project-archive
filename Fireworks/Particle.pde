class Particle {

  void type1_init() {
    PVector rand_vel = PVector.random2D();
    rand_vel.mult(random(5));
    this.velocity = rand_vel; 
  }

  void type2_init() {
    this.velocity = new PVector(random(-1, 1), random(-5, 0));
    if (this.velocity.x <=0) {
      this.wind = new PVector(random(-0.1, 0), 0);
    }
    else {
      this.wind.set(random(0, 0.1), 0);
    }
  }
  
  Particle (float x, float y, int hiu, boolean has_exploded, int type, boolean auto) {
    this.type = type;
    this.wind = new PVector(0, 0);
    if (!has_exploded) {
      if (!auto) {
        this.position = new PVector(mouseX, height + 6);
      }
      else {
        this.position = new PVector(random(150, width - 150), height + 6);
      }

      this.velocity = new PVector(x, y);
    }
    else {
      this.position = new PVector(x, y);
      if (type == 1) type1_init();
      else if (type == 2) type2_init();
    }
    
    this.acceleration = new PVector(0, 0);
    this.has_exploded = has_exploded;
    this.bright = 255;
    this.decr = 0.50;
    this.hiu = hiu;
    this.fatness = 6;
    this.ch = false;
    this.init = new PVector(x, y);
    this.init_y_vel = this.velocity.y;
  }


  PVector position;
  PVector velocity;
  PVector acceleration;
  boolean has_exploded;
  float bright;
  float decr;
  int hiu;
  float fatness;
  int type;
  PVector wind;
  boolean ch;
  PVector init;
  float init_y_vel;


  boolean is_done() {
    if (this.has_exploded) {
      if (this.bright <= 0) {
        return true;
      }

      return false;
    }

    if (this.velocity.y >= 0) {
      return true;
    }

    return false;
  }

  void apply_force(PVector gravity) {
    this.acceleration.add(gravity);
    if (this.has_exploded) {
      this.acceleration.add(wind);
    }
  }

  void update() {
    this.velocity.add(this.acceleration);
    this.position.add(this.velocity);
    this.acceleration.mult(0);
    
    if (has_exploded) {
      this.bright -= this.decr;
      this.decr += 0.1;
      this.fatness -= 0.07;

      if (this.type == 2) {
        if (!ch) {
          if (this.position.y >= this.init.y) {
            this.wind.mult(-1);
            this.ch = true;
          }
        }
        else if (this.wind.x != 0) {
          if (abs(this.position.x - this.init.x) < 1) {
            this.wind.x = 0;
            this.velocity.x = 0;
          }
        }
      }
    }
  }

  void show() {
    if (has_exploded) {
      stroke(this.hiu, 255, bright);
    }
    else {
      stroke(this.hiu, 255, 255);
    }
    strokeWeight(this.fatness);
    point(this.position.x, this.position.y);
  }
}