
#include <utils.hpp>
#include <bot/bot.hpp>
#include <lang/en/start.hpp>

using json = nlohmann::json;
using namespace lang::en;

void bot::bot::dispatch() {

	if (!this->text.compare("/start")) {
		#include "responses/start.cxx"
	}

}
