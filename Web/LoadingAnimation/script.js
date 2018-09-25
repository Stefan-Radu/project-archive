let canvas = document.getElementById ('Canvas');
let ctx = canvas.getContext ('2d');

//======================================================================

function DrawBackground () {
  ctx.fillStyle = 'rgba(255, 255, 255, 0.27';
  ctx.fillRect (0, 0, canvas.width, canvas.height);
}

//======================================================================

let colors = [
  [72, 133, 237],
  [219, 50, 54],
  [244, 194, 13],
  [72, 133, 237],
  [60, 186, 84],
  [219, 50, 54]
];

function RGBstring (rgb1, rgb2, perc) {

  let r = rgb1[0] + perc * (rgb2[0] - rgb1[0]);
  let g = rgb1[1] + perc * (rgb2[1] - rgb1[1]);
  let b = rgb1[2] + perc * (rgb2[2] - rgb1[2]);

  return 'rgb(' + r + ',' + g + ',' + b + ')';
}

let idx = 1;
let perc = 0;
let COLOR_STEP = 0.01;

function CycleColors () {

  if (perc == 1) {
    perc = 0;
    idx = (idx + 1) % (colors.length);
  }
  else {
    perc = Math.min (perc + COLOR_STEP, 1);
  }
}

//======================================================================

const BASE_SPEED = 0.1;
const ACC = 0.007;
const MIN_DIST = 0.1;
const MAX_LEN = Math.PI;
const RADIUS = 100;
const PI2 = Math.PI * 2;
const STEP = 0.05;
const ERR = 5;

let a = 0;
let b = 0.1;
let speedA = BASE_SPEED;
let speedB = BASE_SPEED;
let aFast = false;

function Update () {
  
<<<<<<< HEAD
  // canvas.width = window.innerWidth;
  // canvas.height = window.innerHeight;

=======
>>>>>>> 3c0a652febcde8d2ca2e2ad61a2b3a06a66cf591
  CycleColors ();
  DrawBackground ();

  ctx.beginPath ();
  ctx.lineWidth = 7;

  for (let i = a; i <= b; i += STEP) {
    ctx.moveTo (canvas.width / 2 + Math.cos (i - STEP) * RADIUS, canvas.height / 2 + Math.sin (i - STEP) * RADIUS);
    ctx.lineTo (canvas.width / 2 + Math.cos (i) * RADIUS, canvas.height / 2 + Math.sin (i) * RADIUS);
  }

  ctx.strokeStyle = RGBstring (colors[idx == 0 ? colors.length - 1 : idx - 1], colors[idx], perc);
  ctx.stroke ();
  
  ctx.beginPath ();

  let k = b;
  ctx.arc (canvas.width / 2 + Math.cos (k) * RADIUS, canvas.height / 2 + Math.sin (k) * RADIUS, 3.5, 0, PI2);
  k -= STEP / 2;
  ctx.arc (canvas.width / 2 + Math.cos (k) * RADIUS, canvas.height / 2 + Math.sin (k) * RADIUS, 3.5, 0, PI2);
  k -= STEP / 2;
  ctx.arc (canvas.width / 2 + Math.cos (k) * RADIUS, canvas.height / 2 + Math.sin (k) * RADIUS, 3.5, 0, PI2);

  ctx.fillStyle = RGBstring (colors[idx == 0 ? colors.length - 1 : idx - 1], colors[idx], perc);
  ctx.fill ();

  if (aFast) {
    speedA += ACC;
    speedB = Math.max (BASE_SPEED, speedB - ACC);
  }
  else {
    speedB += ACC;
    speedA = Math.max (BASE_SPEED, speedA - ACC);
  }

  a += speedA;
  b += speedB;

  if (b - a > 1.5 * Math.PI) {

    aFast = true;
    speedB = BASE_SPEED + ERR * ACC;
  }
  else if (b - a < 0.1) {

    a = b - 0.1;
    aFast = false;
    speedA = BASE_SPEED + ERR * ACC;
  }

  if (a > 30 * Math.PI && b > 30 * Math.PI) {

    a -= 20 * Math.PI;
    b -= 20 * Math.PI;
  }
}

function ResizeCanvas () {
  canvas.width = window.innerWidth;
  canvas.height = window.innerHeight;
}

window.onload = function () {

  canvas.width = window.innerWidth;
  canvas.height = window.innerHeight;
  
  ctx.fillStyle = '#000000';
  ctx.fillRect (0, 0, canvas.width, canvas.height);

  window.addEventListener ('resize', ResizeCanvas);

  setInterval (Update, 1000 / 30);
};
