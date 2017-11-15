function Computer() {
    this.paddle = new Paddle(10, 221, 10, 40);
    var parameters = [];
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "DE_Iteration.xml", false);
    xhttp.send();

    var random = Math.floor((Math.random() * 19));
    var xmlDoc = xhttp.responseXML;
    //TO DO:  Add Nodes and Layers to xml file
    var values =
    xmlDoc.getElementsByTagName("values")[random].childNodes[0].nodeValue.split("   ");
    for(i = 0; i < values.length - 1; i++)
    {
        parameters.push(Number(values[i]));
    }

    this.net = new NeuralNet(5, 3, 3, 1, parameters );
  
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
