
let canvas = document.getElementById ('Game');
let ctx = canvas.getContext ('2d');

let score = 0;
const SIZE = 20;
const FRAME_RATE = 20;

function Rect (x, y, w, h, c) {
  ctx.fillStyle = c;
  ctx.fillRect (x, y, w, h);
}

function DrawBackground () {
  Rect (0, 0, canvas.width, canvas.height, '#1b1b1b');
}

class Food {

  constructor () {

    this.x = ((Math.round (Math.random () * 10000)) % (canvas.width / SIZE)) * SIZE;
    this.y = ((Math.round (Math.random () * 10000)) % (canvas.height / SIZE)) * SIZE;
  }

  Update () {

    this.x = ((Math.round (Math.random () * 10000)) % (canvas.width / SIZE)) * SIZE;
    this.y = ((Math.round (Math.random () * 10000)) % (canvas.height / SIZE)) * SIZE;
  }

  Display () {

    Rect (this.x, this.y, SIZE, SIZE, 'red'); 
  }
}

class Snake {
  
  constructor (x, y, len, sz) {

    this.len = 1;
    this.tail = [];
    this.tail[0] = {x, y}; 
    this.sz = sz;
    this.dirX = 0;
    this.dirY = 0;
    this.curDir = 0;
    this.gotNewDir = false;
  }

  Grow () {
    ++ score;
    ++ this.len;
    console.log (this.len);
    this.tail.push ({x : 0, y : 0});
  }

  Update () {

    snake.gotNewDir = false;
    for (var i = this.len - 1; i >= 1; -- i) {
      this.tail[i].x = this.tail[i - 1].x;
      this.tail[i].y = this.tail[i - 1].y;
    }

    this.tail[0].x += this.dirX;
    this.tail[0].y += this.dirY;

    if (this.tail[0].x >= canvas.width) {
      this.tail[0].x = 0;
    }
    else if (this.tail[0].x <= -this.sz) {
      this.tail[0].x = canvas.width - this.sz;
    }
    
    if (this.tail[0].y >= canvas.height) {
      this.tail[0].y = 0;
    }
    else if (this.tail[0].y <= -this.sz) {
      this.tail[0].y = canvas.height - this.sz;
    }
  }

  Display () {

    for (var i = 0; i < this.tail.length; ++ i) {
      Rect (this.tail[i].x, this.tail[i].y, this.sz, this.sz, '#1b1b1b');
      Rect (this.tail[i].x + 1, this.tail[i].y + 1, this.sz - 2, this.sz - 2, 'white');
    }
  }
}

let food = new Food (SIZE);
let snake = new Snake (0, 0, 1, SIZE);

function IsOnFood (block) {
  return Math.abs (block.x - food.x) < 1 && Math.abs (block.y - food.y) < 1;
}

function RenderFrame () {

  DrawBackground ();
  if (IsOnFood (snake.tail[0])) {
  
    snake.Grow ();
    let ok = false;
    while (!ok) {

      ok = true;
      for (let i = 0; i < snake.len; ++ i) {
        if (IsOnFood (snake.tail[i])) {
          ok = false;
          break;
        }
      }
     
      if (!ok) {
        food.Update ();
      }
    }
  }
  else {

    let dead = false;
    for (let i = 1; i < snake.len; ++ i) {
      if (Math.abs (snake.tail[0].x - snake.tail[i].x) < 1 && 
        Math.abs (snake.tail[0].y - snake.tail[i].y) < 1) {
        dead = true;
        break;
      }
    }

    if (dead) {
      while (snake.len > 1) {
        -- snake.len;
        snake.tail.pop ();
      }

      score = 0;
    }
  }

  food.Display ();

  snake.Update ();
  snake.Display ();
  let tmp = document.getElementById ('Score');
  tmp.innerHTML = "Score: " + score;
}

function Click () {
  snake.Grow ();
}

function KeyPush (evt) {
  
  if (snake.gotNewDir) {
    return;
  }

  if (evt.keyCode == 37 && snake.curDir != 39) {
    snake.dirX = -SIZE;
    snake.dirY = 0;
    snake.curDir = 37;
    snake.gotNewDir = true;
  }
  else if (evt.keyCode == 38 && snake.curDir != 40) {
    snake.dirX = 0;
    snake.dirY = -SIZE;
    snake.curDir = 38;
    snake.gotNewDir = true;
  }
  else if (evt.keyCode == 39 && snake.curDir != 37) {
    snake.dirX = SIZE;
    snake.dirY = 0;
    snake.curDir = 39;
    snake.gotNewDir = true;
  }
  else if (evt.keyCode == 40 && snake.curDir != 38) {
    snake.dirX = 0;
    snake.dirY = SIZE;
    snake.curDir = 40;
    snake.gotNewDir = true;
  }
}

window.onload = function () {
 
  DrawBackground ();
  document.addEventListener ('keydown', KeyPush);
  document.addEventListener ('click', Click);
  setInterval (RenderFrame, 1000 / FRAME_RATE);
};
