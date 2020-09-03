uniform sampler2DRect tex0;

uniform float contrast;
uniform float brightness;

void main(){

	vec4 color = texture2DRect(tex0,gl_TexCoord[0].st);

	//adjust brightness and convert to grayscale
	float p = 0.3 *color.g + 0.59*color.r + 0.11*color.b;
	p = p * brightness;
	color = vec4(p,p,p,1.0);
	color = mix( vec4(1.0,1.0,1.0,1.0),color,contrast);
	
	gl_FragColor =  vec4(color.r , color.g, color.b, 1.0);
}
