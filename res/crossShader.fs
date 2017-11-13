#version 120

varying vec2 texCoord0;
varying vec3 normal0;

uniform sampler2D diffuse;
//add uniform for light direction


void main()
{
   gl_FragColor = texture2D(diffuse, texCoord0);

}