let canvas = document.getElementById ('Canvas');
let ctx = canvas.getContext ('2d');

function ResizeCanvas () {

  canvas.width = window.innerWidth;
  canvas.height = window.innerHeight;

  ctx.fillStyle = 'rgba(0, 0, 0, 0.02)';
  ctx.fillRect (0, 0, canvas.width, canvas.height);

  divSize = canvas.width / DIVISIONS_HORIZ;
  radius = 0.3 * divSize;
  margin = 0.2 * divSize;
  dot = 0.015 * canvas.width / DIVISIONS_HORIZ;
}

const INTERVAL = 1000 / 60;
const DIVISIONS_HORIZ = 12;
const PI2 = 2 * Math.PI;
const SPEED_SCALE = 0.02;


let divSize, radius, dot, margin;
let k = 0, speedHoriz = SPEED_SCALE * (Math.random () + 1), speedVert = SPEED_SCALE * (Math.random () + 1);

let angleVert = [];
let angleHoriz = [];

function Init () {

  for (let i = 1; i < 100; ++ i) {
    angleHoriz[i] = 0;
  }

  for (let i = 1; i < 100; ++ i) {
    angleVert[i] = 0;
  }
}

function Update () {

  for (let i = 1; i < DIVISIONS_HORIZ; ++ i) {
    angleHoriz[i] += speedHoriz * i;
    if (angleHoriz[i] >= PI2) {
      angleHoriz[i] -= PI2;
    }
  }

  for (let i = 1; i < Math.floor (canvas.height / divSize); ++ i) {
    angleVert[i] += speedVert * i;
    if (angleVert[i] >= PI2) {
      angleVert[i] -= PI2;
    }
  }
}

function Draw () {

  ctx.fillStyle = 'rgba(0, 0, 0, 0.02)';
  ctx.fillRect (0, 0, canvas.width, canvas.height);

  ctx.fillStyle = '#ffffff';
  for (let i = 1; i < DIVISIONS_HORIZ; ++ i) {
    ctx.beginPath ();
    ctx.arc (margin + divSize * i + radius * (Math.cos (angleHoriz[i]) + 1), margin + radius * (Math.sin (angleHoriz[i]) + 1), dot, 0, PI2);
    ctx.fill ();
  }

  for (let i = 1; i < Math.floor (canvas.height / divSize); ++ i) {
    ctx.beginPath ();
    ctx.arc (margin + radius * (Math.cos (angleVert[i]) + 1), margin + divSize * i + radius * (Math.sin (angleVert[i]) + 1), dot, 0, PI2);
    ctx.fill ();
  }

  for (let i = 1; i < Math.floor (canvas.height / divSize); ++ i) {
    for (let j = 1; j < DIVISIONS_HORIZ; ++ j) {

      ctx.beginPath ();
      ctx.arc (margin + divSize * j + radius * (Math.cos (angleHoriz[j]) + 1), margin + divSize * i + radius * (Math.sin (angleVert[i]) + 1), dot, 0, PI2);
      ctx.fill ();
    }
  }
}

function LissajousCurves () {

  Update ();
  Draw ();
}

window.onload = function () {

  canvas.width = window.innerWidth;
  canvas.height = window.innerHeight;

  ResizeCanvas ();

  ctx.fillStyle = 'rgb(0, 0, 0)';
  ctx.fillRect (0, 0, canvas.width, canvas.height);

  Init ();

  window.addEventListener ('resize', ResizeCanvas);

  setInterval (LissajousCurves, INTERVAL);
}
