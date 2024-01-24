#include <iostream>
#include <curl/curl.h>
#include <json/json.h>

const std::string DRIVER_IP = "127.0.0.1:4444";

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
std::string start_session(CURL* curl){
	struct curl_slist* list = NULL;
	list = curl_slist_append(list, "Content-Type: aplication/json");
	Json::Value msg;
	Json::Value capabilities;
	
	capabilities["browserName"] = "firefox";
	capabilities["browserVersion"] = "1234";
	msg["capabilities"] = capabilities;
	std::string msg_str = msg.toStyledString();

	std::string readBuffer;
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST,"POST");
	curl_easy_setopt(curl, CURLOPT_URL,(DRIVER_IP+"/session").c_str());
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS,msg_str.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
	curl_easy_perform(curl);

	return readBuffer;
}
std::string end_session(CURL* curl, std::string& session_id){
	std::string readBuffer;
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST,"DELETE");
	curl_easy_setopt(curl, CURLOPT_URL, (DRIVER_IP+"/session/" + session_id).c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
	curl_easy_perform(curl);

	std::cout << readBuffer << std::endl;
	return readBuffer;
}

int main(void){
	CURL* curl;

	curl = curl_easy_init();
	
	if(curl){
		// start_session(curl);

		curl_easy_cleanup(curl);
	}

	return 0;
}
