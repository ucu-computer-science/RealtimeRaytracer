#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D screenTexture;

uniform int width, height;

void main()
{ 
    vec2 pos = vec2(gl_FragCoord.x/width, gl_FragCoord.y/height);
    vec4 color1 = texture(screenTexture, pos);

    float v = (color1.x+color1.y+color1.z)/3;
    vec4 color2 =  vec4(0,0,0,1);
    
//    FragColor = mix(color1, color2, pow(length(pos - vec2(0.5, 0.5))*1.9, 3));
    FragColor = color1;
}
