#include "driver.hpp"
#include <curl/curl.h>
#include <curl/easy.h>
#include <iostream>
#include <json/reader.h>
#include <json/writer.h>
#include <stdexcept>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

webdriver::webdriver(){
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    if(!curl){
		printf("Curl not init.\n");
        curl_global_cleanup();
        throw std::runtime_error("Couldn't initalize CURL.");
    }
}

webdriver::~webdriver(){
    curl_easy_cleanup(curl);
    curl_global_cleanup();
}

Json::Value webdriver::start_session(){
	struct curl_slist* list = NULL;
	Json::Value msg;
	Json::Value capabilities;
	
	capabilities["browserName"] = "firefox";
	msg["capabilities"] = capabilities;
	std::string msg_str = msg.toStyledString();

	list = curl_slist_append(list, "Content-Type: aplication/json");

	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST,"POST");
	curl_easy_setopt(curl, CURLOPT_URL,(DRIVER_IP+"/session").c_str());
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS,msg_str.c_str());
	auto rescode = curl_easy_perform(curl);
	if(rescode != CURLE_OK){
		std::cout << "Something went wrong: " << rescode << std::endl;
	}
    // std::cout << readBuffer << std::endl;
	Json::Value response;
	Json::Reader reader;
	if(!reader.parse(readBuffer,response)){
		throw std::runtime_error("Failed to parse json response!");
	}
	readBuffer.erase();
	session = response["value"];

	return session;
}

Json::Value webdriver::stop_session(){
	auto new_curl = curl_easy_init();
	curl_easy_setopt(new_curl, CURLOPT_CUSTOMREQUEST,"DELETE");
	curl_easy_setopt(new_curl, CURLOPT_URL, (DRIVER_IP+"/session/"+(session["sessionId"].asString())).c_str());
	auto rescode = curl_easy_perform(new_curl);
	if(rescode != CURLE_OK){
		std::cout << "Something went wrong: " << rescode << std::endl;
	}

	Json::Value response;
	Json::Reader reader;
	std::cout << readBuffer << std::endl;
	if(!reader.parse(readBuffer,response)){
		throw std::runtime_error("Failed to parse json response!");
	}
	//TODO reader cant parse {"value":null};
	readBuffer.erase();
	curl_easy_cleanup(new_curl);

	return response["value"];
}