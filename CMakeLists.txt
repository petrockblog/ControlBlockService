cmake_minimum_required(VERSION 2.8.5)

project(ControlBlockService)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")
set(EXECUTABLE_NAME "controlblock")

include_directories(src/controlblock)
include_directories(src/lib/bcm2835-1.55/src)
include_directories(src/lib/jsoncpp/include)

add_subdirectory(src/lib/jsoncpp)
add_subdirectory(src/lib/bcm2835-1.55/src)
add_subdirectory(src/controlblock/app)
add_subdirectory(src/controlblock/config)
add_subdirectory(src/controlblock/hal)
add_subdirectory(src/controlblock/gamepads)

add_executable(${EXECUTABLE_NAME} "src/controlblock/main.cpp")
target_link_libraries(${EXECUTABLE_NAME} controlblock-app bcm2835 controlblock-config controlblock-hal controlblock-gamepads)

install(FILES ${CMAKE_BINARY_DIR}/${EXECUTABLE_NAME} DESTINATION /usr/bin
        PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
        GROUP_EXECUTE GROUP_READ
        )
install(FILES ${CMAKE_BINARY_DIR}/../supplementary/controlblockconfig.cfg DESTINATION /etc
        PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
        GROUP_READ
        )

add_custom_target(uninstall
        "${CMAKE_COMMAND}" -P "${CMAKE_SOURCE_DIR}/scripts/uninstall.cmake"
        )

add_custom_target(installservice
        COMMAND chmod +x insertLine.sh
        COMMAND chmod +x controlblockservice
        COMMAND ./insertLine.sh
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/scripts
        COMMENT "Installing service."
        )

add_custom_target(uninstallservice
        COMMAND /etc/init.d/controlblockservice stop
        COMMAND update-rc.d controlblockservice remove
        COMMAND rm /etc/init.d/controlblockservice
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/../scripts
        COMMENT "Uninstalling service."
        )

