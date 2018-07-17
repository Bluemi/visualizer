VISUALIZER_SHADER_STRINGIFY(
out vec4 FragColor;
in vec3 Norm;

uniform vec3 color;

void main()
{
	//FragColor = vec4(0.4f, 0.25f, 0.f, 1.0f);
	FragColor = vec4(color, 1.0);
}
)
