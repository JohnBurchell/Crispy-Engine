#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <GL/glew.h>

class Texture2D
{
public:

	Texture2D();

	//Generates texture from image data
	void generate(GLuint width, GLuint height, unsigned char* data);

	//Binds the texture to the current active GL_TEXTURE_2D texture object
	inline void bind() const { glBindTexture(GL_TEXTURE_2D, m_ID); };

	//Texture ID
	GLuint m_ID;

	//Texture width and height
	GLuint m_width, m_height;

	//Format of texture object and of loaded image
	GLuint m_internal_format;
	GLuint m_image_format;

	//Wrapping modes on S / T axis
	GLuint m_wrap_s;
	GLuint m_wrap_t;

	//Filtering Modes 
	//Min if texture pixels < screen pixels
	GLuint m_filter_min;
	//Max if texture pixels > screen pixels
	GLuint m_filter_max;

};

#endif //TEXTURE_H_