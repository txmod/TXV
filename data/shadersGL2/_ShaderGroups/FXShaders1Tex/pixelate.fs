#version 120

varying vec2 v_texCoord0;

uniform sampler2DRect tex0; 
uniform float dryWetMix;
uniform float pixelWidth; // e.g. 15.0
uniform float pixelHeight; // e.g. 10.0
void main() 
{ 
    vec2 newCoord;
    float offsetX = floor(pixelWidth * 0.5);
    float offsetY = floor(pixelHeight * 0.5);
    newCoord.x = offsetX + (v_texCoord0.x - (mod(v_texCoord0.x, pixelWidth)));
    newCoord.y = offsetY + (v_texCoord0.y - (mod(v_texCoord0.y, pixelHeight)));
    
    vec4 dry =  texture2DRect(tex0, v_texCoord0);
    vec4 wet =  texture2DRect(tex0, newCoord);

    gl_FragColor = mix(dry, wet, dryWetMix);
}
