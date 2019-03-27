
#include <cstdio>
#include <utils.hpp>
#include <bot/bot.hpp>
#include <curl/curl.h>

using json = nlohmann::json;

bot::bot::bot(const char *in) {
	this->_in = in;
	this->in  = json::parse(std::string(in));
	this->chat_id = this->in["message"]["chat"].value("id", -1L);
	this->user_id = this->in["message"]["from"].value("id", -1L);

	#ifdef ESTEH_DEBUG
	this->validate();
	#endif

	this->first_name = this->in["message"]["from"].value("first_name", "");
	this->last_name = this->in["message"]["from"].value("last_name", "");

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

std::string bot::bot::lang_bind(std::string str) {

	if (!this->has_been_bind) {
		std::string name = this->first_name + std::string(this->last_name != "" ? " "+this->last_name : "");
		htmlspecialchars(name);
		this->namelink = "<a href=\"tg://user?id="+std::to_string(this->user_id)+"\">"+name+"</a>";
	}

	replace(str, "{namelink}", this->namelink);
	return str;
}

CURLcode bot::bot::exe(const char *method, const char *body, std::string *response) {

	char *_url = (char *)malloc(sizeof("https://api.telegram.org/bot" TOKEN "/") - 1 + strlen(method));
	sprintf(_url, "https://api.telegram.org/bot" TOKEN "/%s", method);

	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, _url);
		if (response != nullptr) {
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, this->curl_write_callback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
		} else {
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, nullptr);
		}
		curl_easy_setopt(curl, CURLOPT_POST, true);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);

		#ifdef ESTEH_DEBUG
		curl_easy_setopt(curl, CURLOPT_VERBOSE, true);
		#endif

		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}

	return res;
}

#ifdef ESTEH_DEBUG
void bot::bot::validate() {
	if (this->chat_id == -1L) {
		printf("Couldn't get chat_id (exit)\n");
		exit(0);
	}

	if (this->user_id == -1L) {
		printf("Couldn't get user_id (exit)\n");
		exit(0);
	}
}
#endif