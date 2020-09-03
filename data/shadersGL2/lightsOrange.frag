/* NOTE - EXPERIMENTAL!
 this code doesn't look very good. it's the most basic version from the Orange book Chapter 9.
 */

#version 120

// Varyings
//varying vec2 v_texCoord0;

void main()
{
    /*  tex not used
    // apply texture color
    vec4 tex0 = texture2DRect(u_texture0Sampler, v_texCoord0);
	gl_FragColor = gl_Color * tex0;
    */
    
    gl_FragColor =  gl_Color;


}

