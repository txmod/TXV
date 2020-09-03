#version 120

/* NOTE - EXPERIMENTAL!
 this code doesn't look very good. it's from here
 http://www.lighthouse3d.com/tutorials/glsl-tutorial
 */

varying vec4 ambientGlobal, ecPos;
varying vec4 diffuse1, ambient1;
varying vec4 diffuse2, ambient2;
varying vec4 diffuse3, ambient3;
varying vec3 normal, halfVector;

void main()
{
    vec3 aux;
    
    /* first transform the normal into eye space and normalize the result */
    normal = normalize(gl_NormalMatrix * gl_Normal);
    
    /* compute the vertex position  in camera space. */
    ecPos = gl_ModelViewMatrix * gl_Vertex;
    
    /* Normalize the halfVector to pass it to the fragment shader */
    halfVector = gl_LightSource[0].halfVector.xyz;
    
    /* Compute the diffuse, ambient and globalAmbient terms */
    diffuse1 = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
    ambient1 = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
    diffuse2 = gl_FrontMaterial.diffuse * gl_LightSource[1].diffuse;
    ambient2 = gl_FrontMaterial.ambient * gl_LightSource[1].ambient;
    diffuse3 = gl_FrontMaterial.diffuse * gl_LightSource[2].diffuse;
    ambient3 = gl_FrontMaterial.ambient * gl_LightSource[2].ambient;
    ambientGlobal = gl_LightModel.ambient * gl_FrontMaterial.ambient;
    
    
    gl_Position = ftransform();
}
