float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

float srand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453) * 2.0 - 1.0;
}

float rand(float seed){
    vec2 co = vec2(seed, seed + 100);
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

float srand(float seed){
    vec2 co = vec2(seed, seed + 100);
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453) * 2.0 - 1.0;
}
