/* My WebGL camera object constructor */

function Camera() {

    this.eye = quat.fromValues(13.0, 13.0, 13.0, 1.0);
    this.focus = quat.fromValues(0.0, 0.0, 0.0, 1.0);
    this.up = vec4.fromValues(0.0, 1.0, 0.0, 0.0);
    
    this.fovy = 0.1;
    this.ratio = 1.0;
    this.near = 0.1;
    this.far = 100.0;
    
    this.pMatrix = mat4.create();
    this.mvMatrix = mat4.create();
   
    this.getPMatrix = function () {
        return mat4.perspective(this.pMatrix, this.fovy, this.ratio, 
                                               this.near, this.far);
    }
    this.getFocus = function() {
        return this.focus;
    }
    this.getFovy = function () {
        return this.fovy;
    }
   
    this.getMVMatrix = function () {
        return mat4.lookAt(this.mvMatrix, 
                           [this.eye[0], this.eye[1], this.eye[2]], 
                           [this.focus[0], this.focus[1], this.focus[2]], 
                                   [this.up[0], this.up[1], this.up[2]]);
    }
 
    this.getEye = function () {
        return this.eye;
    }
    this.getNear = function () {
        return this.near;
    }
    this.getFar = function () {
        return this.far;
    }
    this.getRatio = function () {
        return this.ratio;
    }
    
    this.setPerspective = function (fovy, ratio, near, far) {
        this.fovy = fovy;
        this.ratio = ratio;
        this.near = near;
        this.far = far;
       

    
    }
    
    this.setLookat = function (eye, focus, up) {
        this.eye = eye;
        this.focus = focus;
        this.up = up;
    
    }
    this.rotate = function (startX, startY, curX, curY) {
    
        var v1 = vec4.fromValues(curX - startX, curY - startY, 0.0, 0.0);   
        var iPMatrix = mat4.create();
        
        mat4.multiply(iPMatrix, camera.getPMatrix(), camera.getMVMatrix());
        mat4.invert(iPMatrix, iPMatrix);
 
        mat4.multiply(v1, iPMatrix, v1);
       
        var v2 = vec3. fromValues(this.eye[0] - this.focus[0], 
                                  this.eye[1] - this.focus[1], 
                                  this.eye[2] - this.focus[2]);

        var rad = Math.sqrt((startX - curX) * (startX - curX) 
                         + (startY - curY) * (startY - curY));
        var axis = vec3.fromValues(v1[1] * v2[2] - v2[1] * v1[2], 
                                       v1[2] * v2[0] - v2[2] * v1[0],
                                       v1[0] * v2[1] - v2[0] * v1[1]);  
  
     
        var tmp = mat4.create(); 
        mat4.fromRotation(tmp, rad, axis); 
        mat4.multiply(this.eye, tmp, this.eye); 
        mat4.multiply(this.up, tmp, this.up);  
    
    }
    
}



 
