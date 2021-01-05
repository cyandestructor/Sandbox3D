#ifndef OPENGL_FRAMEBUFFER_H_JASS
#define OPENGL_FRAMEBUFFER_H_JASS

#include "Jass/Renderer/Framebuffer.h"

namespace Jass {

	class JASS_API OpenGLFramebuffer : public Framebuffer {

	public:
		OpenGLFramebuffer(const FramebufferConfig& config);
		virtual ~OpenGLFramebuffer();

		virtual const FramebufferConfig& GetConfig() const override { return m_fbConfig; }

		virtual void Resize(unsigned int width, unsigned int height) override;

		virtual unsigned int GetColorAttachmentRendererID() const override { return m_colorAttachment; }
		virtual void BindColorAttachment(unsigned int slot = 0) const override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void Invalidate();

	private:
		unsigned int m_rendererID = 0;
		unsigned int m_colorAttachment = 0;
		unsigned int m_depthAttachment = 0;
		FramebufferConfig m_fbConfig;

	};

}

#endif // !OPENGL_FRAMEBUFFER_H_JASS
