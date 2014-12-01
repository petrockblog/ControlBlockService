#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

#include "ControlBlockConfiguration.h"

ControlBlockConfiguration::ControlBlockConfiguration() : gamepadType(GAMEPAD_ARCADE), 
	doShutdown(SHUTDOWN_ACTIVATED)
{
}

ControlBlockConfiguration::~ControlBlockConfiguration() 
{
}

void ControlBlockConfiguration::initialize() 
{
	try {
		Json::Value root;   // will contains the root value after parsing.
		Json::Reader reader;

		std::ifstream t("/etc/controlblockconfig.cfg");
		std::string config_doc((std::istreambuf_iterator<char>(t)),
		                 		std::istreambuf_iterator<char>());

		bool parsingSuccessful = reader.parse( config_doc, root );
		if ( !parsingSuccessful ) {
		    // report to the user the failure and their locations in the document.
		    std::cout  << "Failed to parse configuration\n"
		               << reader.getFormattedErrorMessages();
		    return;
		}

		std::string configvalue = root["input"]["gamepadtype"].asString();
		if (configvalue.compare("arcade") == 0) {
			gamepadType = GAMEPAD_ARCADE;
		} else if (configvalue.compare("mame") == 0) {
			gamepadType = GAMEPAD_MAME;
		} else if (configvalue.compare("snes") == 0) {
			gamepadType = GAMEPAD_SNES;
		}
		std::cout << "Read configuration: gamepadtype = " << gamepadType << std::endl;

		bool configboolean = root["powerswitch"]["activated"].asBool();
		if (configboolean) {
			doShutdown = SHUTDOWN_ACTIVATED;
		} else if (configvalue.compare("snes") == 0) {
			doShutdown = SHUTDOWN_DEACTIVATED;
		}
		std::cout << "Read configuration: doShutdown = " << doShutdown << std::endl;
	} catch (int errno) {
		std::cout << "Error while initializing ControlBlockConfiguration instance. Error number: " << errno << std::endl;
	}
}

ControlBlockConfiguration::GamepadType_e ControlBlockConfiguration::getGamepadType() const  {
	return gamepadType;
}

ControlBlockConfiguration::ShutdownType_e ControlBlockConfiguration::getShutdownActivation() const {
	return doShutdown;
}
