#pragma once

#include <optional>

namespace ZeroEngine
{
	struct QueueFamilyIndices
	{
		std::optional<uint32_t> m_graphicsFamily;
		std::optional<uint32_t> m_presentFamily;

		bool IsComplete()
		{
			return m_graphicsFamily.has_value() && m_presentFamily.has_value();
		}
	};
}