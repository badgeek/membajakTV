uniform float eyeMultiply;
uniform sampler2DRect eyeTexDepth;

void main()
{
	vec4 color = texture2DRect(eyeTexDepth, gl_MultiTexCoord0.st);
	vec4 eyeDepthVertex = vec4(gl_Vertex);
	eyeDepthVertex.z = color.r * eyeMultiply;
	gl_TexCoord[0]= gl_MultiTexCoord0;
	gl_Position =  gl_ModelViewProjectionMatrix  * eyeDepthVertex;
}

