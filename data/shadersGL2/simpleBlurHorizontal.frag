#version 120

// change sampler2D to sampler2DRect and texture2D to texture2DRect

// Varyings
varying vec2 v_texCoord0;

// Uniforms
uniform sampler2DRect u_texture0Sampler;

uniform float u_blurAmnt;

void main( void )
{  
	vec2 st = v_texCoord0;

	vec4 color = vec4( 0.0, 0.0, 0.0, 0.0 );
	
	color		+= 1.0 * texture2DRect(u_texture0Sampler, st + vec2(u_blurAmnt * -4.0, 0.0));
	color		+= 2.0 * texture2DRect(u_texture0Sampler, st + vec2(u_blurAmnt * -3.0, 0.0));
	color		+= 3.0 * texture2DRect(u_texture0Sampler, st + vec2(u_blurAmnt * -2.0, 0.0));
	color		+= 4.0 * texture2DRect(u_texture0Sampler, st + vec2(u_blurAmnt * -1.0, 0.0));	
		
	color		+= 5.0 * texture2DRect(u_texture0Sampler, st + vec2(u_blurAmnt, 0));
	
	color		+= 4.0 * texture2DRect(u_texture0Sampler, st + vec2(u_blurAmnt * 1.0, 0.0));
	color		+= 3.0 * texture2DRect(u_texture0Sampler, st + vec2(u_blurAmnt * 2.0, 0.0));
	color		+= 2.0 * texture2DRect(u_texture0Sampler, st + vec2(u_blurAmnt * 3.0, 0.0));
	color		+= 1.0 * texture2DRect(u_texture0Sampler, st + vec2(u_blurAmnt * 4.0, 0.0));
	
	color /= 25.0;
	
	color.w = 1.0;
	
	gl_FragColor = color;
}