#version 460 core

uniform sampler2D myTexture;
uniform float mycolor;

in vec3 color;
in vec2 TexCoord;

out vec4 fragColor;

void main() {
    fragColor = texture(myTexture, TexCoord) * vec4(color.x, color.y, mycolor, 1.0);
}