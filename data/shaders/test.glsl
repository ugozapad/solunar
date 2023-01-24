// test glsl shader

#ifdef VERTEX_SHADER
layout (location=0) in vec3 position;
layout (location=1) in vec2 texcoord;

out vec2 v_texcoord;

layout (std140) uniform GlobalData
{
    mat4 u_modelMatrix;
    mat4 u_viewMatrix;
    mat4 u_projectionMatrix;
};

void main()
{
    v_texcoord = texcoord;
    gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * vec4(position, 1.0);
}
#endif

///////////////////////////////////////////////////////////

#ifdef PIXEL_SHADER
in vec2 v_texcoord;
out vec4 fragColor;

uniform sampler2D u_texture;

void main()
{
    //fragColor = texture(u_texture, v_texcoord);
    fragColor = vec4(0.2, 0.3, 0.4, 1.0);
}
#endif
