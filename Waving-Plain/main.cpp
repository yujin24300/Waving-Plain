#include <vgl.h>
#include <InitShader.h>
#include <vec.h>
#include "MyPlain.h"

GLuint program;
MyPlain plain;

void myInit()
{
	plain.init(30);
	program = InitShader("vshader.glsl", "fshader.glsl");
}

float myTime = 0;
bool bPlay = false;
bool bWave = false;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glUseProgram(program);

	GLuint uTime = glGetUniformLocation(program, "uTime");
	GLuint uEnableWave = glGetUniformLocation(program, "uEnableWave");
	glUniform1f(uTime, myTime);
	glUniform1i(uEnableWave, bWave);

	plain.draw(program);

	glFlush();
}


void idle()
{
	if (bPlay) myTime += 0.0111f;

	Sleep(33);							// 33 milisecond
	glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1': plain.decrease();	break;
	case '2': plain.increase();	break;
	case 'w': bWave = !bWave;		break;
	case ' ': bPlay = !bPlay;		break;
	case 'q': exit(1);
	default:						break;
	}
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Waving Plain");

	glewExperimental = true;
	glewInit();

	printf("A Waving Color Plain\n");
	printf("----------------------------------------------------------------\n");
	printf("'1' key: Decreaing the Number of Division\n");
	printf("'2' key: Increaing the Number of Division\n");
	printf("'w' key: Showing/hiding the waving pattern\n");
	printf("Spacebar: starting/stoping rotating and waving\n\n");
	printf("'q' Key: Exit the program.\n");
	printf("----------------------------------------------------------------\n\n");

	myInit();

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}