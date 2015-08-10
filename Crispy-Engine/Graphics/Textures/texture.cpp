#include "texture.h"

Texture2D::Texture2D()
	: m_ID(0), m_width(0), m_height(0), m_internal_format(GL_RGB), m_image_format(GL_RGB), m_wrap_s(GL_REPEAT), m_wrap_t(GL_REPEAT),
		m_filter_min(GL_LINEAR), m_filter_max(GL_LINEAR) 
{
	glGenTextures(1, &m_ID);
};

void Texture2D::generate(GLuint width, GLuint height, unsigned char* data)
{
	m_width = width;
	m_height = height;

	//Create the texture
	glBindTexture(GL_TEXTURE_2D, m_ID);
	glTexImage2D(GL_TEXTURE_2D, 0, m_internal_format, m_width, m_height, 0, m_image_format, GL_UNSIGNED_BYTE, data);
	//Set Texture wrap and filter modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrap_t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filter_min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filter_max);
	//Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);

}