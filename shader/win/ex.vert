//
// Passing example
//

#version 140
#extension GL_ARB_compatibility: enable

out vec3 normal;
out vec4 p;
out float dist;

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
        normal = normalize(gl_NormalMatrix * gl_Normal);
        p = gl_Vertex * gl_Position;
        vec3 vDist = vec3(gl_LightSource[0].position - p);
        dist = length(vDist);
}
