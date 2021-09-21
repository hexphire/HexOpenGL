#shader vertex
#version 450 core

attribute vec3 coord3d;
attribute vec2 texcoord;
varying vec2 f_texcoord;
uniform mat4 u_MVP;

void main(void) {
	gl_Position = u_MVP * vec4(coord3d, 1.0);
	f_texcoord = texcoord;
};


#shader fragment
#version 450 core

varying vec2 f_texcoord;
uniform sampler2D u_Texture;

void main(void) {
	gl_FragColor = texture2D(u_Texture, f_texcoord);
};
