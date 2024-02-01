#pragma once
#include <json/json.h>
#include <curl/curl.h>

namespace curl_patterns {
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
inline Json::Value send_get(CURL* curl, std::string& readBuffer, std::string url){
	curl_easy_reset(curl);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST,"GET");
	curl_easy_setopt(curl,CURLOPT_URL,url.c_str());
	auto rescode = curl_easy_perform(curl);
	if(rescode != CURLE_OK){
		throw std::runtime_error("Something went wrong: " + std::to_string(rescode));
	}

	Json::Value response;
	Json::Reader reader;
	if(!reader.parse(readBuffer,response)){
		throw std::runtime_error("Failed to parse json response!");
	}
	readBuffer.erase();

	return response["value"];
}
inline Json::Value send_post(CURL* curl, std::string& readBuffer, std::string url,Json::Value message){
	curl_easy_reset(curl);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

	struct curl_slist* list = NULL;
	list = curl_slist_append(list, "Content-Type: aplication/json");
	std::string msg_str = message.toStyledString();

	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST,"POST");
	curl_easy_setopt(curl, CURLOPT_URL,url.c_str());
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS,msg_str.c_str());
	auto rescode = curl_easy_perform(curl);
	if(rescode != CURLE_OK){
		throw std::runtime_error("Something went wrong: " + std::to_string(rescode));
	}
	curl_slist_free_all(list);

	Json::Value response;
	Json::Reader reader;
	if(!reader.parse(readBuffer,response)){
		throw std::runtime_error("Failed to parse json response!");
	}
	readBuffer.erase();

	return response["value"];
}
inline Json::Value send_delete(CURL* curl, std::string& readBuffer, std::string url){
	curl_easy_reset(curl);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST,"DELETE");
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	auto rescode = curl_easy_perform(curl);
	if(rescode != CURLE_OK){
		throw std::runtime_error("Something went wrong: " + std::to_string(rescode));
	}

	Json::Value response;
	Json::Reader reader;
	if(!reader.parse(readBuffer,response)){
		throw std::runtime_error("Failed to parse json response!");
	}
	readBuffer.erase();

	return response["value"];
}
}