#include "AddBuffer.h"
#include <iostream>
#include <string>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace buffer;

void AddBuffer::add_buffer(std::vector<GLuint*> buffer, float sommets[])
{
	buffer.push_back(new GLuint);
	glGenBuffers(1, buffer[buffer.size()-1]);
	glBindBuffer(GL_ARRAY_BUFFER, *buffer[buffer.size()-1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sommets), sommets, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FALSE, GL_FLOAT, 0, (void*)0);
	glEnableVertexAttribArray(0);
	this->draw(buffer);
}
void AddBuffer::draw(std::vector<GLuint*> buffer)
{
	for (int i(0); i < buffer.size(); i++)
	{
		glBindVertexArray(*buffer[i]);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glEnableVertexAttribArray(0);
	}
}
