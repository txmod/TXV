
precision highp float;
//precision mediump float;

// Attributes
attribute vec4 a_position;
//attribute vec4 a_color;
//attribute vec3 a_normal;
attribute vec4 a_texCoord0;


// Uniforms
//uniform mat4 u_modelViewMatrix;
uniform mat4 u_modelViewProjectionMatrix;

// Varyings
varying vec4 v_texCoord0; 

void main() 
{

	gl_Position = u_modelViewProjectionMatrix * a_position;
	
	v_texCoord0 = a_texCoord0; // pass the attribute along

}
