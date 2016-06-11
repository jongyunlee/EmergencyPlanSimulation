attribute vec4 vPosition;
attribute vec3 vNormal;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
    gl_Position = Projection * View * Model * (vPosition);
}