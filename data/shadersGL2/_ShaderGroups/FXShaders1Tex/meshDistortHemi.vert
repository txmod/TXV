#version 120

// THIS VERSION OF MESHDISTORT USES A HEMILIGHT
// BUT IT LOOKS WIERD WITH COMPLEX MESHES; THE INNER FACES SHOW SHADOWS

uniform int u_useHemiLight;
//uniform vec3 LightPosition;
//uniform vec3 SkyColor;
//uniform vec3 GroundColor;
const vec3 LightPosition = vec3(0.5, 0.5, 0.0);
const vec3 SkyColor = vec3(1.0, 1.0, 1.0);
const vec3 GroundColor = vec3(0.1, 0.1, 0.1);

// varying
varying vec3  DiffuseColor;  // GLSLdemo requires vertex/fragment shader pair

//uniform float radius;
uniform float phase;
uniform vec3  freq;
uniform vec3  amp;

// Constants
const float C_PI    = 3.1415;
const float C_2PI   = 2.0 * C_PI;
const float C_2PI_I = 1.0 / (2.0 * C_PI);
//const float C_PI_2  = C_PI / 2.0;

void main (void)
{
    vec4  distort;
    vec4  vDistort;
    float rad;
    vec3  color;

     // Compute a perturbation factor for the x-direction
    //    rad = (gl_TexCoord[0].s + gl_TexCoord[0].t - 1.0 + radius) * freq.x;
    rad = gl_Vertex.x * freq.x;
    
    // Wrap to -2.0*PI, 2*PI
    rad = rad * C_2PI_I;
    // add phase
    rad = rad + phase;
    rad = fract(rad);
    rad = rad * C_2PI;
    
    distort.x  =  sin(rad) * amp.x;
    
    // Now compute a perturbation factor for the y-direction
    //    rad = (gl_TexCoord[0].s - gl_TexCoord[0].t + radius) * freq.y;
    rad = gl_Vertex.y * freq.y;
    
    // Wrap to -2*PI, 2*PI
    rad = rad * C_2PI_I;
    // add phase
    rad = rad + phase;
    rad = fract(rad);
    rad = rad * C_2PI;
    
    distort.y  =  cos(rad) * amp.y;
    //distort.z  =  distort.y;
    distort.z  =  cos(rad) * amp.z;
    distort.w  =  0.0;

	gl_FrontColor =  gl_Color;
    gl_TexCoord[0]  = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    vDistort = (gl_Vertex + distort);
	gl_Position = gl_ModelViewProjectionMatrix * vDistort;

    // pass through varying
    vec3 ecPosition = vec3(gl_ModelViewMatrix * vDistort);
    vec3 tnorm      = normalize(gl_NormalMatrix * gl_Normal);
    vec3 lightVec   = normalize(LightPosition - ecPosition);
    float costheta  = dot(tnorm, lightVec);
    float a         = 0.5 + 0.5 * costheta;
    DiffuseColor    = mix(GroundColor, SkyColor, a);
    
    
}
