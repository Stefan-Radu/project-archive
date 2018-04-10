
let canv = document.getElementById ('Canvas');
let ctx = canv.getContext ('2d');

let xSpeed = Math.PI / 15;
let ySpeed = Math.PI / 90;
let x = xSpeed;
let y = ySpeed;

function DrawBackground () {

  ctx.fillStyle = '1b1b1b';
  ctx.fillRect (0, 0, canv.width, canv.height);
}

function Arc (x, y, r, start, fin, color) {
  
  ctx.lineWidth = 15;
  ctx.strokeStyle = color;
  ctx.beginPath ();
  ctx.arc (x, y, r, start, fin);
  ctx.stroke ();
}

function Do () {
  
  DrawBackground ();

  Arc (canv.width / 2, canv.height / 2, 150, Math.max (x, y), Math.min (x, y), '#FFFFFF');

  x += xSpeed; 
  y += ySpeed;
  
  if (x >= Math.PI * 2) {
    x -= Math.PI * 2;
  }

  if (y >= Math.PI * 2) {
    y -= Math.PI * 2;
  }
}

window.onload = function () {
  
  // let start = false;
  
  DrawBackground ();
  // document.addEventListener ('keypress', function () { start = true; });

  // if (start) {
    setInterval (Do, 1000 / 30);
  // }
};
