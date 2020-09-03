#version 120

// NOTE - MASK TEXTURE COORDS HELD IN NORMAL(X/Y) FOR CONVENIENCE

// Uniforms

// Varyings
varying vec2 v_normal;
varying vec2 v_texCoord0;

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	v_normal = gl_Normal.xy; // pass the attribute along
	v_texCoord0 = gl_MultiTexCoord0.xy; // pass the attribute along
}
