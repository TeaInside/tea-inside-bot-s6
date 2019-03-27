
#include <iostream>
#include <bot/bot.hpp>

using json = nlohmann::json;

bot::bot::bot(const char *in) {
	this->_in = in;
	this->in  = json::parse(std::string(in));
	this->chat_id = this->in["message"]["chat"].value("id", -1L);
	this->text = this->in["message"].value("text", "");

	if (this->text != "") {
		this->msg_type = msg_text;
	}

	std::string chat_type = this->in["message"]["chat"].value("type", "");
	if (!chat_type.compare("private")) {
		this->chat_type = chat_private;
	} else {
		this->chat_type = chat_group;
	}

}

void bot::bot::exec() {
	if (this->msg_type == msg_text) {
		this->dispatch();
	}
}
