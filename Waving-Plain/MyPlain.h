#ifndef _MY_PLAIN_H_
#define _MY_PLAIN_H_

#include <vgl.h>
#include <vec.h>

struct MyPlainVertex
{
	vec4 position;
	vec4 color;
};

class MyPlain
{
public:
	int m_NumPoly;				// number of division for a circle
	int m_NumDivision;
	int m_NumVertex;			// .. = m_NumPoly * 2 * 3
	int m_NumTriangle;

	GLuint m_vao;					// handle for vertex array
	GLuint m_vbo;					// handle for array buffer

	bool m_bInit;

	MyPlain()
	{
		m_NumPoly = 0;
		m_NumDivision = 0;
		m_NumTriangle = 0;
		m_NumVertex = 0;
		m_bInit = false;
	}
	void init(int numPoly)
	{
		if (numPoly < 2) numPoly = 2;

		m_NumPoly = numPoly;
		m_NumDivision = numPoly * numPoly;
		m_NumTriangle = m_NumDivision * 2;
		m_NumVertex = m_NumDivision * 2 * 3;
		vec4 m_Color[2] = { vec4(0.6, 0.6, 0.6, 1.0), vec4(0.5, 0.5, 0.5, 1.0) }; // 색상 수정

		printf("Division: %d, Num.of Triangle: %d, Num.of Vertex = %d \n", m_NumPoly, m_NumTriangle, m_NumVertex);

		MyPlainVertex* vertices = new MyPlainVertex[m_NumVertex];

		float len = (2.0 * 0.8) / numPoly; // 크기 수정

		int cur = 0;
		for (int i = 0; i < m_NumPoly; i++)
			for (int j = 0; j < m_NumPoly; j++)
			{
				vec4 a = vec4(-0.8 + i * len, -0.8 + j * len, 0, 1);
				vec4 b = vec4(-0.8 + i * len, -0.8 + (j + 1) * len, 0, 1);
				vec4 c = vec4(-0.8 + (i + 1) * len, -0.8 + j * len, 0, 1);
				vec4 d = vec4(-0.8 + (i + 1) * len, -0.8 + (j + 1) * len, 0, 1);

				vec4 color = m_Color[(i + j) % 2];

				// triangle 1
				vertices[cur].position = a;	vertices[cur].color = color; cur++;
				vertices[cur].position = b;	vertices[cur].color = color; cur++;
				vertices[cur].position = c;	vertices[cur].color = color; cur++;

				// triangle 2
				vertices[cur].position = b;	vertices[cur].color = color; cur++;
				vertices[cur].position = d;	vertices[cur].color = color; cur++;
				vertices[cur].position = c;	vertices[cur].color = color; cur++;
			}

		if (m_bInit == false)
		{
			glGenVertexArrays(1, &m_vao);
			glBindVertexArray(m_vao);

			glGenBuffers(1, &m_vbo);
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		}
		else
		{
			glBindVertexArray(m_vao);
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		}

		glBufferData(GL_ARRAY_BUFFER, sizeof(MyPlainVertex) * m_NumVertex, vertices,
			GL_STATIC_DRAW);

		delete[] vertices;

		m_bInit = true;
	}
	void connectShader(GLuint prog)
	{
		GLuint vPosition = glGetAttribLocation(prog, "vPosition");
		glEnableVertexAttribArray(vPosition);
		glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE,
			sizeof(MyPlainVertex), BUFFER_OFFSET(0));

		GLuint vColor = glGetAttribLocation(prog, "vColor");
		glEnableVertexAttribArray(vColor);
		glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE,
			sizeof(MyPlainVertex), BUFFER_OFFSET(sizeof(vec4)));
	}

	void draw(GLuint program)
	{
		glBindVertexArray(m_vao);
		glUseProgram(program);
		connectShader(program);

		glDrawArrays(GL_TRIANGLES, 0, m_NumVertex);
	}

	void increase() {
		int num = m_NumPoly + 1;
		init(num);
	}
	void decrease() {
		int num = m_NumPoly - 1;
		init(num);
	}
};


#endif
