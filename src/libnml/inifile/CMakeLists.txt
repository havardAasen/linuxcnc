#previously this was linuxcncini.so
add_library(libnml_inifile SHARED inifile.cc)
target_include_directories(libnml_inifile PUBLIC .)
set_property(TARGET libnml_inifile PROPERTY POSITION_INDEPENDENT_CODE ON)

add_executable(libnml_inivar inivar.cc)
target_include_directories(libnml_inivar PUBLIC .)
target_link_libraries(libnml_inivar PRIVATE libnml_inifile)