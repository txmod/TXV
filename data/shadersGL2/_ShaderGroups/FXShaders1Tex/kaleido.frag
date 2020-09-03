#version 120  
      
// varying texture coordinates   
varying vec2 v_texCoord0;

// uniforms
uniform sampler2DRect tex0;
uniform vec2 u_texdim0;
uniform float u_numSections;
uniform float u_rotationOffset;

void main()  
{  
    const float PI = 3.141592658;
    const float TAU = 2.0 * PI;
    
    float holdCentreX = 0.5 * u_texdim0.x;
    float holdCentreY = 0.5 * u_texdim0.y;

//    float posX = (v_texCoord0.x - holdCentreX) / u_texdim0.x;
//    float posY = (v_texCoord0.y - holdCentreY) / u_texdim0.y;
    float scale = max(u_texdim0.x, u_texdim0.y);
    float posX = (v_texCoord0.x - holdCentreX) / scale;
    float posY = (v_texCoord0.y - holdCentreY) / scale;

    float rad = length(vec2(posX, posY));
    float angle = atan(posX, posY);

    float ma = mod(angle, TAU / u_numSections);
    ma = abs(ma - (PI / u_numSections) + (u_rotationOffset * TAU));

    float holdTexX = holdCentreX + (u_texdim0.x * cos(ma) * rad);
    float holdTexY = holdCentreY + (u_texdim0.y * sin(ma) * rad);

    gl_FragColor = texture2DRect(tex0, vec2(holdTexX, holdTexY));

}

