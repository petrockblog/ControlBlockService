add_library(controlblock-config STATIC
        ControlBlockConfiguration.cpp
        )

target_link_libraries(controlblock-config jsoncpp_lib_static)
