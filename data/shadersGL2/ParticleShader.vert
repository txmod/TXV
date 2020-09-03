
#version 120

// Varyings
varying vec2 v_normal;
varying vec2 v_texCoord0; 

uniform int u_bendOn;
uniform float u_phaseX;
uniform float u_phaseY;
uniform float u_bendDepthX;
uniform float u_bendDepthY;
uniform float u_bendZoom;

void main()
{
    if (u_bendOn == 1) {
        vec3 vertex = gl_Vertex.xyz + (sin(u_phaseY + gl_Vertex.y) * u_bendDepthY)
            + (sin(u_phaseX + gl_Vertex.x) * u_bendDepthX);
        gl_Position = gl_ModelViewProjectionMatrix * vec4(vertex, 1.0 / u_bendZoom);
    } else {
        // u_bendOn == 0
        gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    };
   	
    // pass the attributes along
	v_normal = gl_Normal.xy; 
    v_texCoord0 = gl_MultiTexCoord0.st; 
}

