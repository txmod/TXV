
#version 120

// Varyings
varying vec2 v_texCoord0; 
varying vec2 v_normCoord0;

void main() 
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	
	v_texCoord0 = gl_MultiTexCoord0.xy; 
    
    //v_normCoord0 = vec2(gl_NormalMatrix * gl_Normal);
    v_normCoord0 = gl_Normal.xy;
}


