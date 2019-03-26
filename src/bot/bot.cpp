
#include <cstdio>
#include <iostream>
#include <json.hpp>
#include <bot/bot.hpp>
#include <config.h>

namespace bot {

	using json = nlohmann::json;

	bot::bot(const char *in) {
		this->in = in;
		this->d  = json::parse(std::string(in));
	}

	void bot::exec() {
		printf("%s\n", std::string(this->d["hello"]).c_str());
	}
}
