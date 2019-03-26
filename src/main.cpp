
#include <cstdio>
#include <unistd.h>
#include <fcgio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <signal.h>
#include <bot/bot.hpp>

#define STDIN_MAX 40960

using namespace std;

string get_request_content(const FCGX_Request & request);

int main(int argc, char **argv) {

	if (argc <= 1) {
		printf("Parameter is required!\n");
		return 1;
	}

	if (!strcmp(argv[1], "fcgi")) {
		signal(SIGCHLD, SIG_IGN);
		// Backup the stdio streambufs
	    streambuf *cin_streambuf  = cin.rdbuf();
	    streambuf *cout_streambuf = cout.rdbuf();
	    streambuf *cerr_streambuf = cerr.rdbuf();
		FCGX_Request request;
	    FCGX_Init();
	    FCGX_InitRequest(&request, 0, 0);
	    while (FCGX_Accept_r(&request) == 0) {
	        fcgi_streambuf cin_fcgi_streambuf(request.in);
	        fcgi_streambuf cout_fcgi_streambuf(request.out);
	        fcgi_streambuf cerr_fcgi_streambuf(request.err);

	        cin.rdbuf(&cin_fcgi_streambuf);
	        cout.rdbuf(&cout_fcgi_streambuf);
	        cerr.rdbuf(&cerr_fcgi_streambuf);

	        string data = get_request_content(request);

	        if (!fork()) {
	        	const char *_data = data.c_str();
	        	sprintf(argv[0], "%s-worker --data %s", argv[0], _data);
	        	cin.rdbuf(cin_streambuf);
    			cout.rdbuf(cout_streambuf);
	    		cerr.rdbuf(cerr_streambuf);
	        	bot::bot *st = new bot::bot(_data);
				st->exec();
				delete st;
				exit(0);
	        }

	        cout << "Content-type: application/json\r\n\r\n\"OK\"";
	        // Note: the fcgi_streambuf destructor will auto flush
	    }
	    cin.rdbuf(cin_streambuf);
    	cout.rdbuf(cout_streambuf);
	    cerr.rdbuf(cerr_streambuf);
	} else {
		bot::bot *st = new bot::bot(argv[1]);
		st->exec();
		delete st;
	}
}

string get_request_content(const FCGX_Request & request) {
    char * content_length_str = FCGX_GetParam("CONTENT_LENGTH", request.envp);
    unsigned long content_length = STDIN_MAX;

    if (content_length_str) {
        content_length = strtol(content_length_str, &content_length_str, 10);
        if (*content_length_str) {
            cerr << "Can't Parse 'CONTENT_LENGTH='"
                 << FCGX_GetParam("CONTENT_LENGTH", request.envp)
                 << "'. Consuming stdin up to " << STDIN_MAX << endl;
        }
        if (content_length > STDIN_MAX) {
            content_length = STDIN_MAX;
        }
    } else {
        // Do not read from stdin if CONTENT_LENGTH is missing
        content_length = 0;
    }
    
	char *content_buffer = new char[content_length];
    cin.read(content_buffer, content_length);
    content_length = cin.gcount();

	do {
		cin.ignore(1024);
	} while (cin.gcount() == 1024);

	string content(content_buffer, content_length);
    delete[] content_buffer;
    return content;
}
