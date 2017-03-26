include(FindPackageHandleStandardArgs)

find_path(
    GLFW_INCLUDE_DIRS
    NAMES
        GLFW/glfw3.h
    PATHS
        /usr/include
        /usr/local/include
)

find_library(
    GLFW_LIBRARIES
    NAMES
        glfw
    PATHS
        /usr/lib64
        /usr/lib
        /usr/local/lib64
        /usr/local/lib
)

find_package_handle_standard_args(
    GLFW
    DEFAULT_MSG
    GLFW_INCLUDE_DIRS GLFW_LIBRARIES
)
