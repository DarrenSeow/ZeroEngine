#pragma once

#define VK_USE_PLATFORM_WIN32_KHR
#include <string>
#include <vector>
#include <vulkan\vulkan.hpp>
#include "..\Windows\ZeroWindow.h"
#include "VulkanSetup\ZeroVkDebug.h"
#include "VulkanSetup\ZeroVkPhysicalDevice.h"
#include "VulkanSetup\ZeroVkLogicalDevice.h"
#include "VulkanSetup\ZeroVkSwapChain.h"

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
		VkSurfaceKHR m_surface;

		ZeroVkDebug m_debug;
		ZeroVkPhysicalDevice m_physicalDevice;
		ZeroVkLogicalDevice m_logicalDevice;
		ZeroVkSwapChain m_frameBuffer;

		static std::vector<char> ReadShaderFile(const std::string& _path);

		void CreateInstance();
		void CreateVkSurface(const ZeroWindow& _window);
		void DestroyVkSurface();
		
		bool CheckValidationLayerSupport();
		
		std::vector<const char*> GetRequiredExtensions();


	public:
		VkDevice GetDevice();
		GraphicsEngine(const ZeroWindow& _window);
		
		void DrawFrame(ZeroWindow& _window);
		~GraphicsEngine();
	};
}