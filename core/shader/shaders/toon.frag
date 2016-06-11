varying vec3 normal;
varying vec4 p;

uniform vec4 LPosition;
uniform int RangeNumber;

void main()
{
    vec4 initColor = vec4(1.0,0.8,0.8,1.0);
    vec3 n = normalize(normal);
    vec3 li = normalize(LPosition-p).xyz;
    float intensity = dot(li, n);

    vec4 color;

    float rangeUnit = 1.0 / float(RangeNumber);
    for (int i = 1; i <= RangeNumber; i++) {
        if (intensity < rangeUnit * float(i)) {
	   color = rangeUnit * float(i) * initColor;
	   break;
	}
    }
    gl_FragColor = color;
}