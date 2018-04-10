
var WIDTH =  window.innerWidth; 
var HEIGHT =  window.innerHeight; 
var symbolSize = 25;
var streamNr = Math.floor(WIDTH / symbolSize - 2);
var on = false;

function Color(r, g, b) {
  this.r = r;
  this.g = g;
  this.b = b;
}

function Symbol(x, y, speed, color) {
  this.x = x;
  this.y = y;
  this.speed = speed;
  this.timeToSwith = round(random(60, 120));
  this.color = color;

  this.setToRandom = function() {
    this.value = String.fromCharCode(0x30A0 + round(random(0, 95)));
  };

  this.update = function() {
    if (frameCount % this.timeToSwith === 0) {
      this.setToRandom();
    }
    
    this.y > HEIGHT ? this.y = 1 - symbolSize : this.y += this.speed;
  };

  this.display = function () {
    fill(this.color.r, this.color.g, this.color.b);
    text(this.value, this.x, this.y);
  };
}

function Stream(x) {
  this.size = round(random(10, 35));
  this.symbols = new Array(this.size + 1);
  this.x = x;
  this.y = random(- 500, - symbolSize);
  this.speed = random(2, 5);

  this.init = function() {
    for (var i = 1; i <= this.size; i ++) {
      var color;
      if (i == 1) {
        var chance = round(random(0, 2));
        if (chance === 0) 
          color = new Color(160, 255, 160);
        else 
          color = new Color(20, 200, 80);
      }
      else { 
        color = new Color(20, 200, 80);
      }

      this.symbols[i] = new Symbol(this.x, this.y, this.speed, color);
      this.symbols[i].setToRandom();
      this.y -= symbolSize;
    }
  };

  this.display = function() {
    for (var i = 1; i <= this.size; i ++) {
      this.symbols[i].display();
    }
  };

  this.update = function() {
    for (var i = 1; i <= this.size; i ++) {
      this.symbols[i].update();
    }
  };
}

function setup() {

  createCanvas(WIDTH, HEIGHT);
  background(0);
  frameRate(60);
  textSize(symbolSize);
  
  stream = new Array(streamNr + 1);
  for (var i = 0; i <= streamNr; i ++) {
    stream[i] = new Stream((i + 1) * symbolSize);
    stream[i].init();
  }
}

function run() {
  textSize(symbolSize);
  background(0, 100);
  for (var i = 0; i <= streamNr; i ++) {
    stream[i].update();
    stream[i].display();
  }
}

function start() {
  fill (255);
  textSize(60);
  textAlign(CENTER);
  text("Press ENTER to start", WIDTH / 2 , HEIGHT / 2);
}

function draw() {
  on ? run() : start();

  if (isKeyPressed) {
    if (keyCode == RETURN) {
      on = true;
    }
  }
}
