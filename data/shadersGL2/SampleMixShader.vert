
//precision highp float;
precision mediump float;

// Attributes
attribute vec4 a_position;
attribute vec4 a_color;
attribute vec3 a_normal;
attribute vec4 a_texCoord0;

// Uniforms
uniform mat4 u_modelViewMatrix;
uniform mat4 u_modelViewProjectionMatrix;

// Varyings
varying vec2 v_normal;
varying vec2 v_texCoord0; 

void main() 
{

	gl_Position = u_modelViewProjectionMatrix * a_position;
	
	v_normal = a_normal.xy; // pass the attribute along
	v_texCoord0 = a_texCoord0.st; // pass the attribute along

}
