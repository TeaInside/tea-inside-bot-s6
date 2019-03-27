<?php

$a = '{
    "update_id": 345222651,
    "message": {
        "message_id": 21682,
        "from": {
            "id": 243692601,
            "is_bot": false,
            "first_name": "Ammar",
            "last_name": "Faizi",
            "username": "ammarfaizi2",
            "language_code": "en"
        },
        "chat": {
            "id": -1001128970273,
            "title": "Private Cloud",
            "type": "private"
        },
        "date": 1553678666,
        "text": "/start",
        "entities": [
            {
                "offset": 0,
                "length": 6,
                "type": "bot_command"
            }
        ]
    }
}';

$ch = curl_init("https://127.0.0.1:8888/");
curl_setopt_array($ch,
	[
		CURLOPT_RETURNTRANSFER => true,
		CURLOPT_POSTFIELDS => json_encode(json_decode($a)),
		CURLOPT_POST => true,
        CURLOPT_SSL_VERIFYPEER => false,
        CURLOPT_SSL_VERIFYHOST => false
	]
);
echo curl_exec($ch)."\n";
curl_close($ch);
