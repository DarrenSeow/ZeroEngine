#pragma once


#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL

#include <vulkan\vulkan.hpp>
#include <glm.hpp>
#include <gtx\hash.hpp>
#include <array>

namespace ZeroEngine
{
    struct Vertex {
        glm::vec3 pos;
        glm::vec3 color;
        glm::vec3 normal;
        glm::vec2 texCoord;
        static VkVertexInputBindingDescription GetBindingDescription();

        static std::array<VkVertexInputAttributeDescription, 4> GetAttributeDescriptions();

        bool operator==(const Vertex& other) const;
    };
}

namespace std {
    template<> struct hash<ZeroEngine::Vertex> {
        size_t operator()(ZeroEngine::Vertex const& vertex) const {
            return ((hash<glm::vec3>()(vertex.pos) ^ (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^ (hash<glm::vec2>()(vertex.texCoord) << 1);
        }
    };
}