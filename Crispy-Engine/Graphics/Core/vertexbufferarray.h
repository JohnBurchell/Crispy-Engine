#ifndef VERTEX_BUFFER_ARRAY_H_
#define VERTEX_BUFFER_ARRAY_H_

#define GLEW_STATIC
#include <GL/glew.h>

#include <memory>
#include <vector>

#include "vertexbuffer.h"

using Buffer = std::shared_ptr <Vertex_Buffer>;
using Buffer_Vector = std::vector <Buffer>;

class Vertex_Buffer_Array
{
public:
	Vertex_Buffer_Array();
	~Vertex_Buffer_Array();

	//TODO - Decide if we want to allow copying / moving

	void add_buffer(Buffer vertex_buffer, GLuint index, GLuint stride = 0, GLuint step = 0);

	inline void bind() const { glBindVertexArray(m_index); };
	inline void unbind() const { glBindVertexArray(0); };

private:

	GLuint m_index;
	Buffer_Vector m_buffers;
};

#endif //VERTEX_BUFFER_ARRAY_H_