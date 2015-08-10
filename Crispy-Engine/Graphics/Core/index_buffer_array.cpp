#include "index_buffer_array.h"

Index_Buffer_Array::Index_Buffer_Array(GLshort* data, GLuint count) :
	m_id(0), m_count(count)
{
	glGenBuffers(1, &m_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Index_Buffer_Array::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void Index_Buffer_Array::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}