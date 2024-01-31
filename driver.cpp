#include "driver.hpp"
#include "curl_patterns.hpp"
#include <curl/curl.h>
#include <curl/easy.h>
#include <iostream>
#include <stdexcept>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
void inline reset_curl_handle(CURL* curl, std::string& output_buffer){
	curl_easy_reset(curl);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &output_buffer);
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
	reset_curl_handle(curl,readBuffer);
	Json::Value msg;
	Json::Value capabilities;
	
	capabilities["browserName"] = "firefox";
	msg["capabilities"] = capabilities;

	session = curl_patterns::post(curl,readBuffer,DRIVER_IP+"/session",msg);

	return session;
}

Json::Value webdriver::stop_session(){
	reset_curl_handle(curl,readBuffer);
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST,"DELETE");
	curl_easy_setopt(curl, CURLOPT_URL, (DRIVER_IP+"/session/"+(session["sessionId"].asString())).c_str());
	auto rescode = curl_easy_perform(curl);
	if(rescode != CURLE_OK){
		std::cout << "Something went wrong: " << rescode << std::endl;
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

Json::Value webdriver::status(){
	reset_curl_handle(curl, readBuffer);
	return curl_patterns::get(curl,readBuffer,DRIVER_IP+"/status");
}

Json::Value webdriver::get_timeouts(){
	reset_curl_handle(curl, readBuffer);
	return curl_patterns::get(curl,readBuffer,DRIVER_IP+"/session/"+session["sessionId"].asString()+"/timeouts");
}

Json::Value webdriver::set_timeouts(){
	reset_curl_handle(curl,readBuffer);
	Json::Value msg;
	msg["implicit"] = 0;
	msg["pageLoad"] = 150000;
	msg["script"] = 15000;

	return curl_patterns::post(curl, readBuffer, DRIVER_IP+"/session/" + session["sessionId"].asString()+"/timeouts",msg);
}