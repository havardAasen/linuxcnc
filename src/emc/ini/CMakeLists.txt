add_library(emc_ini
        emcIniFile.cc
        iniaxis.cc
        inijoint.cc
        initraj.cc
        inihal.cc
        inispindle.cc
        )
target_include_directories(emc_ini PUBLIC .)
target_link_libraries(emc_ini PUBLIC emc_nmlintf hal)
get_uspace_config(emc_ini)