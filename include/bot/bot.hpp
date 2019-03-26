
#ifndef BOT_BOT_HPP
#define BOT_BOT_HPP

#include <json.hpp>

namespace bot {

	using json = nlohmann::json;

	class bot {
		public:
			bot(const char *in);
			void exec();
		private:
			const char *in;
			json d;
	};
};

#endif
