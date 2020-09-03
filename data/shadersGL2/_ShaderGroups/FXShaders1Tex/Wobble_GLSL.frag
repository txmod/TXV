// Constants
const float C_PI    = 3.1415;
const float C_2PI   = 2.0 * C_PI;
const float C_2PI_I = 1.0 / (2.0 * C_PI);
const float C_PI_2  = C_PI / 2.0;

// Varyings
//varying float lightintensity;
varying vec2 v_texCoord0;


//uniform float radius;
uniform float phase;
uniform vec2  freq;
uniform vec2  amp;

uniform sampler2DRect tex0;

void main (void)
{
    vec2  perturb;
    float rad;
    vec3  color;
    
    // Compute a perturbation factor for the x-direction
    //    rad = (gl_TexCoord[0].s + gl_TexCoord[0].t - 1.0 + radius) * freq.x;
    rad = v_texCoord0.s * freq.x;
    
    // Wrap to -2.0*PI, 2*PI
    rad = rad * C_2PI_I;
    // add phase
    rad = rad + phase;
    rad = fract(rad);
    rad = rad * C_2PI;
    
//    // Center in -PI, PI
//    if (rad >  C_PI) rad = rad - C_2PI;
//    if (rad < -C_PI) rad = rad + C_2PI;
//    
//    // Center in -PI/2, PI/2
//    if (rad >  C_PI_2) rad =  C_PI - rad;
//    if (rad < -C_PI_2) rad = -C_PI - rad;
//    
//    perturb.x  = (rad - (rad * rad * rad / 6.0)) * amp.x;
    
   perturb.x  =  sin(rad) * amp.x;
    
    // Now compute a perturbation factor for the y-direction
    //    rad = (gl_TexCoord[0].s - gl_TexCoord[0].t + radius) * freq.y;
    rad = v_texCoord0.t * freq.y;
    
    // Wrap to -2*PI, 2*PI
    rad = rad * C_2PI_I;
    // add phase
    rad = rad + phase;
    rad = fract(rad);
    rad = rad * C_2PI;
    
//    // Center in -PI, PI
//    if (rad >  C_PI) rad = rad - C_2PI;
//    if (rad < -C_PI) rad = rad + C_2PI;
//    
//    // Center in -PI/2, PI/2
//    if (rad >  C_PI_2) rad =  C_PI - rad;
//    if (rad < -C_PI_2) rad = -C_PI - rad;
//    
//    perturb.y  = (rad - (rad * rad * rad / 6.0)) * amp.y;

    perturb.y  =  cos(rad) * amp.y;

    color = vec3 (texture2DRect(tex0, perturb + gl_TexCoord[0].st));
    
    gl_FragColor = vec4 (color, 1.0);
}
