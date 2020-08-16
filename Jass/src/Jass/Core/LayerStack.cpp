#include "jasspch.h"
#include "LayerStack.h"

namespace Jass {

	LayerStack::LayerStack()
	{
		m_insertLayer = 0;
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_layers.emplace(m_layers.begin() + m_insertLayer, layer);
		m_insertLayer++;
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_layers.begin(), m_layers.end(), layer);
		if (it != end()) {
			m_layers.erase(it);
			m_insertLayer--;
		}
	}

	void LayerStack::PushOverlay(Layer* layer)
	{
		m_layers.emplace_back(layer);
	}

	void LayerStack::PopOverlay(Layer* layer)
	{
		auto it = std::find(m_layers.begin(), m_layers.end(), layer);
		if (it != end())
			m_layers.erase(it);
	}

}