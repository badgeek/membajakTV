#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect eyeTexDepth;

void main (void)
{
	vec4 color = texture2DRect(eyeTexDepth, gl_TexCoord[0].st);
	gl_FragColor = color;
}


