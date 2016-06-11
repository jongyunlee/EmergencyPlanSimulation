varying vec3 normal;
varying vec4 p;
varying float dist;

uniform vec4 LPosition;
uniform vec4 LightAmbient;
uniform vec4 LightDiffuse;
uniform vec4 LightSpecular;

uniform vec4 FrontMaterialAmbient;
uniform vec4 FrontMaterialDiffuse;
uniform vec4 FrontMaterialSpecular;
uniform float Shininess;

void main()
{
    vec3 v = normalize(-p).xyz;
    vec3 n = normalize(normal);
    vec3 l = normalize(LPosition-p).xyz;
    vec3 r = normalize(reflect(-l, n));
    float att = 1.0 / (1.0 +
    	      	      0.12 * dist +
		      0.10 * dist * dist);
    vec4 loc_ambient = LightAmbient * FrontMaterialAmbient;
    // vec4 glb_ambient = LightDiffuse * gl_FrontMaterial.ambient;
    vec4 glb_ambient = LightDiffuse * FrontMaterialDiffuse;

    // diffuse
    vec4 diffuse = FrontMaterialDiffuse * LightDiffuse;

    // specular
    vec4 specular = pow(max(dot(r, v), 0.0), Shininess) * FrontMaterialSpecular * LightSpecular;

    // calculate result
    gl_FragColor = glb_ambient +
    		   att*(max(dot(l,n), 0.0)*diffuse + loc_ambient + specular);
}