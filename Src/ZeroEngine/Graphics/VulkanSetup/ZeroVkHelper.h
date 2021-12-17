#pragma once

#include <vulkan\vulkan.hpp>
#include "QueueFamilyIndices.h"
#include "SwapChainSupportDetails.h"
namespace ZeroEngine
{
	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice _device,VkSurfaceKHR _surface);

	SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice _device, VkSurfaceKHR _surface);
}