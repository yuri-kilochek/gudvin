#include <stdexcept>
#include <iostream>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "config.hxx"
#include "vk/enumerate_instance_layer_properties.hxx"
#include "vk/enumerate_instance_extension_properties.hxx"
#include "vk/instance.hxx"
#include "vk/handle.hxx"
#include "scope_guard.hxx"

namespace gudvin {
    void main()
    {
        std::cout << "gudvin v" << GUDVIN_VERSION_MAJOR << "." << GUDVIN_VERSION_MINOR << "." << GUDVIN_VERSION_PATCH << "\n";

        if (!glfwInit()) {
            throw new std::runtime_error("glfwInit() failed");
        }
        scope_guard glfw_guard = [&]{ glfwTerminate(); };

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        auto const window = glfwCreateWindow(
            800, 600, "Vulkan window", nullptr, nullptr);
        if (!window) {
            throw new std::runtime_error("glfwCreateWindow() failed");
        }
        scope_guard window_guard = [&]{ glfwDestroyWindow(window); };

        std::cout << "core extensions:" << "\n";
        for (auto&& extension : vk::enumerate_instance_extension_properties(nullptr)) {
            std::cout << "\t" << extension.extensionName << "\n";
        }
        std::cout << "layers:" << "\n";
        for (auto&& layer : vk::enumerate_instance_layer_properties()) {
            std::cout << "\t" << layer.layerName << ": " << layer.description << "\n";
            std::cout << "\t\t" << "layer extensions:" << "\n";
            for (auto&& extension : vk::enumerate_instance_extension_properties(layer.layerName)) {
                std::cout << "\t\t\t" << extension.extensionName << "\n";
            }
        }

        VkInstanceCreateInfo info{VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};
        //info.enabled_layer_names.emplace("foobaf");
        auto instance = vk::create_instance(&info, nullptr);
        scope_guard instance_guard = [&]{
            vk::destroy_instance(instance, nullptr);
        };

        glm::mat4 matrix;
        glm::vec4 vec;
        vec * matrix;

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
