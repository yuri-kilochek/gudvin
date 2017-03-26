#include <stdexcept>
#include <iostream>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "DEFER.hpp"

namespace gudvin {
    void main()
    {
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
