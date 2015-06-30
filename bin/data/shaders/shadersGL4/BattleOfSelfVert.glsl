/*ARB_vertex_shader*/

#version 430 compatibility

varying vec3 normal;
varying vec4 vpos;

void main()
{
    //vec4 dummy, vpos;

    //vpos = gl_ModelViewMatrix * gl_Vertex;

    //gl_Position = gl_ProjectionMatrix * vpos;
    //gl_Position.xyz = 0.2*gl_Vertex.xyz;

    vpos = gl_Vertex;
    gl_Position.xyz = gl_Vertex.xyz;
    //gl_Position.z=0;
    normal = gl_Normal;

    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
}
