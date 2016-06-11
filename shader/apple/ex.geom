uniform int subdivisionLevel;

varying vec3 perVertexColor;
varying vec3 normal;

vec4 v0, v01, v02;

float intensity(vec4 p1, vec4 p2, vec4 p3) {
  vec3 line1 = (p2- p1).xyz;
  vec3 line2 = (p3 -p1).xyz;
  normal = normalize(cross(line1, line2));
  // vec3 l = normalize(lightPosition).xyz;
  // float d = dot(normal, l);
  // return max(d, 0.0);
  return 1.0;
}

void ProduceVertex(float s, float t) {
     gl_Position = v0 + s*v01 + t*v02;
     // perVertexColor = vec3(0.0, 0.0, 0.4) + intensity(gl_PositionIn[0], gl_PositionIn[1], gl_PositionIn[2], gl_LightSource[0].position) * vec3(0, 0, 1);
     intensity(gl_PositionIn[0], gl_PositionIn[1], gl_PositionIn[2]);
     perVertexColor = vec3(0, 0, 1);
     EmitVertex();
}

int combination(int n, int k) {
  int nominator = 1;
  for (int i = n; i>0; i--) {
    nominator *= i;
  }
  int denominator = 1;
  for (int i = k; i>0; i--) {
    denominator *= i;
  }
  for (int i = (n-k); i>0; i--) {
    denominator *= i;
  }
  return nominator / denominator;
}

void main()
{
  int numLayers = int(pow(2.0, float(subdivisionLevel)));
  float dt = 1.0/float(numLayers);
  float t_top = 1.0;
  int count = 0;

  for (int it=0; it<numLayers; it++) {
    float t_bot = t_top - dt;
    float smax_top = 1.0 - t_top;
    float smax_bot = 1.0 - t_bot;

    int nums = it + 1;
    float ds_top = smax_top / float(nums -1);
    float ds_bot = smax_bot / float(nums);

    float s_top = 0.0;
    float s_bot = 0.0;

    v01 = ( gl_PositionIn[1] - gl_PositionIn[0] );
    v02 = ( gl_PositionIn[2] - gl_PositionIn[0] );
    v0  =   gl_PositionIn[0];

    for (int is=0; is<nums; is++) {
      float c = mod(float(combination(it, is)), 2.0);
      if (c == 1.0) {
        ProduceVertex(s_bot, t_bot);
        ProduceVertex(s_top, t_top);
      }
      s_top += ds_top;
      s_bot += ds_bot;
      if (c == 1.0) {
        ProduceVertex(s_bot, t_bot);
        EndPrimitive();
      }
      count++;
    }
    t_top = t_bot;
    t_bot -= dt;
  }
}
