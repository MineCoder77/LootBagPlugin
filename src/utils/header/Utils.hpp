#pragma once

#include <nlohmann/json.hpp>
#include <llapi/LoggerAPI.h>

extern Logger logger;

class JsonConfig {
private:
	nlohmann::json json_config;
	bool create_file();
	const bool isset_config_path();
	const bool isset_config();
	void set_config();
	static JsonConfig instance;
	JsonConfig() {}
	JsonConfig(const JsonConfig&) = delete;
	JsonConfig& operator=(JsonConfig&) = delete;
	const bool check_config_correct();
public:
	const void init();
	static JsonConfig& get_instance();
	nlohmann::json get_config();
	bool contains_items();
};

namespace PluginFolder {
	const bool contains_in_plugin_folder(std::string name);
	void set_in_plugin_folder(std::string name);
	void create_folder();
	const bool isset_folder_path();
}
