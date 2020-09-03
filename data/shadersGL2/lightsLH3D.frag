#version 120

#define MAX_LIGHTS 3

// light types:   0-point, 1-directional, 2-spot
uniform int light1Type;
uniform int light2Type;
uniform int light3Type;

varying vec4 ambientGlobal, ecPos;
varying vec4 diffuse1, ambient1;
varying vec4 diffuse2, ambient2;
varying vec4 diffuse3, ambient3;
varying vec3 normal, halfVector;

void main()
{
    vec3 n,halfV,viewV,lightDir;
    float NdotL,NdotHV;
    vec4 color = ambientGlobal;
    float att, dist, spotEffect;
    
    int[3] lightTypes;
    vec4[3] diffuseColors;
    vec4[3] ambientColors;

    lightTypes[0] = light1Type;
    lightTypes[1] = light2Type;
    lightTypes[2] = light3Type;
    diffuseColors[0] = diffuse1;
    diffuseColors[1] = diffuse2;
    diffuseColors[2] = diffuse3;
    ambientColors[0] = ambient1;
    ambientColors[1] = ambient2;
    ambientColors[2] = ambient3;

    /* a fragment shader can't write a verying variable, hence we need
     a new variable to store the normalized interpolated normal */
    n = normalize(normal);
    
    for (int i=0;i<MAX_LIGHTS;i++)
    {
        // Compute the light direction
        lightDir = vec3(gl_LightSource[i].position-ecPos);
        
        // if not directional
        if (lightTypes[i] != 1) {
            /* compute the distance to the light source to a varying variable*/
            dist = length(lightDir);
        } else {
            color += ambientColors[i];
        };
        
        /* compute the dot product between normal and ldir */
        NdotL = max(dot(n,normalize(lightDir)),0.0);
        
        
        if (lightTypes[i] == 1) {
            // directional light
            if (NdotL > 0.0) {
                color += diffuseColors[i] * NdotL;
                halfV = normalize(halfVector);
                NdotHV = max(dot(n,halfV),0.0);
                color += gl_FrontMaterial.specular *
                gl_LightSource[0].specular *
                pow(NdotHV, gl_FrontMaterial.shininess);
                }
        } else if (lightTypes[i] == 0) {
            // point light
            if (NdotL > 0.0) {
                
                att = 1.0 / (gl_LightSource[0].constantAttenuation +
                             gl_LightSource[0].linearAttenuation * dist +
                             gl_LightSource[0].quadraticAttenuation * dist * dist);
                color += att * (diffuseColors[i] * NdotL + ambientColors[i]);
                
                
                halfV = normalize(halfVector);
                NdotHV = max(dot(n,halfV),0.0);
                color += att * gl_FrontMaterial.specular * gl_LightSource[0].specular * pow(NdotHV,gl_FrontMaterial.shininess);
            }
        } else {
            // spot light
            if (NdotL > 0.0) {
                
                spotEffect = dot(normalize(gl_LightSource[0].spotDirection), normalize(-lightDir));
                if (spotEffect > gl_LightSource[0].spotCosCutoff) {
                    spotEffect = pow(spotEffect, gl_LightSource[0].spotExponent);
                    att = spotEffect / (gl_LightSource[0].constantAttenuation +
                                        gl_LightSource[0].linearAttenuation * dist +
                                        gl_LightSource[0].quadraticAttenuation * dist * dist);
                    
                    color += att * (diffuseColors[i] * NdotL + ambientColors[i]);
                    
                    
                    halfV = normalize(halfVector);
                    NdotHV = max(dot(n,halfV),0.0);
                    color += att * gl_FrontMaterial.specular * gl_LightSource[0].specular * pow(NdotHV,gl_FrontMaterial.shininess);
                }
            }
            
        }
        
        
    }
    
    gl_FragColor = color;
}


