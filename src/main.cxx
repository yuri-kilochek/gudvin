#include <stdexcept>
#include <iostream>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "config.hxx"
#include "defer.hxx"
#include "vk/enumerate_instance_layer_properties.hxx"
#include "vk/enumerate_instance_extension_properties.hxx"
#include "vk/instance.hxx"

namespace gudvin {
    void main()
    {
        std::cout << "gudvin v" << GUDVIN_VERSION_MAJOR << "." << GUDVIN_VERSION_MINOR << "." << GUDVIN_VERSION_PATCH << "\n";

        if (!glfwInit()) {
            throw new std::runtime_error("glfwInit() failed");
        }
        GUDVIN_DEFER(glfwTerminate());

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        auto const window = glfwCreateWindow(
            800, 600, "Vulkan window", nullptr, nullptr);
        if (!window) {
            throw new std::runtime_error("glfwCreateWindow() failed");
        }
        GUDVIN_DEFER(glfwDestroyWindow(window));

        std::cout << "core extensions:" << "\n";
        for (auto&& extension : vk::enumerate_instance_extension_properties()) {
            std::cout << "\t" << extension.extensionName << "\n";
        }
        std::cout << "layers:" << "\n";
        for (auto&& layer : vk::enumerate_instance_layer_properties()) {
            std::cout << "\t" << layer.layerName << ": " << layer.description << "\n";
            std::cout << "\t\t" << "layer extensions:" << "\n";
            for (auto&& extension : vk::enumerate_instance_extension_properties(std::string(layer.layerName))) {
                std::cout << "\t\t\t" << extension.extensionName << "\n";
            }
        }


        vk::instance_create_info info;
        //info.enabled_layer_names.emplace("foobaf");
        info.prepare();
        auto instance = vk::create_instance(info);
        GUDVIN_DEFER(vk::destroy_instance(instance));


        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        std::cout << extensionCount << " extensions supported" << std::endl;

        glm::mat4 matrix;
        glm::vec4 vec;
        auto test = matrix * vec;

        while(!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }
} /* namespace gudvin */

auto main()
    -> int
{
    gudvin::main();
}
