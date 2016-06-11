attribute vec4 vPosition;
attribute vec3 vNormal;

varying vec3 normal;
varying vec4 p;
varying float dist;

uniform mat3 Compensate;
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform vec4 LightPosition;

void main()
{
    gl_Position = Projection * View * Model * vPosition;
    normal = normalize(Compensate * vNormal);

    p = vPosition * View * Model;

    vec3 vDist = vec3(LightPosition - p);
    dist = length(vDist);
}
