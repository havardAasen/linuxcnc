add_library(posemath
        SHARED
        _posemath.c
        gomath.c
        sincos.c)
target_include_directories(posemath PUBLIC .)
get_uspace_config(posemath)

set_property(TARGET posemath PROPERTY POSITION_INDEPENDENT_CODE ON)

# some sources don't use the shared library
# as i don't know how they use it, i just add them as separate targets
add_library(libnml_posemath
        _posemath.c
        gomath.c
        sincos.c)
target_include_directories(libnml_posemath PUBLIC .)
get_uspace_config(posemath)

set_property(TARGET posemath PROPERTY POSITION_INDEPENDENT_CODE ON)
