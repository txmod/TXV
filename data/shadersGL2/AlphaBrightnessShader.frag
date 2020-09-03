
#version 120

// changes for #version 120: OpenGL 2.1
// change sampler2D to sampler2DRect and texture2D to texture2DRect

// Varyings
varying vec2 v_texCoord0;

// Uniforms
uniform sampler2DRect u_texture0Sampler;
uniform float u_alpha;
uniform float u_brightness;

void main()
{
	vec4 tex0 = texture2DRect(u_texture0Sampler, v_texCoord0.st);
    
	vec4 color = vec4(tex0.r * u_brightness, tex0.g * u_brightness, tex0.b * u_brightness, tex0.a * u_alpha);
	gl_FragColor = color;
}



