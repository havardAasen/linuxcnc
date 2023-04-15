add_library(motion_task
        emcmotglb.c
        usrmotintf.cc
        emcmotutil.c
        dbuf.c
        stashf.c
)
get_uspace_config(motion_task)
target_include_directories(motion_task PUBLIC .)
target_link_libraries(motion_task
        PRIVATE
        libnml_posemath
        emc_nmlintf
        )

add_library(motion_component
        command.c
        control.c
        simple_tp.c
        emcmotutil.c
        stashf.c
        dbuf.c
        )
target_link_libraries(motion_component
        PRIVATE
        hal
        PUBLIC
        trajectoryplanner
        )
target_include_directories(motion_component PUBLIC .)
get_uspace_config(motion_component)

build_component(NAME motmod
        SOURCES
        motion.c
        homing.c
        LIBS ulapi hal motion_component libnml_posemath emc_kinematics_cubic trajectoryplanner emc_nmlintf
        )
