#include "header/EventHandler.hpp"

const void give_kit(Player* player);

inline EventHandler EventHandler::instance = EventHandler();

inline EventHandler& EventHandler::get_instance() {
	return instance;
}

inline void EventHandler::on_player_use() {
	srand(time(NULL));
	Event::PlayerUseItemEvent::subscribe([](const Event::PlayerUseItemEvent& event) {
		auto item_stack = event.mItemStack;
		Player* player = event.mPlayer;
		if (item_stack->getTypeName() == "lb:lootbag") {
			player->sendTitlePacket(ColorFormat::YELLOW + "Набор открыт!", TitleType::SetTitle, 20, 20, 20);
			give_kit(player);
			player->addExperience(rand() % 21);
			player->sendSpawnParticleEffectPacket(player->getPosition() + 0.5, 0, "minecraft:villager_happy");
			player->clearItem(item_stack->getItem()->getFullItemName(), 1);
		}
		return true;
	});
}

inline void EventHandler::on_player_join() {
	Event::PlayerJoinEvent::subscribe([](const Event::PlayerJoinEvent& event) {
		Player* player = event.mPlayer;
		if (!PluginFolder::contains_in_plugin_folder(player->getRealName())) {
			ItemStack* item = ItemStack::create("lb:lootbag");
			player->giveItem(item);
			delete item;
			PluginFolder::set_in_plugin_folder(player->getRealName());
		}
		return true;
	});
}

inline void give_kit(Player* player) {
	if (JsonConfig::get_instance().contains_items()) {
		for (const auto& x : JsonConfig::get_instance().get_config())
			player->giveItem(std::string(x["id"]), short(x["count"]));
	}
	else
		logger.error("Необходим минимум 1 предмет в наборе: в вашем конфиг-файле нет ни 1 предмета.");
}

inline void EventHandler::init() {
	on_player_use();
	on_player_join();
}
