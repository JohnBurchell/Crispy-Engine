#include "vertex_buffer_object.h"

Vertex_Buffer_Object::Vertex_Buffer_Object(GLfloat* data, GLsizei count, GLuint component_count)
	:	m_index(0),
		m_count(component_count)
{
	//Generate the buffers to set the ID of the buffer to a given int.
	glGenBuffers(1, &m_index);
	glBindBuffer(GL_ARRAY_BUFFER, m_index);
	//Recall that sizeof on a pointer gives the size of the pointer, not the type/data pointed at
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Vertex_Buffer_Object::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_index);
}

void Vertex_Buffer_Object::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}