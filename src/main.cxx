#include <stdexcept>
#include <iostream>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "config.hxx"
#include "scope_guard.hxx"
#include "vk/enumerate_instance_layer_properties.hxx"
#include "vk/enumerate_instance_extension_properties.hxx"
#include "vk/instance.hxx"
#include "vk/enumerate_physical_devices.hxx"
#include "glfw/error.hxx"

namespace gudvin {
    void main()
    {
        std::cout << "gudvin v" << GUDVIN_VERSION_MAJOR << "." << GUDVIN_VERSION_MINOR << "." << GUDVIN_VERSION_PATCH << "\n";

        if (!glfwInit()) { glfw::check_error(); }
        scope_guard glfw_guard = [&]{
            glfwTerminate();
            glfw::suppress_error();
        };

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfw::check_error();
        auto const window =
            glfwCreateWindow(800, 600, "gudvin", nullptr, nullptr);
        if (!window) { glfw::check_error(); }
        scope_guard window_guard = [&]{
            glfwDestroyWindow(window);
            glfw::suppress_error();
        };

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
        auto instance = vk::create_instance(&info, nullptr);
        scope_guard instance_guard = [&]{
            vk::destroy_instance(instance, nullptr);
        };

        std::cout << "physical devices:\n";
        for (auto physical_device : vk::enumerate_physical_devices(instance.value())) {
            VkPhysicalDeviceProperties properties;
            vkGetPhysicalDeviceProperties(physical_device, &properties);
            std::cout << "\t" << properties.deviceName << "\n";
        }

        glm::mat4 matrix;
        glm::vec4 vec;
        vec * matrix;

        while (!glfwWindowShouldClose(window)) {
            glfw::check_error();
            glfwPollEvents();
            glfw::check_error();
        }
        glfw::check_error();
    }
} /* namespace gudvin */

auto main()
    -> int
{
    gudvin::main();
}
