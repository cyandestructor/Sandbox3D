#ifndef FRAMEBUFFER_H_JASS
#define FRAMEBUFFER_H_JASS

#include "Jass/Core/Core.h"

namespace Jass {

	struct FramebufferConfig {
		unsigned int Width = 1280;
		unsigned int Height = 720;

		unsigned int Samples = 1;

		bool SwapChainTarget = false;
	};

	class JASS_API Framebuffer {

	public:
		virtual ~Framebuffer() = default;

		virtual const FramebufferConfig& GetConfig() const = 0;

		virtual void Resize(unsigned int width, unsigned int height) = 0;

		virtual unsigned int GetColorAttachmentRendererID() const = 0;
		virtual void BindColorAttachment(unsigned int slot = 0) const = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Ref<Framebuffer> Create(const FramebufferConfig& config);

	};

}

#endif // !FRAMEBUFFER_H_JASS
