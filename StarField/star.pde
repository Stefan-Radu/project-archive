class Star {
  float x;
  float y;
  float z;
  float max_z;
  float speed;
  float prev_z;

  Star() {
    this.x = random(-width, width);
    this.y = random(-height, height);
    this.z = random(width, 3000);
    this.max_z = this.z;
  }

  void reset() {
    this.z = random(width, 3000);
    this.x = random(-width, width);
    this.y = random(-height, height);
    this.max_z = this.z;
    this.prev_z = this.z;
  }

  void update() {
    prev_z = this.z;
    this.speed = map (mouseX, 0, width, 0, 70);
    this.z -= this.speed;
    
    if (this.z <= 0) {
      this.reset();
    }
  }

  void show() {
    fill(255);
    noStroke();
    float xp = map(x / z, -1, 1, -width, width);
    float yp = map(y / z, -1, 1, -height, height);
    float pxp = map(x / prev_z, -1, 1, -height, height);
    float pyp = map(y / prev_z, -1, 1, -height, height);

    float radius = map(z, 0, max_z, 7, 0);
    ellipse(xp, yp, radius, radius);
    stroke(255);
    line(xp, yp, pxp, pyp);  
  }
};