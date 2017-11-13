#version 120

varying vec2 texCoord0;
varying vec3 normal0;

uniform sampler2D diffuse;
//add uniform for light direction


void main()
{
   gl_FragColor = texture2D(diffuse, texCoord0)
	* clamp(dot(-vec3(0,0,1), normal0), 0.0, 1.0); 
	//clamp(dot(-lightDirection, normal0), 0.0, 1.0);
	// 0,0,1 for light coming out of camera
	//0,-1,0 for light from sky

}