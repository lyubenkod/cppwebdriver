#pragma once
#include <json/json.h>
#include <curl/curl.h>

namespace curl_patterns {
inline Json::Value get(CURL* curl, std::string& readBuffer, std::string url){
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
	//TODO reader cant parse {"value":null};
	readBuffer.erase();

	return response["value"];
}
inline Json::Value post(CURL* curl, std::string& readBuffer, std::string url,Json::Value message){
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

    // std::cout << readBuffer << std::endl;
	Json::Value response;
	Json::Reader reader;
	if(!reader.parse(readBuffer,response)){
		throw std::runtime_error("Failed to parse json response!");
	}
	readBuffer.erase();

	return response["value"];
}
}