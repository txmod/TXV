// note code used is a modified version of this:
// https://www.opengl.org/sdk/docs/tutorials/ClockworkCoders/lighting.php

#version 120

// light types:   0-off, 1-point, 2-directional, 3-spot
uniform int light1Type;
uniform int light2Type;
uniform int light3Type;

varying vec3 vN;
varying vec3 v;

//void main(void)
//{
//    v = vec3(gl_ModelViewMatrix * gl_Vertex);
//    N = normalize(gl_NormalMatrix * gl_Normal);
//    
//    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
//}
/*
 renderShader.setUniform1i("distortionActive", (int) distortionActive->getBool());
 renderShader.setUniform1i("distortAfterMatrix", (int) distortAfterMatrix->getBool());
 renderShader.setUniform1i("wave1Type", wave1Type->getInt());
 renderShader.setUniform1i("wave2Type", wave2Type->getInt());
 renderShader.setUniform1i("wave3Type", wave3Type->getInt());
 renderShader.setUniform1f("wave1Phase", wave1Phase->getFloat());
 renderShader.setUniform1f("wave2Phase", wave2Phase->getFloat());
 renderShader.setUniform1f("wave3Phase", wave3Phase->getFloat());
 renderShader.setUniform1f("wave1Freq", wave1Freq->getFloat());
 renderShader.setUniform1f("wave2Freq", wave2Freq->getFloat());
 renderShader.setUniform1f("wave3Freq", wave3Freq->getFloat());
 renderShader.setUniform3f("wave1Amp", wave1AmpX->getFloat(), wave1AmpY->getFloat(), wave1AmpZ->getFloat());
 renderShader.setUniform3f("wave2Amp", wave2AmpX->getFloat(), wave2AmpY->getFloat(), wave2AmpZ->getFloat());
 renderShader.setUniform3f("wave3Amp", wave3AmpX->getFloat(), wave3AmpY->getFloat(), wave3AmpZ->getFloat());
 */

//uniform float radius;
uniform int  distortionActive;
uniform int  distortAfterMatrix;
uniform int  wave1Type;
uniform int  wave2Type;
uniform int  wave3Type;
uniform int  wave4Type;
uniform float wave1Phase;
uniform float wave2Phase;
uniform float wave3Phase;
uniform float wave4Phase;
uniform float wave1Freq;
uniform float wave2Freq;
uniform float wave3Freq;
uniform float wave4Freq;
uniform vec3 wave1Amp;
uniform vec3 wave2Amp;
uniform vec3 wave3Amp;
uniform vec3 wave4Amp;

// Constants
const float C_PI    = 3.1415;
const float C_2PI   = 2.0 * C_PI;
const float C_2PI_I = 1.0 / (2.0 * C_PI);
//const float C_PI_2  = C_PI / 2.0;

