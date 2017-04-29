cmake_minimum_required(VERSION 3.7)

project(gudvin)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -std=c++1z -Wall -pedantic -Wfatal-errors")
endif()

add_executable(
    ${PROJECT_NAME}
    
    src/main.cxx
)

find_package(Boost REQUIRED)
target_include_directories(
    ${PROJECT_NAME} SYSTEM PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(
    ${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})

find_package(GLM REQUIRED)
target_compile_definitions(
    ${PROJECT_NAME} PRIVATE GLM_FORCE_DEPTH_ZERO_TO_ONE)
target_include_directories(
    ${PROJECT_NAME} SYSTEM PRIVATE ${GLM_INCLUDE_DIRS})

find_package(GLFW REQUIRED)
target_compile_definitions(
    ${PROJECT_NAME} PRIVATE GLFW_INCLUDE_VULKAN)
target_include_directories(
    ${PROJECT_NAME} SYSTEM PRIVATE ${GLFW_INCLUDE_DIRS})
target_link_libraries(
    ${PROJECT_NAME} PRIVATE ${GLFW_LIBRARIES})

find_package(Vulkan REQUIRED)
target_include_directories(
    ${PROJECT_NAME} SYSTEM PRIVATE ${Vulkan_INCLUDE_DIRS})
target_link_libraries(
    ${PROJECT_NAME} PRIVATE ${Vulkan_LIBRARIES})
