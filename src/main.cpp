
#include <cstdio>
#include <bot/bot.hpp>

int main(int argc, char **argv) {

	if (argc <= 1) {
		printf("Parameter is required!\n");
		return 1;
	}

	bot::bot st = new bot::bot(argv[1]);
	st->exec();
	delete st;
}
