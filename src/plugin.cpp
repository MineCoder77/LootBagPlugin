#include "pch.hpp"

void PluginInit() {

	EventHandler& handler = EventHandler::get_instance();
	handler.init();

	JsonConfig& config = JsonConfig::get_instance();
	config.init();
}
