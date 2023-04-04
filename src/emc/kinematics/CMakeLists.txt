set(GENSERKINS_SOURCES
        ugenserkins.c
        genserfuncs.c)

add_executable(genserkins ${GENSERKINS_SOURCES})
target_link_libraries(genserkins
        PRIVATE
        hal
        posemath
        m)
get_uspace_config(genserkins)

add_library(l_lineardeltakins SHARED lineardeltakins.cc)
target_link_libraries(l_lineardeltakins
        PRIVATE
        ${BOOST_LIBS}
        Python3::Python
        hal
        posemath)
get_uspace_config(l_lineardeltakins)

add_library(l_rotarydeltakins SHARED rotarydeltakins.cc)
target_link_libraries(l_rotarydeltakins
        PRIVATE
        ${BOOST_LIBS}
        Python3::Python
        hal
        posemath)
get_uspace_config(l_rotarydeltakins)
