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

const bool JsonConfig::isset_config_path() {
	return PluginFolder::isset_folder_path();
}

const bool JsonConfig::isset_config() {
	return std::filesystem::exists("plugins/LootBag/items.json");
}

const bool JsonConfig::check_config_correct() {
	for (const auto& x : get_config()) {
		if (x.empty()) {
			logger.error("Предмет не может быть пуст. Он должен содержать айди и количество!");
			return false;
		}
		if (!x["id"].is_string()) {
			logger.error("Айди предметов должно быть в виде строки!");
			return false;
		}
		if (!x["count"].is_number() || !x["count"].is_number_integer()) {
			logger.error("Количество предметов должно быть целочисленного типа!");
			return false;
		}
	}
	return true;
}

const void JsonConfig::init() {
	if (!isset_config_path()) {
		logger.info("Папка LootBag не существует. Создаю...");
		PluginFolder::create_folder();
		logger.info("Папка успешно создана.");
		logger.info("Создаю конфиг items.json.");
		if (!create_file())
			logger.error("Проблемы с созданием конфига. Проверьте права на запись файла.");
		else
			logger.info("Файл items.json успешно создан!");
	}
	else if (!isset_config()) {
		logger.info("Не найден конфиг items.json. Создаю новый...");
		if (!create_file())
			logger.error("Проблемы с созданием конфига. Проверьте права на запись файла.");
		else
			logger.info("Файл items.json успешно создан!");
	}
	set_config();
	check_config_correct() ? logger.info("Конфиг-файл настроен правильно. Плагин работает!") :
		logger.error("В конфиг-файле были найдены ошибки. Пока Вы их не исправите, код не будет работать!");
}

const bool PluginFolder::contains_in_plugin_folder(std::string name) {
	return std::filesystem::exists("plugins/LootBag/" + name + ".lb");
}

void PluginFolder::set_in_plugin_folder(std::string name) {
	std::ofstream file("plugins/LootBag/" + name + ".lb");
	if (!file) {
		file.close();
		logger.error("Невозможно записать файл игрока.");
	}
	file.close();
}

void PluginFolder::create_folder() {
	std::filesystem::create_directories("plugins/LootBag");
}

const bool PluginFolder::isset_folder_path() {
	return std::filesystem::exists("plugins/LootBag");
}
