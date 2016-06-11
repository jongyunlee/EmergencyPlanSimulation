varying vec3 normal;
varying vec4 p;
varying float dist;

void main()
{
    gl_FragColor.xyz = vec3(1.0, 1.0, 1.0);

    vec3 v = normalize(-p).xyz;
    vec3 n = normalize(normal);
    vec3 l = normalize(gl_LightSource[0].position-p).xyz;
    vec3 r = normalize(reflect(-l, n));
    float att = 1.0 / (1.0 +
    	      	      0.12 * dist +
		      0.10 * dist * dist);
    vec4 loc_ambient = gl_LightSource[0].ambient * gl_FrontMaterial.ambient;
    vec4 glb_ambient = gl_LightSource[0].diffuse * gl_FrontMaterial.diffuse;

    // diffuse
    vec4 diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;

    // specular
    vec4 specular = pow(max(dot(r, v), 0.0), 100.0) * gl_FrontMaterial.specular * gl_LightSource[0].specular;

    // calculate result
    gl_FragColor = glb_ambient +
    		   att*(max(dot(l,n), 0.0)*diffuse + loc_ambient + specular);
}