// test glsl shader

#ifdef VERTEX_SHADER
layout (location=0) in vec3 position;
//layout (location=1) in vec2 texcoord;

//out vec2 v_texcoord;

void main()
{
   // v_texcoord = texcoord;
    gl_Position = vec4(position, 1.0);
}
#endif

///////////////////////////////////////////////////////////

#ifdef PIXEL_SHADER
//in vec2 v_texcoord;
out vec4 fragColor;

void main()
{
    fragColor = vec4(1.0);
}
#endif
