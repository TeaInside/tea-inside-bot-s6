
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

			std::string exe(const char *method, const char *body) {

				char *_url = (char *)malloc(sizeof("https://api.telegram.org/bot" TOKEN "/") - 1 + strlen(method));
				sprintf(_url, "https://api.telegram.org/bot" TOKEN "/%s", method);

				CURL *curl;
				// CURLcode res;
				std::string readBuffer = "";
				curl = curl_easy_init();
				if (curl) {
					curl_easy_setopt(curl, CURLOPT_URL, _url);
					curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, this->curl_write_callback);
					curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
					curl_easy_setopt(curl, CURLOPT_POST, true);
					curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
					curl_easy_setopt(curl, CURLOPT_VERBOSE, true);
					curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
					curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
					/*res = */curl_easy_perform(curl);
					curl_easy_cleanup(curl);
				}

				return readBuffer;
			}

		private:
			inline static size_t curl_write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
			    ((std::string*)userp)->append((char*)contents, size * nmemb);
			    return size * nmemb;
			}

			void dispatch();

			const char *_in;
			json in;
			uint8_t msg_type = msg_unknown;
			uint8_t chat_type = chat_unknown;
			int64_t chat_id = -1L;
			std::string text;
	};
};

#endif
