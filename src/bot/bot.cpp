
#include <cstdio>
#include <iostream>
#include <json.hpp>
#include <bot/bot.hpp>
#include <config.hpp>

namespace bot {

	using json = nlohmann::json;

	bot::bot(const char *in) {
		this->_in = in;
		this->in  = json::parse(std::string(in));
	}

	void bot::exec() {
		printf("in\n");
		this->chat_id = this->in["message"]["chat"].value("id", -1LL);
		printf("chat_id: %ld\n", this->chat_id);
	}
}
