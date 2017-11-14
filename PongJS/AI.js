function Computer() {
    this.paddle = new Paddle(10, 200, 10, 40);
    this.net = new NeuralNet(5, 3, 3, 1, [-400.511, 59.5233, 52.3747, 222.184, 425.817, -117.612, 90.8607, 4.5963, -8.38821, 341.047, -189.923, 27.6449, -227.436, -8.70612, 114.281, 121.578, -47.2572, 103.279, -57.3863, 13.3613, 81.227, -56.3332, -18.3833, 19.8708, 39.2165, 34.8184, -266.833, -451.953, 3.7511, 345.676, -21.4557, -43.6315, 320.206, 104.468, -7.2336, 5.19102] );
  
}

Computer.prototype.render = function() {
    this.paddle.render();
};

Computer.prototype.update = function(ball) {
    var result = (this.net.evaluate([math.abs((ball.x - 2.5) - (this.paddle.x + 5.0))/ 640.0,
                                    (ball.y - 2.5) / 480.0,
                                    -ball.x_speed / 640.0,
                                    ball.y_speed / 480.0,
                                    (this.paddle.y + 20.0) / 480.0])).get([0]);
    if(result < 0.0)
    {
        this.paddle.move(0, -8);
    }
    else
    {
        this.paddle.move(0, 8);
    }
};
