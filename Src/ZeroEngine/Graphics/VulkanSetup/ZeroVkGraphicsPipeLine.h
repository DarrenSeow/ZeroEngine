#pragma once

#include <vector>
#include <string>
namespace ZeroEngine
{
	class ZeroVkGraphicsPipeLine
	{
		VkPipelineLayout m_pipelineLayout;
		VkPipeline m_graphicsPipeline;

		VkShaderModule CreateShaderModule(const std::vector<char>& _code, VkDevice _device);
	public:

		void CreateGraphicsPipeLine(
			const std::string& _vert, 
			const std::string& _frag, 
			VkDevice _device,
			VkRenderPass _renderPass,
			VkExtent2D _swapChainExtent);

		VkPipeline GetPipeLine();
		void DestroyGraphicsPipeLineLayout(VkDevice _device);
		void DestroyGraphicsPipeLine(VkDevice _device);

	};
}