#version 120

uniform sampler2DRect tex0;
uniform float random;
varying vec2 texCoordVarying;


void main (void)
{
    vec4 col = texture2DRect(tex0,texCoordVarying + vec2(0,floor(sin(texCoordVarying.y/80.0*random+random*random))*80.0*random));
    
    gl_FragColor = col;
}