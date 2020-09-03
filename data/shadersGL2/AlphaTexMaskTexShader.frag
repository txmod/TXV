#version 120

// changes for #version 120: OpenGL 2.1
// change sampler2D to sampler2DRect and texture2D to texture2DRect

// NOTE - MASK TEXTURE COORDS HELD IN NORMAL(X/Y) FOR CONVENIENCE

// Uniforms
uniform sampler2DRect u_texture0Sampler;
uniform sampler2DRect u_texture1Sampler;

//uniform int  u_maskType;
uniform int  u_invertMask;

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
	vec4 t1;
    vec4 color;
    float maskAlpha;
    float holdDistance;
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
    
    t1 = texture2DRect(u_texture1Sampler, v_normal.xy);
    maskAlpha = t1.r;

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

