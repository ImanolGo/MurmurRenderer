/*EXT_geometry_shader*/
//InputPrimitive LINES
//OutputPrimitive TRIANGLE_STRIP
//VerticesOut 24

#version 430 compatibility

uniform float nshift=0.0;
uniform float thick=0.03;
in vec4 vpos[];
in vec3 normal[];
varying vec3 normal2;

void main(void)
{
    normal2=normal[0];
    gl_Position = gl_ProjectionMatrix * (gl_ModelViewMatrix * (vpos[0] + (nshift-0.5*thick)*vec4(normal2,0)) );
    EmitVertex();
    gl_Position = gl_ProjectionMatrix * (gl_ModelViewMatrix * (vpos[0] + (nshift+0.5*thick)*vec4(normal2,0)) );
    EmitVertex();

    normal2=normal[1];
    gl_Position = gl_ProjectionMatrix * (gl_ModelViewMatrix * (vpos[1] + (nshift-0.5*thick)*vec4(normal2,0)) );
    EmitVertex();
    gl_Position = gl_ProjectionMatrix * (gl_ModelViewMatrix * (vpos[1] + (nshift+0.5*thick)*vec4(normal2,0)) );
    EmitVertex();
    EndPrimitive();
}
