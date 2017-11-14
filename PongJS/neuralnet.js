function NeuralNet(inputs, n, l, outputs, parameters) 
{
    l += 1 //output layer
    this.network = [];
    this.nodes = n;
    this.layers = l;
    this.network.push(math.matrix(math.zeros(inputs, this.nodes)));
    for(i = 0; i < l-2; i++)
    {
        this.network.push(math.matrix(math.zeros(this.nodes, this.nodes)));
    }
    this.network.push(math.matrix(math.zeros(this.nodes, outputs)));
    var count = 0;
    for(i = 0; i < l; i++)
    {
        var shape = math.size(this.network[i]);
        var temp = []
        for(j = 0; j < shape.get([0]); j++)
        {
            var temprow = []
            for(k = 0; k < shape.get([1]); k++)
            {
                temprow.push(parameters[count]);
                count++;
            }
            temp.push(temprow);
        }
        this.network[i] = temp;
    }
}

NeuralNet.prototype.evaluate = function(input)
{
    var result = math.matrix(input);
    //console.log(result);    

    for(i = 0; i < this.network.length; i++)
    {
        result = math.multiply(result, this.network[i]);
        //console.log(result); 

        result = math.tanh(result);
        //console.log(result); 


    }  
    return result;
}