// https://github.com/ashima/webgl-noise
vec3 mod289(vec3 x) {
    
    return x - floor(x * (1.0 / 289.0)) * 289.0;
    
}
vec2 mod289(vec2 x) {
    
    return x - floor(x * (1.0 / 289.0)) * 289.0;
    
}
vec3 permute(vec3 x) {
    
    return mod289(((x*34.0)+1.0)*x);
    
}
float snoise(vec2 v) {
    const vec4 C = vec4(0.211324865405187, // (3.0-sqrt(3.0))/6.0
                        0.366025403784439, // 0.5*(sqrt(3.0)-1.0)
                        -0.577350269189626, // -1.0 + 2.0 * C.x
                        0.024390243902439); // 1.0 / 41.0
    // First corner
    vec2 i = floor(v + dot(v, C.yy) );
    vec2 x0 = v - i + dot(i, C.xx);
    // Other corners
    vec2 i1;
    //i1.x = step( x0.y, x0.x ); // x0.x > x0.y ? 1.0 : 0.0
    //i1.y = 1.0 - i1.x;
    i1 = (x0.x > x0.y) ? vec2(1.0, 0.0) : vec2(0.0, 1.0);
    // x0 = x0 - 0.0 + 0.0 * C.xx ;
    // x1 = x0 - i1 + 1.0 * C.xx ;
    // x2 = x0 - 1.0 + 2.0 * C.xx ;
    vec4 x12 = x0.xyxy + C.xxzz;
    x12.xy -= i1;
    // Permutations
    i = mod289(i); // Avoid truncation effects in permutation
    vec3 p = permute( permute( i.y + vec3(0.0, i1.y, 1.0 ))
        + i.x + vec3(0.0, i1.x, 1.0 ));
    vec3 m = max(0.5 - vec3(dot(x0,x0), dot(x12.xy,x12.xy), dot(x12.zw,x12.zw)), 0.0);
    m = m*m ;
    m = m*m ;
    // Gradients: 41 points uniformly over a line, mapped onto a diamond.
    // The ring size 17*17 = 289 is close to a multiple of 41 (41*7 = 287)
    vec3 x = 2.0 * fract(p * C.www) - 1.0;
    vec3 h = abs(x) - 0.5;
    vec3 ox = floor(x + 0.5);
    vec3 a0 = x - ox;
    
    // Normalise gradients implicitly by scaling m
    // Approximation of: m *= inversesqrt( a0*a0 + h*h );
    m *= 1.79284291400159 - 0.85373472095314 * ( a0*a0 + h*h );
    
    // Compute final noise value at P
    vec3 g;
    g.x = a0.x * x0.x + h.x * x0.y;
    g.yz = a0.yz * x12.xz + h.yz * x12.yw;
    return 130.0 * dot(m, g);
}

/*  ==== OLD PERLIN - HAS JUMPS ===============
 
float hash( float n )
{
    return fract(sin(n)*43758.5453);
}

float perlin( vec3 x )
{
    // The noise function returns a value in the range -1.0f -> 1.0f
    
    vec3 p = floor(x);
    vec3 f = fract(x);
    
    f       = f*f*(3.0-2.0*f);
    float n = p.x + p.y*57.0 + 113.0*p.z;
    
    return mix(mix(mix( hash(n+0.0), hash(n+1.0),f.x),
                   mix( hash(n+57.0), hash(n+58.0),f.x),f.y),
               mix(mix( hash(n+113.0), hash(n+114.0),f.x),
                   mix( hash(n+170.0), hash(n+171.0),f.x),f.y),f.z);
}
*/

// wave types:  0:sine, 1:cosine, 2:square, 3:rampUp, 4:rampDown, 5:triangle, 6: perlin
float getWaveVal (int waveType, float phase)
{
    float outVal, holdVal;
    if (waveType == 0) {
        // 0:sine
        holdVal = fract(phase) * C_2PI;
        outVal = sin(holdVal);
    } else if (waveType == 1) {
        // 1:cosine
        holdVal = fract(phase) * C_2PI;
        outVal = cos(holdVal);
    } else if (waveType == 2) {
        // 2:square
        holdVal = fract(phase);
        outVal = floor(holdVal + 0.5);
    } else if (waveType == 3) {
        // 3:rampUp
        outVal = fract(phase);
    } else if (waveType == 4) {
        // 4:rampDown
        holdVal = fract(phase);
        outVal = 1 - holdVal;
    } else if (waveType == 5) {
        // 5:triangle
        holdVal = fract(phase);
        if (holdVal <= 0.5) {
            outVal = 2.0 * holdVal;
        } else {
            outVal = 1.0 - (2.0 * (holdVal - 0.5));
        };
    } else {
        // 6: perlin
        //outVal = perlin(vec3(phase, phase, phase));
        outVal = snoise(vec2(phase, phase));
    };
    return outVal;
}

