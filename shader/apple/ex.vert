varying vec3 normal;
varying vec4 p;
varying float dist;

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
        normal = normalize(gl_NormalMatrix * gl_Normal);
        p = gl_Vertex * gl_Position;
        vec3 vDist = vec3(gl_LightSource[0].position - p);
        dist = length(vDist);
}
