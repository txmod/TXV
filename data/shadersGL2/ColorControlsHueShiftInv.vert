
#version 120

// Uniforms

// Varyings
varying vec2 v_texCoord0;

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
//	v_texCoord0 = gl_MultiTexCoord0.xy; // pass the attribute along
    v_texCoord0  = vec2(gl_TextureMatrix[0] * gl_MultiTexCoord0);
}

