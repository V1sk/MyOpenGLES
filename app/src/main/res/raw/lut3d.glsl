// 适配不同的lut滤镜图片 纹理宽度开三次根号的值 例如 4:表示每个通道16位（16*16*16）  8:表示每个通道64位（64*64*64）
#version 300 es                            
precision highp float;
in vec2 v_texCoord;
layout(location = 0) out vec4 outColor;
uniform sampler2D s_TextureMap;
uniform sampler2D LutImageTexture;

void main(){

    lowp vec4 color = texture(s_TextureMap, v_texCoord);
    mediump float intensity = 0.5f;
    mediump float fb = color.b * 15.0;
    mediump float fr = color.r * 15.0;
    mediump float blockLeft = floor(fb);
    mediump float blockRight = ceil(fb);
    highp float u  = blockLeft / 15.0 * 240.0;
    u  = fr + 0.5 + u;
    u /= 256.0;
    highp float v  = color.g;
    lowp vec4 left = texture(LutImageTexture, vec2(u, v));
    u  = blockRight / 15.0 * 240.0;
    u  = fr + 0.5 + u;
    u /= 256.0;
    lowp vec4 right = texture(LutImageTexture, vec2(u, v));
    mediump vec4 interp = mix(left, right, fract(color * 15.0));
    outColor = clamp(mix(color, interp, intensity), 0.0, 1.0);;
}