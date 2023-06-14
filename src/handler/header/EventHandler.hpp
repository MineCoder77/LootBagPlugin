#pragma once

#include <llapi/EventAPI.h>
#include <llapi/mc/ItemStack.hpp>
#include <llapi/mc/Item.hpp>
#include <llapi/mc/ColorFormat.hpp>
#include <llapi/mc/Player.hpp>
#include "../../utils/header/Utils.hpp"

class EventHandler {
private:
	EventHandler() {}
	static EventHandler instance;
	void on_player_use();
	void on_player_join();
	EventHandler(const EventHandler&) = delete;
	EventHandler& operator=(EventHandler&) = delete;
public:
	void init();
	static EventHandler& get_instance();
};
