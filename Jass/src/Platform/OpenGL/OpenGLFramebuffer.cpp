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
		glDeleteTextures(1, &m_colorAttachment);
		glDeleteTextures(1, &m_depthAttachment);
	}

	void OpenGLFramebuffer::Resize(unsigned int width, unsigned int height)
	{
		m_fbConfig.Width = width;
		m_fbConfig.Height = height;

		Invalidate();
	}

	void OpenGLFramebuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_rendererID);
		glViewport(0, 0, m_fbConfig.Width, m_fbConfig.Height);
	}

	void OpenGLFramebuffer::Unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Invalidate()
	{
		if (!m_fbConfig.Width || !m_fbConfig.Height)
			return;

		if (m_rendererID) {
			glDeleteFramebuffers(1, &m_rendererID);
			glDeleteTextures(1, &m_colorAttachment);
			glDeleteTextures(1, &m_depthAttachment);
		}
		
		glCreateFramebuffers(1, &m_rendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_rendererID);

		// Color Attachment

		glCreateTextures(GL_TEXTURE_2D, 1, &m_colorAttachment);
		glBindTexture(GL_TEXTURE_2D, m_colorAttachment);
		glTextureStorage2D(m_colorAttachment, 1, GL_RGBA8, m_fbConfig.Width, m_fbConfig.Height);
		glTextureParameteri(m_colorAttachment, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_colorAttachment, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorAttachment, 0);

		// Depth Attachment

		glCreateTextures(GL_TEXTURE_2D, 1, &m_depthAttachment);
		glBindTexture(GL_TEXTURE_2D, m_depthAttachment);
		glTextureStorage2D(m_depthAttachment, 1, GL_DEPTH24_STENCIL8, m_fbConfig.Width, m_fbConfig.Height);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depthAttachment, 0);

		JASS_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "The framebuffer is incomplete");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

}
