#shader vertex
#version 450 core

attribute vec3 coord3d;
attribute vec3 v_color;
uniform mat4 u_MVP;
varying vec3 f_color;

void main(void) {
	gl_Position = u_MVP * vec4(coord3d, 1.0);
	f_color = v_color;
}
;

#shader fragment
#version 450 core

varying vec3 f_color;


void main(void) {
	gl_FragColor = vec4(f_color.r, f_color.g, f_color.b, 1.0);
}
;