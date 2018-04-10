let canvas, ctx;
let FRAME_RATE = 30;

function Init () {

  canvas = document.getElementById ('Canvas');

  canvas.width = window.innerWidth;
  canvas.height = window.innerHeight;

  ctx = canvas.getContext ('2d');
}

class Particle {
  
 

}

function Draw () {

}

window.onload = function () {

  Init ();
  setInterval (Draw, 1000 / FRAME_RATE);
};
