// test glsl shader

#ifdef VERTEX_SHADER
layout (location=0) in vec3 position;
layout (location=1) in vec2 texcoord;

out vec2 v_texcoord;

layout (std140) uniform GlobalData
{
    mat4 u_modelMatrix;
};

void main()
{
    v_texcoord = texcoord;
    gl_Position = u_modelMatrix * vec4(position, 1.0);
}
#endif

///////////////////////////////////////////////////////////

#ifdef PIXEL_SHADER
in vec2 v_texcoord;
out vec4 fragColor;

uniform sampler2D u_texture;

void main()
{
    fragColor = texture(u_texture, v_texcoord);
}
#endif
