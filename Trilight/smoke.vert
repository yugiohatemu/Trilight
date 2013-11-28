varying vec3 position;
void main(){
    position = gl_Vertex.xyz;
    gl_Position = ftransform();
    gl_FrontColor = gl_Color;
}