#version 120

uniform int u_useHemiLight;

varying vec3  DiffuseColor;

void main (void)
{
    if (u_useHemiLight == 1) {
        gl_FragColor = vec4(gl_Color.rgb * DiffuseColor, gl_Color.a);
    } else {
        gl_FragColor = gl_Color;
    }
}
