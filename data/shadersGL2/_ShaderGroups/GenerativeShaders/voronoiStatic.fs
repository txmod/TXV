uniform float time;
uniform float zoom;
uniform vec2 mouse;
uniform vec2 resolution;
uniform vec4 color1;
//uniform vec4 color2;
//uniform vec4 color3;
//uniform vec4 color4;

const float jitter = 0.76;
const float FracMapJitter = 0.76; //0.0 is a grid, >0.8 is bad edges
const float K = 0.142857142857; // 1/7
const float Ko = 0.428571428571; // 3/7



vec3 permute(vec3 x) {
    return mod((34.0 * x + 1.0) * x, 560.0);
}

// Cellular noise, returning F1 and F2 in a vec2.
// Standard 3x3 search window for good F1 and F2 values
vec2 cellular(vec2 P) {
    vec2 Pi = mod(floor(P), 289.0);
    vec2 Pf = fract(P);
    vec3 oi = vec3(-1.0, 0.0, 1.0);
    vec3 of = vec3(-0.5, 0.5, 1.5);
    vec3 px = permute(Pi.x + oi);
    vec3 p = permute(px.x + Pi.y + oi); // p11, p12, p13
    vec3 ox = fract(p*K) - Ko;
    vec3 oy = mod(floor(p*K),7.0)*K - Ko;
    vec3 dx = Pf.x + 0.5 + jitter*ox;
    vec3 dy = Pf.y - of + jitter*oy;
    vec3 d1 = dx * dx + dy * dy; // d11, d12 and d13, squared
    p = permute(px.y + Pi.y + oi); // p21, p22, p23
    ox = fract(p*K) - Ko;
    oy = mod(floor(p*K),7.0)*K - Ko;
    dx = Pf.x - 0.5 + jitter*ox;
    dy = Pf.y - of + jitter*oy;
    vec3 d2 = dx * dx + dy * dy; // d21, d22 and d23, squared
    p = permute(px.z + Pi.y + oi); // p31, p32, p33
    ox = fract(p*K) - Ko;
    oy = mod(floor(p*K),7.0)*K - Ko;
    dx = Pf.x - 1.5 + jitter*ox;
    dy = Pf.y - of + jitter*oy;
    vec3 d3 = dx * dx + dy * dy; // d31, d32 and d33, squared
    // Sort out the two smallest distances (F1, F2)
    vec3 d1a = min(d1, d2);
    d2 = max(d1, d2); // Swap to keep candidates for F2
    d2 = min(d2, d3); // neither F1 nor F2 are now in d3
    d1 = min(d1a, d2); // F1 is now in d1
    d2 = max(d1a, d2); // Swap to keep candidates for F2
    d1.xy = (d1.x < d1.y) ? d1.xy : d1.yx; // Swap if smaller
    d1.xz = (d1.x < d1.z) ? d1.xz : d1.zx; // F1 is in d1.x
    d1.yz = min(d1.yz, d2.yz); // F2 is now not in d2.yz
    d1.y = min(d1.y, d1.z); // nor in  d1.z
    d1.y = min(d1.y, d2.x); // F2 is in d1.y, we're done.
    return sqrt(d1.xy);
}

void main( void ) {
    float FracMapScale = zoom * 16.0;
    float FracMapLineWidth = FracMapScale / resolution.x * 0.7;
    float FracMapLineAA = FracMapScale / resolution.x * 1.5;
    vec2 position = ((( gl_FragCoord.xy / resolution.x ) + mouse * 2.0) - 1.0) * FracMapScale;
    vec2 F = cellular(position);
    float lines = 1.0 - smoothstep(FracMapLineWidth, FracMapLineWidth + FracMapLineAA, abs(F.y-F.x));
// OLD:
//    gl_FragColor = vec4(lines * 0.7, lines * 0.5, lines * 0.2, 1.0);
    gl_FragColor = vec4(lines * color1.r, lines * color1.g, lines * color1.b, color1.a);
}