#version 120

// changes for #version 120: OpenGL 2.1
// change sampler2D to sampler2DRect and texture2D to texture2DRect

// NOTE - MASK TEXTURE COORDS HELD IN NORMAL(X/Y) FOR CONVENIENCE


// Uniforms
uniform sampler2DRect u_texture0Sampler;
//uniform sampler2DRect u_texture1Sampler;

uniform int  u_maskType;
uniform int  u_invertMask;
uniform float  u_feathering;

uniform float u_alpha;
uniform float u_alphaThreshold;

uniform float u_numTiles;
uniform int  u_mirrorTileX;
uniform int  u_mirrorTileY;
uniform float u_texXMin;
uniform float u_texYMin;
uniform float u_texXMax;
uniform float u_texYMax;

// Varyings
varying vec2 v_normal;
varying vec2 v_texCoord0;

float wrap(float val, float lo, float hi) {
	float range;
	if (val >= hi) {
		range = hi - lo;
		val -= range;
		if (val < hi) return val;
	} else if (val < lo) {
		range = hi - lo;
		val += range;
		if (val >= lo) return val;
	} else return val;
	if (hi == lo) return lo;
	return val - range * floor((val - lo)/range);
}

float fold(float val, float lo, float hi) {
	float x, c, range, range2;
	x = val - lo;
	if (val >= hi) {
		val = hi + hi - val;
		if (val >= lo) return val;
	} else if (val < lo) {
		val = lo + lo - val;
		if (val < hi) return val;
	} else return val;
	if (hi == lo) return lo;
	range = hi - lo;
	range2 = range + range;
	c = x - range2 * floor(x / range2);
	if (c>=range) c = range2 - c;
	return c + lo;
}

void main() 
{
	vec4 t0;
    vec4 color;
    float maskAlpha;
    float holdDistance, holdFeatherVal;
    float holdTexX, holdTexY;
    
    if (u_numTiles == 1.0) {
        t0 = texture2DRect(u_texture0Sampler, v_texCoord0);
    } else {
        if (u_mirrorTileX == 1) {
            holdTexX = fold(v_texCoord0.x * u_numTiles, u_texXMin, u_texXMax);
        } else {
            holdTexX = wrap(v_texCoord0.x * u_numTiles, u_texXMin, u_texXMax);
        };
        if (u_mirrorTileY == 1) {
            holdTexY = fold(v_texCoord0.y * u_numTiles, u_texYMin, u_texYMax);
        } else {
            holdTexY = wrap(v_texCoord0.y * u_numTiles, u_texYMin, u_texYMax);
        };
        t0 = texture2DRect(u_texture0Sampler, vec2(holdTexX, holdTexY));
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
        // 2 - feathered rectangle
        holdDistance = max(abs(0.5 - v_normal.x), abs(0.5 - v_normal.y));
        holdFeatherVal = 0.5 - (u_feathering * 0.5);
        if (holdDistance <= holdFeatherVal) {
            maskAlpha = 1.0;
        } else {
            maskAlpha = 1.0 - smoothstep(holdFeatherVal, 0.5, holdDistance);
        };
    } else if (u_maskType == 3) {
        // 3 - oval
        holdDistance = distance(v_normal.xy, vec2(0.5, 0.5));
        if (holdDistance >= 0.5) {
            maskAlpha = 0.0;
        } else {
            maskAlpha = 1.0;
        };
    } else if (u_maskType == 4) {
        // 4 - feathered oval
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
        // 5 - blurred oval
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
    if (u_invertMask == 1) {
        maskAlpha = 1.0 - maskAlpha;
    };
    
    float holdAlpha = t0.a * u_alpha * maskAlpha;
    if (holdAlpha < u_alphaThreshold) {
        holdAlpha = 0.0;
    };
    
    color = vec4(t0.r, t0.g, t0.b, holdAlpha);
	gl_FragColor = color;
}

