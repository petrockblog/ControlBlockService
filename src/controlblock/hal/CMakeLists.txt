add_library(controlblock-hal STATIC
		GPIO.cpp
        mcp23017pi.cpp
        )

target_link_libraries(controlblock-hal bcm2835)
