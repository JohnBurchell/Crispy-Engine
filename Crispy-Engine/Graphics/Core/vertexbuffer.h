#ifndef VERTEX_ARRAY_H_
#define VERTEX_ARRAY_H_


#define GLEW_STATIC
#include <GL/glew.h>

class Vertex_Buffer
{

public:

	Vertex_Buffer(GLfloat* data, GLsizei count, GLuint component_count);

	inline void bind() const { glBindVertexArray(m_index); };
	inline void unbind() const { glBindVertexArray(0); };

	inline GLuint get_index() const { return m_index; };
	inline GLuint get_count() const { return m_count; };

private:
	
	GLuint m_index;
	GLuint m_count;
};

#endif //VERTEX_ARRAY_H_