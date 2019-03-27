<?php

$a = '{
    "message": {
        "chat": {
            "id": -1001128970273,
            "title": "Private Cloud",
            "type": "supergroup"
        }
    }
}';

$ch = curl_init("http://127.0.0.1");
curl_setopt_array($ch,
	[
		CURLOPT_RETURNTRANSFER => true,
		CURLOPT_POSTFIELDS => json_encode(json_decode($a)),
		CURLOPT_POST => true
	]
);
echo curl_exec($ch)."\n";
curl_close($ch);
