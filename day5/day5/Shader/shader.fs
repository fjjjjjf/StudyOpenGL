#version 330 core
out vec4 FragColor;


in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixValue;

void main()
{                                                                                //x轴翻转
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(1.0-TexCoord.x,TexCoord.y)), mixValue);//第一个颜色0.8加第二个纹理0.2
}