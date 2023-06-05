#pragma once

#include <nlohmann/json.hpp>
#include <llapi/LoggerAPI.h>

extern Logger logger;

class JsonConfig {
private:
	nlohmann::json json_config;
	bool create_file();
	bool isset_config_path();
	bool isset_config();
	void set_config();
	static JsonConfig instance;
	JsonConfig() {}
	JsonConfig(const JsonConfig&) = delete;
	JsonConfig& operator=(JsonConfig&) = delete;
public:
	void init();
	static JsonConfig& get_instance();
	nlohmann::json get_config();
	bool contains_items();
};

namespace PluginFolder {
	bool contains_in_plugin_folder(std::string name);
	void set_in_plugin_folder(std::string name);
	void create_folder();
	bool isset_folder_path();
}