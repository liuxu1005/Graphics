
function Cube(segmentX, segmentY) {

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
        this.vNum = 24* segmentX * segmentY + 12 * segmentX * segmentX;
        var yunit = 1.0/segmentY;
        var zunit = 1.0/segmentX;
        var xunit = 1.0/segmentX;
        var y_coor = -0.5;
        var y_next = y_coor + yunit;
 
        for (y = 0; y < segmentY; y++) {
            var tmp = -0.5;
            for (x = 0; x < segmentX; x++) {
                var x_next = tmp + xunit;
                this.pushStack(this.vertices, tmp, y_coor, 0.5); 
                //this.pushStack(this.normals, 0.0, 0.0, 1.0);
                
                this.pushStack(this.vertices, x_next, y_coor, 0.5); 
                //this.pushStack(this.normals, 0.0, 0.0, 1.0);
                
                this.pushStack(this.vertices, x_next, y_next, 0.5); 
                //this.pushStack(this.normals, 0.0, 0.0, 1.0);
                
                this.pushStack(this.vertices, tmp, y_coor, 0.5); 
                //this.pushStack(this.normals, 0.0, 0.0, 1.0);
                
                this.pushStack(this.vertices, x_next, y_next, 0.5); 
                //this.pushStack(this.normals, 0.0, 0.0, 1.0);
                
                this.pushStack(this.vertices, tmp, y_next, 0.5); 
                //this.pushStack(this.normals, 0.0, 0.0, 1.0);
                tmp += xunit;
            }
            tmp = 0.5;
            for (z = 0; z < segmentX; z++) {
            
                var z_next = tmp - zunit;
                
                this.pushStack(this.vertices, 0.5 , y_coor, tmp); 
                //this.pushStack(this.normals, 1.0, 0.0, 0.0);
                
                this.pushStack(this.vertices, 0.5, y_coor, z_next); 
                //this.pushStack(this.normals, 1.0, 0.0, 0.0);
                
                this.pushStack(this.vertices, 0.5, y_next, z_next); 
                //this.pushStack(this.normals, 1.0, 0.0, 0.0);
                
                this.pushStack(this.vertices, 0.5 , y_coor, tmp); 
                //this.pushStack(this.normals, 1.0, 0.0, 0.0);
                
                this.pushStack(this.vertices, 0.5, y_next, z_next); 
                //this.pushStack(this.normals, 1.0, 0.0, 0.0);
                
                this.pushStack(this.vertices, 0.5, y_next, tmp); 
                //this.pushStack(this.normals, 1.0, 0.0, 0.0);
                tmp -= zunit;
            }
            tmp = 0.5;
            for (x = 0; x < segmentX; x++) {
                var x_next = tmp - xunit;
                this.pushStack(this.vertices, tmp, y_coor, -0.5); 
                //this.pushStack(this.normals, 0.0, 0.0, -1.0);
                
                this.pushStack(this.vertices, x_next, y_coor, -0.5); 
                //this.pushStack(this.normals, 0.0, 0.0, -1.0);
                
                this.pushStack(this.vertices, x_next, y_next, -0.5); 
                //this.pushStack(this.normals, 0.0, 0.0, -1.0);
                
                this.pushStack(this.vertices, tmp, y_coor, -0.5); 
                //this.pushStack(this.normals, 0.0, 0.0, -1.0);
                
                this.pushStack(this.vertices, x_next, y_next, -0.5); 
                //this.pushStack(this.normals, 0.0, 0.0, -1.0);
                
                this.pushStack(this.vertices, tmp, y_next, -0.5); 
                //this.pushStack(this.normals, 0.0, 0.0, -1.0);
                tmp -= xunit;
            }
            tmp = -0.5;
            for (z = 0; z < segmentX; z++) {
            
                var z_next = tmp + zunit;
                
                this.pushStack(this.vertices, -0.5 , y_coor, tmp); 
                //this.pushStack(this.normals, -1.0, 0.0, 0.0);
                
                this.pushStack(this.vertices, -0.5, y_coor, z_next); 
                //this.pushStack(this.normals, -1.0, 0.0, 0.0);
                
                this.pushStack(this.vertices, -0.5, y_next, z_next); 
                //this.pushStack(this.normals, -1.0, 0.0, 0.0);
                
                this.pushStack(this.vertices, -0.5 , y_coor, tmp); 
                //this.pushStack(this.normals, -1.0, 0.0, 0.0);
                
                this.pushStack(this.vertices, -0.5, y_next, z_next); 
                //this.pushStack(this.normals, -1.0, 0.0, 0.0);
                
                this.pushStack(this.vertices, -0.5, y_next, tmp); 
                //this.pushStack(this.normals, -1.0, 0.0, 0.0);
                tmp += zunit;
            }
            y_coor += yunit;
            y_next = y_coor + yunit;
        }
        
        
        //calculate vertices on top
       
        var x_coor;
        var z_coor = 0.5;
        for (z = 0; z < segmentX; z++) {
            var z_next = z_coor - zunit;
            x_coor = -0.5;
            for (x = 0; x < segmentX; x++) {
                var x_next = x_coor + xunit;
                
                this.pushStack(this.vertices, x_coor, 0.5, z_coor); 
                //this.pushStack(this.normals, 0.0, 1.0, 0.0);
                
                this.pushStack(this.vertices, x_next, 0.5, z_coor); 
                //this.pushStack(this.normals, 0.0, 1.0, 0.0);
                
                this.pushStack(this.vertices, x_next, 0.5, z_next); 
                //this.pushStack(this.normals, 0.0, 1.0, 0.0);
                
                this.pushStack(this.vertices, x_coor, 0.5, z_coor); 
                //this.pushStack(this.normals, 0.0, 1.0, 0.0);
                
                this.pushStack(this.vertices, x_next, 0.5, z_next); 
                //this.pushStack(this.normals, 0.0, 1.0, 0.0);
                
                this.pushStack(this.vertices, x_coor, 0.5, z_next); 
                //this.pushStack(this.normals, 0.0, 1.0, 0.0);
                
                x_coor += xunit;
            }
            z_coor -= zunit;
 
        }
        //calculate vertices on bottom
         
        
        x_coor;
        z_coor = -0.5;
        for (z = 0; z < segmentX; z++) {
            var z_next = z_coor + zunit;
            x_coor = -0.5;
            for (x = 0; x < segmentX; x++) {
                var x_next = x_coor + xunit;
                
                this.pushStack(this.vertices, x_coor, -0.5, z_coor); 
                //this.pushStack(this.normals, 0.0, -1.0, 0.0);
                
                this.pushStack(this.vertices, x_next, -0.5, z_coor); 
                //this.pushStack(this.normals, 0.0, -1.0, 0.0);
                
                this.pushStack(this.vertices, x_next, -0.5, z_next); 
                //this.pushStack(this.normals, 0.0, -1.0, 0.0);
                
                this.pushStack(this.vertices, x_coor, -0.5, z_coor); 
                //this.pushStack(this.normals, 0.0, -1.0, 0.0);
                
                this.pushStack(this.vertices, x_next, -0.5, z_next); 
                //this.pushStack(this.normals, 0.0, -1.0, 0.0);
                
                this.pushStack(this.vertices, x_coor, -0.5, z_next); 
                //this.pushStack(this.normals, 0.0, -1.0, 0.0);
                
                x_coor += xunit;
            }
            z_coor += zunit;
 
        }
    }
    this.initial(segmentX, segmentY);

}
