include(FindPackageHandleStandardArgs)

find_path(
    GLM_INCLUDE_DIRS
    NAMES
        glm/glm.hpp
    PATHS
        /usr/include
        /usr/local/include
)

set(GLM_LIBRARIES)

find_package_handle_standard_args(
    GLM
    DEFAULT_MSG
    GLM_INCLUDE_DIRS
)
