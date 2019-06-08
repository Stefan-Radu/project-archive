class Firework {

  Firework(int type, boolean auto) {
    this.hiu = floor(random(255));
    this.rocket = new Particle(0, random(-15,  -10), this.hiu, false, type, auto);
    sparkles = new ArrayList < Particle > ();
    this.has_exploded = false;
    this.has_faded = false;
    gravity = new PVector(0, 0.17);
  }

  Particle rocket;
  ArrayList < Particle > sparkles;
  boolean has_exploded;
  boolean has_faded;
  PVector gravity;
  int hiu;

  void try_to_explode() {
    if (this.rocket.is_done()) {
      this.explode();
    }
  }

  void explode() {
    this.has_exploded = true;
    int nr_of_sparkles;
    if (type == 1) {
      nr_of_sparkles = floor(random(27, 500));
    }
    else {
      nr_of_sparkles = floor(random(100, 300));
    }

    for (int i = 0; i < nr_of_sparkles; i ++) {
      sparkles.add(new Particle(this.rocket.position.x,
       this.rocket.position.y, this.hiu, true, type, auto));
    }
  }

  void update() {
    if (!has_exploded) {
      this.rocket.apply_force(this.gravity);
      this.rocket.update();
      this.try_to_explode();
    }
    else {
      for (Particle p : sparkles) {
        p.apply_force(this.gravity);
        p.update();
        if (p.is_done()) {
          this.has_faded = true;
        }
      }
    }

    for (int i = sparkles.size() - 1; i >= 0; i --) {
      Particle p = sparkles.get(i);
      if (p.bright <= 0) {
        sparkles.remove(i);
      }
    }
  }

  void show() {
    if (!has_exploded) {
      this.rocket.show();
    }
    else {
      for (Particle p : sparkles) {
        p.show();
      }
    }
  }
}