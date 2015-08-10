#ifndef INDEX_BUFFER_ARRAY_H_
#define INDEX_BUFFER_ARRAY_H_

#define GLEW_STATIC
#include <GL/glew.h>

class Index_Buffer_Array
{
public:
	Index_Buffer_Array(GLshort* data, GLuint count);

	void bind() const;
	void unbind() const;

	inline GLuint get_count() { return m_count; };

private:

	GLuint m_count;
	GLuint m_id;
};

#endif //INDEX_BUFFER_ARRAY_H_