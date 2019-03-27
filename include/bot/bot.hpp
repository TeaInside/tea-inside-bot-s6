
#ifndef BOT_BOT_HPP
#define BOT_BOT_HPP

#include <json.hpp>
#include <stdint.h>

namespace bot {

	using json = nlohmann::json;

	class bot {
		public:
			bot(const char *in);
			void exec();
		private:
			const char *_in;
			json in;
			int64_t chat_id = -1LL;
	};
};

#endif
