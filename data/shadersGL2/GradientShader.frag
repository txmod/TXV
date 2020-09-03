
#version 120

// Uniforms
uniform vec2 resolution;
uniform int gradientType;
uniform int numColors;
uniform float curveBias;
uniform int invert; // bool
uniform vec2 point1;
uniform vec2 point2;
uniform vec4 color1;
uniform vec4 color2;
uniform vec4 color3;
uniform vec4 color4;

// vec4 gl_FragColor

void main()
{
    vec2 fragPos = gl_FragCoord.xy / resolution.xy;
    float proportion;

    if (gradientType == 0) {
        // TXGRADIENTTYPE_HORIZONTAL
        if (point1.x == point2.x) {
            proportion = 0.0;
        } else if (point1.x < point2.x) {
            if (fragPos.x <= point1.x) {
                proportion = 0.0;
            } else if (fragPos.x >= point2.x) {
                proportion = 1.0;
            } else {
                proportion = (fragPos.x - point1.x) / (point2.x - point1.x);
            }
        } else {
            if (fragPos.x >= point1.x) {
                proportion = 0.0;
            } else if (fragPos.x >= point2.x) {
                proportion = 1.0;
            } else {
                proportion = (fragPos.x - point1.x) / (point2.x - point1.x);
            }
        }
    } else if (gradientType == 1) {
        // TXGRADIENTTYPE_VERTICAL
        if (point1.y == point2.y) {
            proportion = 0.0;
        } else if (point1.y < point2.y) {
            if (fragPos.y <= point1.y) {
                proportion = 0.0;
            } else if (fragPos.y >= point2.y) {
                proportion = 1.0;
            } else {
                proportion = (fragPos.y - point1.y) / (point2.y - point1.y);
            }
        } else {
            if (fragPos.y >= point1.y) {
                proportion = 0.0;
            } else if (fragPos.y >= point2.y) {
                proportion = 1.0;
            } else {
                proportion = (fragPos.y - point1.y) / (point2.y - point1.y);
            }
        }
    } else {
        // TXGRADIENTTYPE_RADIAL,
        float maxDistance = distance(point1, point2);
        float propDistance = distance(fragPos, point1);
        if (maxDistance < 0.0001) {
            proportion = 1.0;
        } else {
            if (propDistance > maxDistance) {
                proportion = 1.0;
            } else {
                proportion = distance(fragPos, point1) / maxDistance;
            }
        };
    };
    if (invert == 1) {
        proportion = 1.0 - proportion;
    };
    
    float biasedProp = pow(proportion, pow(2.0, curveBias));

    float mixProp;
    vec4 outColor;
    
    if (numColors == 2) {
        outColor = mix(color1, color2, biasedProp);
    } else if (numColors == 3) {
        mixProp = biasedProp * 2;
        if (biasedProp < 0.5) {
            outColor = mix(color1, color2, mixProp);
        } else {
            outColor = mix(color2, color3, mixProp - 1);
        };
    } else {
        mixProp = biasedProp * 3;
        if (biasedProp < 0.333333) {
            outColor = mix(color1, color2, mixProp);
        } else if (biasedProp < 0.666666) {
            outColor = mix(color2, color3, mixProp - 1);
        } else {
            outColor = mix(color3, color4, mixProp - 2);
        };
    }
	gl_FragColor = outColor;
}



