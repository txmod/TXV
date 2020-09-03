
#version 120

// Varyings
varying vec2 v_normal;
varying vec2 v_texCoord0;

// Uniforms
uniform sampler2DRect u_texture0Sampler;
//uniform sampler2DRect u_texture1Sampler; // mask image

uniform float u_alpha;
uniform float u_alphaThreshold;
uniform int   u_invertMask;
uniform float  u_feathering;

uniform int u_useCenterPixel;
uniform float u_centerX;
uniform float u_centerY;

uniform float u_tintMix;
uniform float u_tintR;
uniform float u_tintG;
uniform float u_tintB;

uniform int  u_maskType;

uniform float u_phaseX;
uniform float u_phaseY;
uniform float u_numWavesX;
uniform float u_numWavesY;
uniform int u_wavesHorizontalOn;
uniform int u_wavesVerticalOn;
uniform int u_wavesQuantised;

const float C_PI    = 3.1415;
const float C_2PI   = 2.0 * C_PI;

void main() 
{
	vec4  t0;
//    vec4  t1;
    vec3  tintColor;
    vec3  textureColor; 
    vec4  outColor;
    float maskAlpha, outAlpha;
    float holdDistance, holdFeatherVal;
    float holdWavesVal;
    
    if (u_useCenterPixel == 1) {
        t0 = texture2DRect(u_texture0Sampler, vec2(u_centerX, u_centerY));
    } else {
        t0 = texture2DRect(u_texture0Sampler, v_texCoord0);
    };
    
//	if (u_maskType == 0) {
//        // 0 - no mask
//        maskAlpha = 1.0;
//    } else if (u_maskType == 1) {
//        // 1 - use mask image
//        t1 = texture2DRect(u_texture1Sampler, v_normal.xy);
//        maskAlpha = t1.r;
//    } else
    if (u_maskType == 2) {
        // 2 - feathered square
        holdDistance = max(abs(0.5 - v_normal.x), abs(0.5 - v_normal.y));
        holdFeatherVal = 0.5 - (u_feathering * 0.5);
        if (holdDistance <= holdFeatherVal) {
            maskAlpha = 1.0;
        } else {
            maskAlpha = 1.0 - smoothstep(holdFeatherVal, 0.5, holdDistance);
        };
    } else if (u_maskType == 3) {
        // 3 - circle
        holdDistance = distance(v_normal.xy, vec2(0.5, 0.5));
        if (holdDistance >= 0.5) {
            maskAlpha = 0.0;
        } else {
            maskAlpha = 1.0;
        };
    } else if (u_maskType == 4) {
        // 4 - feathered circle
        holdDistance = distance(v_normal.xy, vec2(0.5, 0.5));
        holdFeatherVal = 0.5 - (u_feathering * 0.5);
        if (holdDistance >= 0.5) {
            maskAlpha = 0.0;
        } else if (holdDistance >= holdFeatherVal) {
            maskAlpha = 1.0 - smoothstep(holdFeatherVal, 0.5, holdDistance);
        } else {
            maskAlpha = 1.0;
        };
    } else if (u_maskType == 5) {
        // 5 - blurred circle
        holdDistance = distance(v_normal.xy, vec2(0.5, 0.5));
        if (holdDistance >= 0.5) {
            maskAlpha = 0.0;
        } else {
            maskAlpha = 1.0 - smoothstep(0.0, 0.5, holdDistance);
        };
    } else if (u_maskType == 6) {
        // 6 - ring
        holdDistance = distance(v_normal.xy, vec2(0.5, 0.5));
        if (holdDistance >= 0.5) {
            maskAlpha = 0.0;
        } else if (holdDistance >= 0.3) {
            maskAlpha = 1.0;
        } else {
            maskAlpha = 0.0;
        };
    } else if (u_maskType == 7) {
        // 7 - feathered ring
        holdDistance = distance(v_normal.xy, vec2(0.5, 0.5));
        holdFeatherVal = 0.1 - (u_feathering * 0.1);
        if (holdDistance >= 0.5) {
            maskAlpha = 0.0;
        } else if (holdDistance >= (0.4 + holdFeatherVal)) {
            maskAlpha = 1.0 - smoothstep((0.4 + holdFeatherVal), 0.5, holdDistance);
        } else if (holdDistance >= (0.4 - holdFeatherVal)) {
            maskAlpha = 1.0;
        } else if (holdDistance >= 0.3) {
            maskAlpha = smoothstep(0.3, (0.4 - holdFeatherVal), holdDistance);
        } else {
            maskAlpha = 0.0;
        };
    } else if (u_maskType == 8) {
        // 8 - diamond
        holdDistance = (abs(v_normal.x -0.5) + abs(v_normal.y -0.5));
        if (holdDistance <= 0.5) {
            maskAlpha = 1.0;
        } else {
            maskAlpha = 0.0;
        };
    } else if (u_maskType == 9) {
        // 9 - feathered diamond
        holdDistance = (abs(v_normal.x -0.5) + abs(v_normal.y -0.5));
        holdFeatherVal = 0.5 - (u_feathering * 0.5);
        if (holdDistance <= holdFeatherVal) {
            maskAlpha = 1.0;
        } else {
            maskAlpha = 1.0 - smoothstep(holdFeatherVal, 0.5, holdDistance);
        };
        
    } else {
        // defaults to no mask
        maskAlpha = 1.0;
    };
    
    if (u_wavesHorizontalOn == 1) {
        holdWavesVal = sin((u_phaseX + (v_normal.s * C_2PI)) * u_numWavesX);
        if (u_wavesQuantised == 1) {
            holdWavesVal = floor(holdWavesVal + 0.5);
        };
        maskAlpha = maskAlpha * holdWavesVal;        
    }; 
    if (u_wavesVerticalOn == 1) {
        holdWavesVal = sin((u_phaseY + (v_normal.t * C_2PI)) * u_numWavesY);
        if (u_wavesQuantised == 1) {
            holdWavesVal = floor(holdWavesVal + 0.5);
        };
        maskAlpha = maskAlpha * holdWavesVal;        
    }; 
    
    if (u_invertMask == 1) {
        maskAlpha = 1.0 - maskAlpha;
    };

    //    float outAlpha = t0.a * u_alpha;
    outAlpha = maskAlpha * u_alpha;
    if (outAlpha < u_alphaThreshold) {
        outAlpha = 0.0;
    }; 

	textureColor = vec3(t0.r, t0.g, t0.b);
    tintColor = vec3(u_tintR, u_tintG, u_tintB);
    outColor = vec4(mix(textureColor, tintColor, u_tintMix), outAlpha);


	gl_FragColor = outColor;
}
