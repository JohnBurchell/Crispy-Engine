#ifndef VERTEX_BUFFER_ARRAY_H_
#define VERTEX_BUFFER_ARRAY_H_

#define GLEW_STATIC
#include <GL/glew.h>

#include <memory>
#include <vector>

class Vertex_Buffer_Object;

using Buffer = Vertex_Buffer_Object;
using Buffer_Vector = std::vector <Buffer*>;

class Vertex_Buffer_Array
{
public:
	Vertex_Buffer_Array();
	~Vertex_Buffer_Array();

	void add_buffer(Vertex_Buffer_Object* vertex_buffer, GLuint index, GLuint stride = 0, GLuint step = 0);

	inline void bind() const { glBindVertexArray(m_ID); };
	inline void unbind() const { glBindVertexArray(0); };

	inline GLuint get_int() const { return m_ID; };

private:

	GLuint m_ID;
	Buffer_Vector m_buffers;
};

#endif //VERTEX_BUFFER_ARRAY_H_