#ifndef JASS_LAYERSTACK_H
#define JASS_LAYERSTACK_H

#include "Layer.h"

namespace Jass {

	class JASS_API LayerStack {

	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void PopOverlay(Layer* layer);

		std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_layers.end(); }
		std::vector<Layer*>::reverse_iterator rbegin() { return m_layers.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return m_layers.rend(); }

	private:
		std::vector<Layer*> m_layers;
		int m_insertLayer;

	};

}

#endif // !JASS_LAYERSTACK_H