void main (void)
{
    vec4  distort;
    vec4  vDistort;
    vec3  color;
    vec4 holdVertex;
    vec3 wave1, wave2, wave3, wave4;
    
    if (distortionActive == 1) {
        
        if (distortAfterMatrix == 1) {
            holdVertex = gl_ModelViewProjectionMatrix * gl_Vertex;
        } else {
            holdVertex = gl_Vertex;
        };
        
        wave1.x  =  getWaveVal(wave1Type, wave1Phase + (holdVertex.x * wave1Freq));
        wave1.y  =  getWaveVal(wave1Type, wave1Phase + (holdVertex.y * wave1Freq));
        wave1.z  =  getWaveVal(wave1Type, wave1Phase + (holdVertex.z * wave1Freq));
        wave2.x  =  getWaveVal(wave2Type, wave2Phase + (holdVertex.x * wave2Freq));
        wave2.y  =  getWaveVal(wave2Type, wave2Phase + (holdVertex.y * wave2Freq));
        wave2.z  =  getWaveVal(wave2Type, wave2Phase + (holdVertex.z * wave2Freq));
        wave3.x  =  getWaveVal(wave3Type, wave3Phase + (holdVertex.x * wave3Freq));
        wave3.y  =  getWaveVal(wave3Type, wave3Phase + (holdVertex.y * wave3Freq));
        wave3.z  =  getWaveVal(wave3Type, wave3Phase + (holdVertex.z * wave3Freq));
        wave4.x  =  getWaveVal(wave4Type, wave4Phase + (holdVertex.x * wave4Freq));
        wave4.y  =  getWaveVal(wave4Type, wave4Phase + (holdVertex.y * wave4Freq));
        wave4.z  =  getWaveVal(wave4Type, wave4Phase + (holdVertex.z * wave4Freq));
        
        distort.x  = (wave1.x * wave1Amp.x) + (wave2.x * wave2Amp.x) + (wave3.x * wave3Amp.x) + (wave4.x * wave4Amp.x);
        distort.y  = (wave1.y * wave1Amp.y) + (wave2.y * wave2Amp.y) + (wave3.y * wave3Amp.y) + (wave4.y * wave4Amp.y);
        distort.z  = ((wave1.z - 1) * wave1Amp.z) + ((wave2.z - 1) * wave2Amp.z) + ((wave3.z - 1) * wave3Amp.z) + ((wave4.z - 1) * wave4Amp.z);
        //distort.z  = ((wave1.z - 0.5) * wave1Amp.z) + ((wave2.z - 0.5) * wave2Amp.z) + ((wave3.z - 0.5) * wave3Amp.z) + ((wave4.z - 0.5) * wave4Amp.z);
        //distort.z  = (wave1.z * wave1Amp.z) + (wave2.z * wave2Amp.z) + (wave3.z * wave3Amp.z) + (wave4.z * wave4Amp.z);
        distort.w  =  0.0;
        
        /* OLD:
        // Compute a perturbation factor for the x-direction
        //    rad = (gl_TexCoord[0].s + gl_TexCoord[0].t - 1.0 + radius) * freq.x;
        //    rad = holdVertex.x * freq.x;
        
         // Wrap to -2.0*PI, 2*PI
         rad = rad * C_2PI_I;
         // add phase
         rad = rad + phase;
         rad = fract(rad);
         rad = rad * C_2PI;
         
         distort.x  =  sin(rad) * amp.x;
         
         // Now compute a perturbation factor for the y-direction
         //    rad = (gl_TexCoord[0].s - gl_TexCoord[0].t + radius) * freq.y;
         rad = holdVertex.y * freq.y;
         
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
         */
        
        
        vDistort = (holdVertex + distort);
        
        if (distortAfterMatrix == 1) {
            gl_Position = vDistort;
        } else {
            gl_Position = gl_ModelViewProjectionMatrix * vDistort;
        };
    } else {
        gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    };

    gl_FrontColor =  gl_Color;
    gl_TexCoord[0]  = gl_TextureMatrix[0] * gl_MultiTexCoord0;

    // pass through varying
        v = vec3(gl_Position);
        vN = normalize(gl_NormalMatrix * gl_Normal);
    
}
