

function Sphere(segmentX, segmentY) {

    this.segmentX = segmentX;
    this.segmentY = segmentY;
    this.vNum;
    
    this.vertices = [];
    this.normals = [];
    this.texture = false;

    this.pushStack = function (stack, x, y, z) {
        stack.push(x);
        stack.push(y);
        stack.push(z);
    
    }
  
    this.initial = function (segmentX, segmentY) {
        var PI = 3.1415926;
        var R = 0.5;
        var u;
        var v;
        var xunit = (2.0 * PI)/segmentX;
        var yunit = PI/segmentY;
        var beta = PI/(-2.0);
        var index = 0;
    
        this.vNum = segmentY * segmentX * 6;
 
        for (h = 0; h < segmentY; h++) {
            var alpha = 0.0;
            var y = R * Math.sin(beta);
            var y_above = R * Math.sin(beta + yunit);
            for(w = 0; w < segmentX; w++) {
              
                var x = R * Math.cos(beta) * Math.cos(alpha);
                var x_above = R * Math.cos(beta + yunit) * Math.cos(alpha);
                var x_left = R * Math.cos(beta) * Math.cos(alpha + xunit);
                var x_diagonal = R * Math.cos(beta + yunit) * Math.cos(alpha + xunit);
                var z = R * Math.cos(beta) * Math.sin(alpha);
                var z_above = R * Math.cos(beta + yunit) * Math.sin(alpha);
                var z_left = R * Math.cos(beta) * Math.sin(alpha + xunit);
                var z_diagonal = R * Math.cos(beta + yunit) * Math.sin(alpha + xunit);
                
                //current
                this.pushStack(this.vertices, x, y, z);
	            //above point
                this.pushStack(this.vertices, x_above, y_above, z_above);
	            //diagonal point
                this.pushStack(this.vertices, x_diagonal, y_above, z_diagonal);
                //current
                this.pushStack(this.vertices, x, y, z);
                //diagonal point
                this.pushStack(this.vertices, x_diagonal, y_above, z_diagonal);
	            //left point
                this.pushStack(this.vertices, x_left, y, z_left);               
                   
                alpha += xunit;
            }
            beta += yunit;
        } 
    }
    this.initial(this.segmentX, this.segmentY);

}
