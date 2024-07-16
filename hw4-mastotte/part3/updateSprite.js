const updateSpriteWGSL = `
    struct Particle {
        pos : vec2<f32>
    };

    struct Particles {
        particles : array<Particle>
    };

    @binding(0) @group(0) var<storage, read_write> particlesA : Particles;
    @binding(1) @group(0) var<storage, read_write> particlesB : Particles;

    @compute @workgroup_size(64)
    fn main(@builtin(global_invocation_id) GlobalInvocationID : vec3<u32>) {
        var index : u32 = GlobalInvocationID.x;

        // Get position of current particle
        var vPos1 = particlesA.particles[index].pos;
        
        // ADD YOUR COMPUTATION HERE
        // --------------------------------
        var num_particles: i32 = i32(arrayLength(&particlesA.particles));
        var min_dist: f32 = 9999999.9;
        var y_move: f32 = 0.0;
        var x_move: f32 = 0.0;

        // CHANGE FROM 1024 LATER

        for (var j = 0; j < num_particles; j++){
            // find index of nearest particle, over 3 away
            var vPos2 = particlesA.particles[j].pos;
            var dist = sqrt((pow((vPos1.x - vPos2.x),2) + pow((vPos1.y - vPos2.y),2)));
            if (dist < min_dist && dist > 0.003){
                min_dist = dist;

                if (vPos2.y > vPos1.y){
                    y_move = 0.001;
                }else if(vPos2.y < vPos1.y){
                    y_move = -0.001;
                }else{
                    y_move = 0.0;
                }

                if (vPos2.x > vPos1.x){
                    x_move = 0.001;
                }else if(vPos2.x < vPos1.x){
                    x_move = -0.001;
                }else{
                    x_move = 0.0;
                }
            }
        }
    
        // compute move towards neares particle
        vPos1.x = vPos1.x + x_move;
        vPos1.y = vPos1.y + y_move;
        particlesB.particles[index].pos = vPos1;

    }
`;

export default updateSpriteWGSL;