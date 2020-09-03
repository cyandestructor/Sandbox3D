#include "jasspch.h"
#include "OpenGLFramebuffer.h"

#include <glad/glad.h>

namespace Jass {

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferConfig& config) :
		m_fbConfig(config)
	{
		Invalidate();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &m_rendererID);
	}

	void OpenGLFramebuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_rendererID);
	}

	void OpenGLFramebuffer::Unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Invalidate()
	{
		glCreateFramebuffers(1, &m_rendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_rendererID);

		// Color Attachment

		if (m_colorAttachment != 0)
			glDeleteTextures(1, &m_colorAttachment);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_colorAttachment);
		glBindTexture(GL_TEXTURE_2D, m_colorAttachment);
		glTextureStorage2D(m_colorAttachment, 1, GL_RGBA8, m_fbConfig.Width, m_fbConfig.Height);
		glTextureParameteri(m_colorAttachment, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_colorAttachment, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorAttachment, 0);

		// Depth Attachment

		if (m_depthAttachment != 0)
			glDeleteTextures(1, &m_depthAttachment);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_depthAttachment);
		glBindTexture(GL_TEXTURE_2D, m_depthAttachment);
		glTextureStorage2D(m_depthAttachment, 1, GL_DEPTH24_STENCIL8, m_fbConfig.Width, m_fbConfig.Height);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depthAttachment, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

}
