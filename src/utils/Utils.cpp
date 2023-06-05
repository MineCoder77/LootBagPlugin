#include "header/Utils.hpp"
#include <string>

JsonConfig JsonConfig::instance = JsonConfig();

JsonConfig& JsonConfig::get_instance() {
	return instance;
}

bool JsonConfig::contains_items() {
	return get_config() != NULL;
}

nlohmann::json JsonConfig::get_config() {
	return JsonConfig::json_config;
}

void JsonConfig::set_config() {
	std::ifstream file("plugins/LootBag/items.json");
	JsonConfig::json_config = nlohmann::json::parse(file);
	file.close();
}

bool JsonConfig::create_file() {
	nlohmann::json j;
	j["sword"]["id"] = "minecraft:stone_sword";
	j["sword"]["count"] = 1;
	j["apple"]["id"] = "minecraft:apple";
	j["apple"]["count"] = 16;
	j["oak_log"]["id"] = "minecraft:log";
	j["oak_log"]["count"] = 32;
	std::ofstream file("plugins/LootBag/items.json");
	if (!file) {
		file.close();
		return false;
	}
	file << std::setw(4) << j << std::endl;
	file.close();
	return true;
}

bool JsonConfig::isset_config_path() {
	return PluginFolder::isset_folder_path();
}

bool JsonConfig::isset_config() {
	return std::filesystem::exists("plugins/LootBag/items.json");
}

void JsonConfig::init() {
	if (!isset_config_path()) {
		logger.info("Папка LootBag не существует. Создаю...");
		PluginFolder::create_folder();
		logger.info("Папка успешно создана.");
		logger.info("Создаю конфиг items.json.");
		if (!create_file())
			throw std::runtime_error("Проблемы с созданием конфига. Проверьте права на запись файла.");
		else
			logger.info("Файл items.json успешно создан!");
	}
	else if (!isset_config()) {
		logger.info("Не найден конфиг items.json. Создаю новый...");
		if (!create_file())
			throw std::runtime_error("Проблемы с созданием конфига. Проверьте права на запись файла.");
		else
			logger.info("Файл items.json успешно создан!");
	}
	set_config();
}

bool PluginFolder::contains_in_plugin_folder(std::string name) {
	return std::filesystem::exists("plugins/LootBag/" + name + ".lb");
}

void PluginFolder::set_in_plugin_folder(std::string name) {
	std::ofstream file("plugins/LootBag/" + name + ".lb");
	if (!file) {
		file.close();
		throw std::runtime_error("Невозможно записать файл игрока.");
	}
	file.close();
}

void PluginFolder::create_folder() {
	std::filesystem::create_directories("plugins/LootBag");
}

bool PluginFolder::isset_folder_path() {
	return std::filesystem::exists("plugins/LootBag");
}