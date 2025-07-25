#version 330

in  vec4 color;
in  vec4 position;

out vec4 fColor;

void main()
{
	fColor = color;
	float a = abs(position.z)*4;
	if(position.z <= 0){
		vec4 g = color;		
		
		fColor = (1-a) * g+ a * vec4(1.0, 0.5, 0.0, 1.0);
	}
	else {
		vec4 g = color;
		
		fColor = (1-a) * g+ a * vec4(0.0, 0.5, 1.0, 1.0);

	}
}