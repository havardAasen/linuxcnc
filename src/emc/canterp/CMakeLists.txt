add_library(canterp SHARED canterp.cc)
target_link_libraries(canterp
        PRIVATE
        rs274ngc
        libnml_posemath
        motion_component
        )

set_property(TARGET canterp PROPERTY POSITION_INDEPENDENT_CODE ON)
