
#version 120

// Varyings
varying vec2 v_texCoord0; 

void main() 
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	
	v_texCoord0 = gl_MultiTexCoord0.xy; // pass the attribute along
    
}
