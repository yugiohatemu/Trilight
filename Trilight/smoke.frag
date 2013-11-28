varying vec3 position;
uniform float time;
/*const vec2 light_position = float[](320,220);*/
/*const float density;
const float exposure;
const float decay;
const float weight; lets try gaussian blur*/
void main(){
    vec2 col = (noise2(position.xy) * 0.5) + 0.5;
    float val = (col.x+col.y ) / 2.0;
    gl_FragColor = gl_Color * vec4(val,val,val,1.0);
}