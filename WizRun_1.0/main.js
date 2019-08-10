let canvas = document.getElementById ('Canvas');
let ctx = canvas.getContext ('2d');

const PS = 3;
const GRAVITY = 0.01
canvas.width = window.innerWidth;
canvas.height = window.innerHeight;

class Character {

  constructor (pixels, x, y) {

    this.pixels = pixels; 
    this.pos = {x: x, y: y};
  }

  Draw () {

    let x, y;
    for (let i = 0; i < this.pixels.length; ++ i) {

      x = this.pos.x + this.pixels[i][0] * PS;
      y = this.pos.y + this.pixels[i][1] * PS;

      ctx.fillStyle = colors[this.pixels[i][2]];
      ctx.fillRect (x, y, PS, PS);
    }
  }
}

let wiz = new Character (wizzard, 100, 100);

function Main (timestamp) {

  ctx.fillStyle = '#ffffff';
  ctx.fillRect (0, 0, canvas.width, canvas.height);

  wiz.Draw ();

  console.log (timestamp);
  requestAnimationFrame (Main);
}

requestAnimationFrame (Main);


