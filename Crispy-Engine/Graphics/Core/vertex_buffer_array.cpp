#include "vertex_buffer_array.h"
#include "vertex_buffer_object.h"


Vertex_Buffer_Array::Vertex_Buffer_Array()
	: m_buffers{}
{
	glGenVertexArrays(1, &m_ID);
}

void Vertex_Buffer_Array::add_buffer(Vertex_Buffer_Object* vertex_buffer, GLuint index, GLuint stride, GLuint step)
{
	bind();
	vertex_buffer->bind();

	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, vertex_buffer->get_count(), GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)(step * sizeof(GLfloat)));

	vertex_buffer->unbind();
	unbind();

	m_buffers.emplace_back(vertex_buffer);
}

Vertex_Buffer_Array::~Vertex_Buffer_Array()
{

}