attribute   vec4 vPosition;
attribute   vec3 vNormal;

uniform mat3 Compensate;
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform float Thickness;

void main()
{
    gl_Position = Projection * View * Model * (vPosition + Thickness * vec4(vNormal.x, vNormal.y, vNormal.z, 0));
}
