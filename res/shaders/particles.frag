#version 400 core
in vec2 uv;
in vec4 particleColor;

out vec4 fragColor;

void main(){
    fragColor = vec4(1);
    if(length(uv) < 1.0) {
        fragColor = particleColor;
    } else {
        discard;
    }
}
