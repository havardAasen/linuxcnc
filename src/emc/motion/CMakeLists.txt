add_library(motion_task
        emcmotglb.c
        usrmotintf.cc
        emcmotutil.c
        dbuf.c
        stashf.c
)
get_uspace_config(motion_task)
target_include_directories(motion_task PUBLIC .)

add_library(motion_component
        motion.c
        command.c
        control.c
        homing.c
        simple_tp.c
        emcmotutil.c
        stashf.c
        dbuf.c
        )
target_include_directories(motion_component PUBLIC .)
get_uspace_config(motion_component)
