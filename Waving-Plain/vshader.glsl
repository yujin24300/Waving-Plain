#version 330

uniform float uTime;
uniform bool uEnableWave; // ���� Ȱ��ȭ ����

in vec4 vPosition;			// x,y,z,1		-> vec3 ->vec4
in vec4 vColor;

out vec4 color;
out vec4 position;

void main()
{
	float ang = uTime*90/180.0f*3.141592f;
	float a = -0.5*90/180.0f*3.141592f;
	vec4 newPosition = vPosition;

	if (uEnableWave) {
        float distanceFromCenter = length(newPosition.xy); // �߽����κ����� �Ÿ�
        
        // ���� �Ķ����
        float frequency = 20.0; // ���� ���ļ�
        float maxAmplitude = 0.35; // �߽ɿ����� �ִ� ����
        
        // �Ÿ��� ���� ���� ����
        float decayRate = 3.5; // ���� ������, ���� Ŭ���� �� ������ ����
	    float amplitudeFactor = exp(-decayRate * distanceFromCenter);
		if(distanceFromCenter >= 0.8)
			amplitudeFactor = 0;
        
        // �Ÿ��� ���� �����ϴ� �������� �ĵ� ���
        float waveHeight = maxAmplitude * amplitudeFactor * sin(frequency * distanceFromCenter - uTime * 20.0);
        
        newPosition.z = waveHeight;

    }
	
	mat4 m1 = mat4(1.0f);			//[1 0 0 0]
	// x-rotation					//[0 c-s 0]
									//[0 s c 0]
									//[0 0 0 1]
	m1[1][1] = cos(a);
	m1[1][2] = -sin(a);
	m1[2][1] = sin(a);
	m1[2][2] = cos(a);


	mat4 m3 = mat4(1.0f);			//[ c s 0 0]
	// z-rotation					//[-s c 0 0]
									//[ 0 0 1 0]
									//[ 0 0 0 1]
	m3[0][0] = cos(ang);
	m3[0][1] = sin(ang);
	m3[1][0] = -sin(ang);
	m3[1][1] = cos(ang);


	gl_Position = m1*m3*newPosition;

	gl_Position.w = 1.0f;
	color = vColor;
	position = newPosition;
}