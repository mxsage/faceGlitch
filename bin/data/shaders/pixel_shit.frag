#version 120

uniform sampler2DRect tex0;
uniform float random;
varying vec2 texCoordVarying;


void main (void)
{
    vec4 col = texture2DRect(tex0,texCoordVarying + vec2(mod(texCoordVarying.x/1000.0, 10.0)-5.0,floor(sin(texCoordVarying.y*random+random*random))*random));
    
    gl_FragColor = col;
}