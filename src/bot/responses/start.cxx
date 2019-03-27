
this->exe(
	"sendMessage",
	std::string(
		"chat_id="+std::to_string(this->chat_id)+
		"&text="+urlencode(this->lang_bind(this->chat_type == chat_private ? start_private : start_group))+
		"&parse_mode=html"
	).c_str()
);

return;
