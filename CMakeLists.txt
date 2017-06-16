cmake_minimum_required(VERSION 3.8)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

project(gudvin VERSION 0.0.0)

add_executable(
    ${PROJECT_NAME}
    
    src/main.cxx
)
set_target_properties(
    ${PROJECT_NAME} PROPERTIES

    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS OFF
)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(
        ${PROJECT_NAME} PRIVATE
        
        -Wall
        -pedantic
        -Wfatal-errors
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(
        ${PROJECT_NAME} PRIVATE
        /Wall
    )
endif()
configure_file(
    "${CMAKE_SOURCE_DIR}/src/config.hxx.in"
    "${CMAKE_BINARY_DIR}/src/config.hxx"
)
target_include_directories(
    ${PROJECT_NAME} SYSTEM PRIVATE
    "${CMAKE_BINARY_DIR}/src"
)

find_package(Boost REQUIRED)
target_include_directories(
    ${PROJECT_NAME} SYSTEM PRIVATE
    ${Boost_INCLUDE_DIRS}
)
target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    ${Boost_LIBRARIES}
)

find_package(GLM REQUIRED)
target_compile_definitions(
    ${PROJECT_NAME} PRIVATE
    GLM_FORCE_DEPTH_ZERO_TO_ONE
)
target_include_directories(
    ${PROJECT_NAME} SYSTEM PRIVATE
    ${GLM_INCLUDE_DIRS}
)

find_package(GLFW REQUIRED)
target_compile_definitions(
    ${PROJECT_NAME} PRIVATE
    GLFW_INCLUDE_VULKAN
)
target_include_directories(
    ${PROJECT_NAME} SYSTEM PRIVATE
    ${GLFW_INCLUDE_DIRS}
)
target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    ${GLFW_LIBRARIES}
)

find_package(Vulkan REQUIRED)
target_include_directories(
    ${PROJECT_NAME} SYSTEM PRIVATE
    ${Vulkan_INCLUDE_DIRS}
)
target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    ${Vulkan_LIBRARIES}
)
