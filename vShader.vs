#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;
out vec3 vertexPosition;

uniform vec3 horizontalOffset;

void main()
{
    gl_Position = vec4(aPos.x - horizontalOffset.x, aPos.y, aPos.z, 1.0);
    ourColor = aColor;
    vertexPosition = vec3(aPos.x - horizontalOffset.x, aPos.y, aPos.z);
}