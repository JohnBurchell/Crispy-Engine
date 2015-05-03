#include "vertexbuffer.h"

Vertex_Buffer::Vertex_Buffer(GLfloat* data, GLsizei count, GLuint component_count)
	:	m_index(0),
		m_count(component_count)
{
	//Generate the buffers to set the ID of the buffer to a given int.
	glGenBuffers(1, &m_index);
	bind();
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
	unbind();
}