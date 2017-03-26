cmake_minimum_required(VERSION 3.7)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -Wall -pedantic")
endif()

add_executable(
    gudvin
    
    src/main.cpp

    src/vk/error.cpp
)

find_package(GLM REQUIRED)
target_compile_definitions(gudvin PRIVATE GLM_FORCE_DEPTH_ZERO_TO_ONE)
target_include_directories(gudvin SYSTEM PRIVATE ${GLM_INCLUDE_DIRS})

find_package(GLFW REQUIRED)
target_compile_definitions(gudvin PRIVATE GLFW_INCLUDE_VULKAN)
target_include_directories(gudvin SYSTEM PRIVATE ${GLFW_INCLUDE_DIRS})
target_link_libraries(gudvin PRIVATE ${GLFW_LIBRARIES})

find_package(Boost REQUIRED)
target_include_directories(gudvin SYSTEM PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(gudvin PRIVATE ${Boost_LIBRARIES})

find_package(Vulkan REQUIRED)
target_include_directories(gudvin SYSTEM PRIVATE ${Vulkan_INCLUDE_DIRS})
target_link_libraries(gudvin PRIVATE ${Vulkan_LIBRARIES})
