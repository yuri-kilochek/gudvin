cmake_minimum_required(VERSION 3.8)

project(gudvin VERSION 0.0.0)

add_executable(program
    src/main.cxx
)

set_target_properties(program PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}
    DEBUG_POSTFIX _d

    VERSION ${PROJECT_VERSION}

    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS OFF
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(program PRIVATE
        -Wall
        -Wextra
        -pedantic
        -Wfatal-errors
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(program PRIVATE
        /Wall
    )
endif()

configure_file("src/config.hxx.in" "src/config.hxx")
target_include_directories(program PRIVATE "${CMAKE_BINARY_DIR}/src")

find_package(Boost REQUIRED)
target_link_libraries(program Boost::boost)

find_package(glm REQUIRED)
target_compile_definitions(program PUBLIC
    GLM_FORCE_DEPTH_ZERO_TO_ONE
)
target_link_libraries(program glm)

find_package(glfw3 REQUIRED)
target_compile_definitions(program PUBLIC
    GLFW_INCLUDE_NONE
    GLFW_INCLUDE_VULKAN
)
target_link_libraries(program glfw)

find_package(Vulkan REQUIRED)
target_link_libraries(program Vulkan::Vulkan)
