/*EXT_geometry_shader*/
//InputPrimitive LINES
//OutputPrimitive TRIANGLE_STRIP
//VerticesOut 24

#version 150 

uniform float nshift=0.0;
uniform float thick=0.03;

in vec4 vpos[];
in vec3 normal_[];
out vec3 normal2;

layout(lines) in;
layout(triangle_strip, max_vertices = 4) out;


void main(void)
{
    normal2=normal_[0];
    gl_Position = (gl_in[0].gl_Position + (nshift-0.5*thick)*vec4(normal2,0)) ;
    EmitVertex();
    gl_Position =  (gl_in[0].gl_Position + (nshift+0.5*thick)*vec4(normal2,0)) ;
    EmitVertex();

    normal2=normal_[1];
    gl_Position = = (gl_in[1].gl_Position + (nshift-0.5*thick)*vec4(normal2,0));
    EmitVertex();
    gl_Position =  (gl_in[1].gl_Position + (nshift+0.5*thick)*vec4(normal2,0)) );
    EmitVertex();
    EndPrimitive();
}
