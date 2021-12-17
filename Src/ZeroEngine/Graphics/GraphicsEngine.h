#pragma once

#define VK_USE_PLATFORM_WIN32_KHR
#include <string>
#include <vector>
#include <vulkan\vulkan.hpp>
#include "..\Windows\ZeroWindow.h"
#include "VulkanSetup\ZeroVkDebug.h"
#include "VulkanSetup\ZeroVkPhysicalDevice.h"
#include "VulkanSetup\ZeroVkLogicalDevice.h"
namespace ZeroEngine
{
	class GraphicsEngine
	{
#ifdef NDEBUG
		const bool m_enableValidationLayers = false;
#else
		const bool m_enableValidationLayers = true;
#endif   


		const std::vector<const char*> validationLayers = {
			"VK_LAYER_KHRONOS_validation"
		};

		std::vector<const char*> requiredInstanceExtension
		{
			"VK_EXT_debug_report",
			VK_KHR_SURFACE_EXTENSION_NAME, 
			VK_KHR_WIN32_SURFACE_EXTENSION_NAME 
		};

		VkInstance m_instance;
		ZeroWindow m_window;
		ZeroVkDebug m_debug;
		ZeroVkPhysicalDevice m_physicalDevice;
		ZeroVkLogicalDevice m_logicalDevice;

		static std::vector<char> ReadShaderFile(const std::string& _path);

		void CreateInstance();
		bool CheckValidationLayerSupport();

		std::vector<const char*> GetRequiredExtensions();


	public:
		GraphicsEngine();
		bool WindowProcessMessage();
		~GraphicsEngine();
	};
}