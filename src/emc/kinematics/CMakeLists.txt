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

add_library(emc_kinematics_cubic cubic.c)
target_link_libraries(emc_kinematics_cubic
        PUBLIC
        libnml_posemath)
target_include_directories(emc_kinematics_cubic PUBLIC .)
get_uspace_config(emc_kinematics_cubic)

#kinematics components
build_component(NAME trivkins SOURCES trivkins.c kins_util.c LIBS ulapi hal motion_component libnml_posemath emc_nmlintf emc_kinematics_cubic trajectoryplanner)
build_component(NAME maxkins SOURCES maxkins.c LIBS ulapi hal emc_nmlintf libnml_posemath)
build_component(NAME rotatekins SOURCES rotatekins.c LIBS ulapi hal emc_nmlintf libnml_posemath)
build_component(NAME tripodkins SOURCES tripodkins.c LIBS ulapi hal emc_nmlintf libnml_posemath)
build_component(NAME corexykins SOURCES corexykins.c LIBS ulapi hal emc_nmlintf libnml_posemath motion_component emc_kinematics_cubic)
build_component(NAME lineardeltakins SOURCES lineardeltakins.c LIBS ulapi hal)
build_component(NAME rotarydeltakins SOURCES rotarydeltakins.c LIBS ulapi hal)
build_component(NAME rosekins SOURCES rosekins.c LIBS ulapi hal)
build_component(NAME scorbot-kins SOURCES scorbot-kins.c LIBS ulapi hal emc_nmlintf libnml_posemath)
build_component(NAME pentakins SOURCES pentakins.c LIBS ulapi hal emc_nmlintf libnml_posemath)
