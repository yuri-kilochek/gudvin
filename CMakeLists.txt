cmake_minimum_required(VERSION 3.7)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

add_executable(
    gudvin
    
    src/main.cpp
)

find_package(GLM REQUIRED)
target_include_directories(gudvin PRIVATE ${GLM_INCLUDE_DIRS})
target_link_libraries(gudvin PRIVATE ${GLM_LIBRARIES})

find_package(GLFW REQUIRED)
target_include_directories(gudvin PRIVATE ${GLFW_INCLUDE_DIRS})
target_link_libraries(gudvin PRIVATE ${GLFW_LIBRARIES})

find_package(Boost REQUIRED)
target_include_directories(gudvin PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(gudvin PRIVATE ${Boost_LIBRARIES})

find_package(Vulkan REQUIRED)
target_include_directories(gudvin PRIVATE ${Vulkan_INCLUDE_DIRS})
target_link_libraries(gudvin PRIVATE ${Vulkan_LIBRARIES})
