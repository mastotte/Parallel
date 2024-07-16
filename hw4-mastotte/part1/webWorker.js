// Perform computation when receive data from main.js
self.onmessage = function(event) {
    
    // Unpack data received from main.js
    var NUMPARTICLES = event.data.NUMPARTICLES;
    var particlesComputeData = new Float32Array(event.data.particlesComputeBuffer);
    var particlesRenderData = new Float32Array(event.data.particlesRenderBuffer);

    for (let i = 0; i < NUMPARTICLES; i++) {
        let min_dist = 99999999
        let y_move = 0
        let x_move = 0
        /* ADD YOUR COMPUTATION HERE
        */
       for (let j = 0; j < NUMPARTICLES; j++){
            // find index of nearest particle, over 3 away
            let x1 = particlesComputeData[2 * i]
            let y1 = particlesComputeData[2 * i + 1]
            let x2 = particlesComputeData[2 * j]
            let y2 = particlesComputeData[2 * j + 1]
            let dist = Math.sqrt((Math.pow((x1 - x2),2) + Math.pow((y1 - y2),2)))
            if (dist < min_dist && dist > 3){
                min_dist = dist

                if (y2 > y1){
                    y_move = 1
                }else if(y2 < y1){
                    y_move = -1
                }else{
                    y_move = 0
                }

                if (x2 > x1){
                    x_move = 1
                }else if(x2 < x1){
                    x_move = -1
                }else{
                    x_move = 0
                }
            }
       }
        
        // compute move towards neares particle
        particlesRenderData[2 * i] = particlesComputeData[2 * i] + x_move
        particlesRenderData[2 * i + 1] = particlesComputeData[2 * i + 1] + y_move
    }
    
    // Send back new data back to main.js
    postMessage(null);
}