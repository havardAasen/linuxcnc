add_library(trajectoryplanner
        tc.c
        tcq.c
        tp.c
        spherical_arc.c
        blendmath.c
)
target_include_directories(trajectoryplanner PUBLIC .)
target_link_libraries(trajectoryplanner PUBLIC emc_nmlintf emc_kinematics_cubic)
get_uspace_config(trajectoryplanner)
