var animate = window.requestAnimationFrame ||
  window.webkitRequestAnimationFrame ||
  window.mozRequestAnimationFrame ||
  function(callback) { window.setTimeout(callback, 1000/60) };

var canvas = document.createElement('canvas');
var height = 482;
var width = 640;
canvas.width = width;
canvas.height = height;
canvas.style = "margin-left:auto; margin-right:auto";
var context = canvas.getContext('2d');

window.onload = function() {
  var div = document.getElementById("PongCanvas");
  div.appendChild(canvas);
  animate(step);
};

var step = function() {
  update();
  render();
  animate(step);
};

var keysDown = {};

window.addEventListener("keydown", function(event) {
  keysDown[event.keyCode] = true;
});

window.addEventListener("keyup", function(event) {
  delete keysDown[event.keyCode];
});

var update = function() {
  var point = ball.update(computer.paddle, player.paddle);
  if( point)
  {
    computer = new Computer();
  }
  player.update();
  computer.update(ball);
};

var render = function() {
  context.fillStyle = "#FFFFFF";
  context.fillRect(0, 0, width, height);
  player.render();
  computer.render();
  ball.render();
};

function Paddle(x, y, width, height) {
  this.x = x;
  this.y = y;
  this.width = width;
  this.height = height;
  this.x_speed = 0;
  this.y_speed = 0;
}

Paddle.prototype.render = function() {
  context.fillStyle = "#000000";
  context.fillRect(this.x, this.y, this.width, this.height);
};

Paddle.prototype.move = function(x, y) {
  this.x += x;
  this.y += y;
  this.x_speed = x;
  this.y_speed = y;
  if(this.y < 1) { // all the way to the left
    this.y = 1;
    this.y_speed = 0;
  } else if (this.y + this.height > 481) { // Bottom
    this.y = 481 - this.height;
    this.y_speed = 0;
  }
};

function Ball(x, y) {
  this.x = x;
  this.y = y;
  this.x_speed = 5;
  this.y_speed = 0;
  this.radius = 5;
}

Ball.prototype.render = function() {
  context.beginPath();
  context.arc(this.x, this.y, this.radius, 2 * Math.PI, false);
  context.fillStyle = "#000000";
  context.fill();
};

Ball.prototype.update = function(paddle1, paddle2) {
  this.x += this.x_speed;
  this.y += this.y_speed;
  var top_x = this.x - 5;
  var top_y = this.y - 5;
  var bottom_x = this.x + 5;
  var bottom_y = this.y + 5;
  if(this.y - 5 < 1) { // hitting the top wall
    this.y = 6;
    this.y_speed = -this.y_speed;
  } else if(this.y + 5 > 481) { // hitting the bottom wall
    this.y = 476;
    this.y_speed = -this.y_speed;
  }

  if(this.x < 0 || this.x > 640) { // a point was scored
    this.x_speed = 5;
    this.y_speed = 0;
    this.x = 320;
    this.y = 241;
    return true; 
  }

  if(top_x < 320) {
    if(top_x < (paddle1.x + paddle1.width) && bottom_x > paddle1.x && top_y < (paddle1.y + paddle1.height) && bottom_y > paddle1.y) {
      // hit the player's paddle
      var relY = this.y - (paddle1.y + 20.0);
      this.y_speed =  .5 * relY;
      this.x_speed = 5;
      this.x += this.x_speed;
    }
  } else {
    if(top_x < (paddle2.x + paddle2.width) && bottom_x > paddle2.x && top_y < (paddle2.y + paddle2.height) && bottom_y > paddle2.y) {
      // hit the computer's paddle
      var relY = this.y - (paddle2.y + 20.0);
      this.y_speed =  .5 * relY;
      this.x_speed = -5;
      this.x += this.x_speed;
    }
  }
  return false;
};

function Player() {
   this.paddle = new Paddle(620, 221, 10, 40);
}

Player.prototype.update = function() {
  this.paddle.move(0, 0);
  for(var key in keysDown) {
    var value = Number(key);
    if(value == 38) { // left arrow
      this.paddle.move(0, -8);
    } else if (value == 40) { // right arrow
      this.paddle.move(0, 8);
    }
  }
};



Player.prototype.render = function() {
  this.paddle.render();
};



var player = new Player();
var ball = new Ball(320, 241);
var computer = new Computer();



