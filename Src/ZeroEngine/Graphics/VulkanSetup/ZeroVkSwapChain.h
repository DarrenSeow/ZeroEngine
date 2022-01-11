#pragma once

#include <vulkan\vulkan.hpp>
#include "..\Windows\ZeroWindow.h"
#include "ZeroVkGraphicsPipeLine.h"

namespace ZeroEngine
{
	class ZeroVkSwapChain
	{

		VkSwapchainKHR m_swapChain;
		std::vector<VkImage> m_swapChainImages;
		VkFormat m_swapChainImageFormat;
		VkExtent2D m_swapChainExtent;
		std::vector<VkImageView> m_swapChainImageViews;
		std::vector<VkFramebuffer> m_swapChainFrameBuffers;

		VkRenderPass m_renderPass;

		ZeroVkGraphicsPipeLine m_graphicsPipeLine;

		VkCommandPool m_commandPool;
		std::vector<VkCommandBuffer> m_commandBuffers;



		VkQueue m_graphicsQueue;
		VkQueue m_presentQueue;

		std::vector<VkSemaphore> m_imageAvailableSemaphores;
		std::vector<VkSemaphore> m_renderFinishedSemaphores;
		std::vector<VkFence> m_inFlightFences;
		std::vector<VkFence> m_imagesInFlight;


		size_t m_currentFrame = 0;

		const int MAX_FRAMES_IN_FLIGHT = 1;
		VkSurfaceFormatKHR ChooseSwapSurfaceFormat(
			const std::vector<VkSurfaceFormatKHR>& _availableFormats);
		
		VkPresentModeKHR ChooseSwapPresentMode(
			const std::vector<VkPresentModeKHR>& _availablePresentModes);
		
		VkExtent2D ChooseSwapExtent(
			const VkSurfaceCapabilitiesKHR& _capabilities, 
			const ZeroWindow& _window);

		VkImageView CreateImageView(
			VkDevice _device, 
			VkImage _image, 
			VkFormat _format, 
			VkImageAspectFlags _aspectFlag);

		VkFormat FindDepthFormat(VkPhysicalDevice _physicalDevice);

		VkFormat FindSupportedFormat(VkPhysicalDevice _physicalDevice, const std::vector<VkFormat>& candidates,
			VkImageTiling tiling, 
			VkFormatFeatureFlags features);

		VkAttachmentDescription CreateAttachmentDescription(
			VkFormat _format,
			VkSampleCountFlagBits _countFlagBits,
			VkAttachmentLoadOp _loadOp,
			VkAttachmentStoreOp _storeOp,
			VkAttachmentLoadOp _stencilLoadOp,
			VkAttachmentStoreOp _stencilStoreOp,
			VkImageLayout _initialLayout,
			VkImageLayout _finalLayout
		);
		
	public:

		void CreateGraphicsPipeLine(VkDevice _device);
		VkExtent2D GetSwapChainExtent();
		VkRenderPass GetRenderPass();
		void CreateSwapChain(VkPhysicalDevice _physicalDevice, 
			VkDevice _device, 
			VkSurfaceKHR _surface, 
			const ZeroWindow& _window);
		
		void CreateRenderPass(VkDevice _device,VkPhysicalDevice _physicalDevice);


		void CreateImageViews(VkDevice _device);

		void CleanUpSwapChain(VkDevice _device);

		void CreateFrameBuffers(VkDevice _device);

		void CreateCommandPool(VkDevice _device, VkPhysicalDevice _physicalDevice, VkSurfaceKHR _surface);

		void CreateCommandBuffers(VkDevice _device);
		void DestroyCommandPool(VkDevice _device);


		void DrawFrame(VkDevice _device);
	};
}