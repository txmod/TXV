#version 120

varying vec2 texcoord0;
varying vec2 texcoord1;

void main()
{
	// perform standard transform on vertex
	gl_Position = ftransform();
    
	// transform texcoords
	texcoord0 = vec2(gl_TextureMatrix[0] * gl_MultiTexCoord0);
	//texcoord1 = vec2(gl_TextureMatrix[1] * gl_MultiTexCoord1);
    // use normal instead
    //texcoord1 = vec2(gl_NormalMatrix * gl_Normal);
    texcoord1 = gl_Normal.xy;
}