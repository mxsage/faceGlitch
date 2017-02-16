#version 120

uniform sampler2DRect tex0;
uniform float random;
uniform int time;

varying vec2 texCoordVarying;

void main() {
    vec4 color = texture2DRect(tex0, texCoordVarying + vec2((mod(random, .01)-0.005)*1000.0, 0));
    
    if (mod(time*(random), texCoordVarying.x/10.0) > 10){
        vec4 left_color = texture2DRect(tex0, texCoordVarying+vec2(random*100, 0));
        vec4 right_color = texture2DRect(tex0, texCoordVarying+vec2(-random*100, 0));
    
        gl_FragColor = vec4(right_color.r, color.g, left_color.b, 1);
    }
    else {
        gl_FragColor = color;
    }
}