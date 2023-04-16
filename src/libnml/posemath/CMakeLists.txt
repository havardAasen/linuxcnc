add_library(posemath
        SHARED
        _posemath.c
        gomath.c
        sincos.c)
target_include_directories(posemath PUBLIC .)
target_link_libraries(posemath PUBLIC ulapi)
get_uspace_config(posemath)

set_property(TARGET posemath PROPERTY POSITION_INDEPENDENT_CODE ON)

add_library(libnml_posemath
        _posemath.c
        posemath.cc
        gomath.c
        sincos.c)
target_include_directories(libnml_posemath PUBLIC .)
target_link_libraries(libnml_posemath PUBLIC ulapi)
get_uspace_config(libnml_posemath)

set_property(TARGET posemath PROPERTY POSITION_INDEPENDENT_CODE ON)
