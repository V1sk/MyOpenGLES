// 适配不同的lut滤镜图片 纹理宽度开三次根号的值 例如 4:表示每个通道16位（16*16*16）  8:表示每个通道64位（64*64*64）
#version 300 es                            
precision highp float;                     
in vec2 v_texCoord;                        
layout(location = 0) out vec4 outColor;     
uniform sampler2D s_TextureMap;      
uniform sampler2D LutImageTexture;      
void main(){                               
    lowp vec4 color = texture(s_TextureMap, v_texCoord);

    lowp float blockLeft = floor(color.b * 15.0);
    lowp float blockRight = ceil(color.b * 15.0);
    mediump float u = blockLeft / 15.0 * 240.0;
    u  = (floor(color.r * 15.0) / 15.0 * 15.0) + u;
    u /= 255.0;
    mediump float v  = (floor(color.g * 15.0) / 15.0);
    lowp vec4 left = texture(LutImageTexture, vec2(u, v));

    u  = blockRight / 15.0 * 240.0;
    u  = (ceil(color.r * 15.0) / 15.0 * 15.0) + u;
    u /= 255.0;
    v  = (ceil(color.g * 15.0) / 15.0);
    lowp vec4 right = texture(LutImageTexture, vec2(u, v));

    color.r = mix(left.r, right.r, fract(color.r * 15.0));
    color.g = mix(left.g, right.g, fract(color.g * 15.0));
    color.b = mix(left.b, right.b, fract(color.b * 15.0));
    outColor = color;
}