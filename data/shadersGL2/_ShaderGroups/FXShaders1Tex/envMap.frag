#version 120

//
// Fragment shader for environment mapping with an
// equirectangular 2D texture
//
// Authors: John Kessenich, Randi Rost
//
// Copyright (c) 2002-2006 3Dlabs Inc. Ltd.
//
// See 3Dlabs-License.txt for license information
//

/*   ORIGINAL VERSION:
 
uniform vec3  BaseColor;
uniform float MixRatio;

uniform sampler2D EnvMap;

varying vec3  Normal;
varying vec3  EyeDir;
varying float LightIntensity;

const vec3 Xunitvec = vec3(1.0, 0.0, 0.0);
const vec3 Yunitvec = vec3(0.0, 1.0, 0.0);

void main()
{
    // Compute reflection vector
    
    vec3 reflectDir = reflect(EyeDir, Normal);
    
    // Compute altitude and azimuth angles
    
    vec2 index;
    
    index.y = dot(normalize(reflectDir), Yunitvec);
    reflectDir.y = 0.0;
    index.x = dot(normalize(reflectDir), Xunitvec) * 0.5;
    
    // Translate index values into proper range
    
    if (reflectDir.z >= 0.0)
        index = (index + 1.0) * 0.5;
    else
    {
        index.t = (index.t + 1.0) * 0.5;
        index.s = (-index.s) * 0.5 + 1.0;
    }
    
    // if reflectDir.z >= 0.0, s will go from 0.25 to 0.75
    // if reflectDir.z <  0.0, s will go from 0.75 to 1.25, and
    // that's OK, because we've set the texture to wrap.
    
    // Do a lookup into the environment map.
    
    vec3 envColor = vec3(texture2D(EnvMap, index));
    
    // Add lighting to base color and mix
    
    vec3 base = LightIntensity * BaseColor;
    envColor = mix(envColor, base, MixRatio);
    
    gl_FragColor = vec4(envColor, 1.0);
}
 */

/////////// Modified by paul to use sampler2DRect & ImageSize and optional mirroring:

uniform vec3  BaseColor;
uniform float BaseEnvMixRatio;
uniform float LightMixRatio;

uniform sampler2DRect EnvMap;
uniform vec2 ImageSize;
uniform float ImageWidthRecip;
uniform int Mirror;
uniform float Rotation;
uniform float BlurTopBottom;

varying vec3  Normal;
varying vec3  EyeDir;
varying float LightIntensity;

const vec3 Xunitvec = vec3(1.0, 0.0, 0.0);
const vec3 Yunitvec = vec3(0.0, 1.0, 0.0);

float hash( float n )
{
    return fract(sin(n*0.2)*437.585453);
}


void main()
{
    // Compute reflection vector
    
    vec3 reflectDir = reflect(EyeDir, Normal);
    
    // Compute altitude and azimuth angles
    
    vec2 index;
    
    index.y = dot(normalize(reflectDir), Yunitvec);
    reflectDir.y = 0.0;
    index.x = dot(normalize(reflectDir), Xunitvec) * 0.5;
    
    // Translate index values into proper range
    
    if (reflectDir.z >= 0.0)
        index = (index + 1.0) * 0.5;
    else
    {
        index.t = (index.t + 1.0) * 0.5;
        index.s = (-index.s) * 0.5;
        if (index.s < 0) {
            index.s = index.s + 1.0;
        }
    }
    // add rotation
    index.s = fract(index.s  + Rotation);
    
    if (Mirror == 1) {
        if (index.s <= 0.5) {
            index.s = index.s * 2.0;
        } else {
            index.s = 1.0 - ((index.s - 0.5) * 2.0);
        }
    }
    
    // Do a lookup into the environment map.
    
    vec3 envColor = vec3(texture2DRect(EnvMap, index * ImageSize));
    
    // add blur
    if (BlurTopBottom > 0.01) {
        float holdS = index.s;
        float blurDepth = 1.2 * abs(index.t - 0.5);
        float offset = BlurTopBottom * 40 * hash(holdS + index.t) * ImageWidthRecip * blurDepth;
        
        index.s = fract(holdS  + offset);
        vec3 envColor2 = vec3(texture2DRect(EnvMap, index * ImageSize));
        index.s = fract(index.s  + offset);
        vec3 envColor3 = vec3(texture2DRect(EnvMap, index * ImageSize));

        index.s = fract(1.0 + holdS - offset);
        vec3 envColor4 = vec3(texture2DRect(EnvMap, index * ImageSize));
        index.s = fract(1.0 + index.s - offset);
        vec3 envColor5 = vec3(texture2DRect(EnvMap, index * ImageSize));
        
       vec3 blurColor = 0.25 * (envColor2 + envColor3 + envColor4 + envColor5);
        
        envColor = mix(envColor, blurColor, blurDepth);
    }
    
    // Add lighting to base color and mix
    
    // OLD VERSION
//    vec3 base = LightIntensity * BaseColor;
//    vec3 envBaseMixColor = mix(base, envColor * base, BaseEnvMixRatio);
//    envColor = mix(envColor, envBaseMixColor, LightMixRatio);
//    gl_FragColor = vec4(envColor, 1.0);
    
    // NEW VERSION
    vec3 outBaseColor = mix(BaseColor, LightIntensity * BaseColor, LightMixRatio);
    //vec3 outEnvColor = mix(envColor, LightIntensity * BaseColor * envColor, LightMixRatio); // test
    vec3 outEnvColor = mix(envColor, LightIntensity * envColor, LightMixRatio);
    vec3 outColor = mix(outBaseColor, outEnvColor, BaseEnvMixRatio);
    gl_FragColor = vec4(outColor, 1.0);
}



