// Perform computation when receive data from main.js
self.onmessage = function(event) {
    
    // Unpack data received from main.js
    var NUMPARTICLES = event.data.NUMPARTICLES;
    var particlesComputeData = new Float32Array(event.data.particlesComputeBuffer);
    var particlesRenderData = new Float32Array(event.data.particlesRenderBuffer);
    var NUMWORKERS = event.data.NUMWORKERS;
    var THREADID = event.data.THREADID;
    let min_dist = 9999999
    let y_move = 0
    let x_move = 0
    let x1 = 0
    let y1 = 0
    let x2 = 0
    let y2 = 0
    let dist = 0
    let clump_counter = 1
    for (let i = THREADID; i < NUMPARTICLES; i += NUMWORKERS) {
        /* ADD YOUR COMPUTATION HERE*/
        
        min_dist = 9999999
        y_move = 0
        x_move = 0
        clump_counter = 1
       for (let j = 0; j < NUMPARTICLES; j += clump_counter){
            // find index of nearest particle, over 3 away
            x1 = particlesComputeData[2 * i]
            y1 = particlesComputeData[2 * i + 1]
            x2 = particlesComputeData[2 * j]
            y2 = particlesComputeData[2 * j + 1]
            dist = Math.sqrt((Math.pow((x2 - x1),2) + Math.pow((y2 - y1),2)))
            if (dist < 3){
                clump_counter++;
            }
            if (dist > 3 && dist < min_dist - 3){
                min_dist = dist

                if (y2 > y1 +1){
                    y_move = 1
                }else if(y2 < y1 -1){
                    y_move = -1
                }else{
                    y_move = 0
                }

                if (x2 > x1 +1){
                    x_move = 1
                }else if(x2 < x1 -1){
                    x_move = -1
                }else{
                    x_move = 0
                }
            }
            if (dist > 3 && dist < 4){
                break
            }
        }
    
        // compute move towards neares particle
        particlesRenderData[2 * i] = particlesComputeData[2 * i] + x_move
        particlesRenderData[2 * i + 1] = particlesComputeData[2 * i + 1] + y_move
    }
    
    // Send back new data back to main.js
    postMessage(THREADID);
}