#include "pch.h"
#include "Helpers.h"
#include <istream>
#include <fstream>

namespace ZeroEngine
{
    std::vector<char> ReadFile(const std::string& _path)
    {
        std::ifstream file(_path, std::ios::ate | std::ios::binary);

        if (!file.is_open())
        {
            throw std::runtime_error("failed to open " + _path + " file!");
        }

        size_t fileSize = static_cast<size_t>(file.tellg());
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();

        return buffer;
    }
}