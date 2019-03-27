
#ifndef BOT_BOT_HPP
#define BOT_BOT_HPP

#include <string>
#include <json.hpp>
#include <stdint.h>
#include <string.h>
#include <config.hpp>
#include <curl/curl.h>

#define MSG_TEXT 1
#define MSG_PHOTO 2

enum _chat_type {
	chat_unknown = 0,
	chat_private = (1 << 0),
	chat_group = (1 << 1)
};

enum _msg_type {
	msg_unknown = 0,
	msg_text = (1 << 0),
	msg_photo = (1 << 1)
};

namespace bot {

	using json = nlohmann::json;

	class bot {
		public:
			bot(const char *in);
			void exec();
			CURLcode exe(const char *method, const char *body, std::string *response = nullptr);
		private:
			inline static size_t curl_write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
			    ((std::string*)userp)->append((char*)contents, size * nmemb);
			    return size * nmemb;
			}
			#ifdef ESTEH_DEBUG
			void validate();
			#endif
			void dispatch();
			std::string lang_bind(std::string str);

			const char *_in;
			json in;
			bool has_been_bind = false;
			uint8_t msg_type = msg_unknown;
			uint8_t chat_type = chat_unknown;
			int64_t chat_id = -1L;
			int64_t user_id = -1L;
			bool is_bot = false;
			std::string text = "";
			std::string first_name = "";
			std::string last_name = "";
			std::string username = "";
			std::string namelink = "";
	};
};

#endif
