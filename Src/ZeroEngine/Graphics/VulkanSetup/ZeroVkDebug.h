#pragma once

#include <vulkan\vulkan.hpp>
namespace ZeroEngine
{
	class ZeroVkDebug
	{
		VkDebugUtilsMessengerEXT m_debugMessenger;

		VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
			const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
			const VkAllocationCallbacks* pAllocator,
			VkDebugUtilsMessengerEXT* pDebugMessenger);

		

		static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData
		);

		void DestroyDebugUtilsMessengerEXT(VkInstance instance,
			VkDebugUtilsMessengerEXT debugMessenger,
			const VkAllocationCallbacks* pAllocator);
		
	public:
		ZeroVkDebug();

		void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& _createInfo);

		void SetupDebugMessenger(
			const VkInstance& _instance, 
			const bool _enableValidationLayers);

		void DestroyDebugUtlisMessenger(
			const VkInstance& _instance,
			const bool _enableValidationLayers);
	};
}