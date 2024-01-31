#include "driver.hpp"
#include "curl_patterns.hpp"
#include <curl/curl.h>
#include <curl/easy.h>
#include <iostream>
#include <stdexcept>

void inline reset_curl_handle(CURL* curl, std::string& output_buffer){
}

webdriver::webdriver(){
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
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
	return curl_patterns::get(curl,readBuffer,DRIVER_IP+"/status");
}

Json::Value webdriver::get_timeouts(){
	return curl_patterns::get(curl,readBuffer,DRIVER_IP+"/session/"+session["sessionId"].asString()+"/timeouts");
}

Json::Value webdriver::set_timeouts(int implicit, int pageLoad, int script){
	Json::Value msg;
	msg["implicit"] = implicit;
	msg["pageLoad"] = pageLoad;
	msg["script"] = script;

	return curl_patterns::post(curl, readBuffer, DRIVER_IP+"/session/" + session["sessionId"].asString()+"/timeouts",msg);
}

Json::Value webdriver::navigate_to(std::string url){
	Json::Value msg;
	msg["url"] = url;

	return curl_patterns::post(curl,readBuffer,DRIVER_IP+"/session/"+session["sessionId"].asString()+"/url",msg);
}
Json::Value webdriver::get_url(){
	return curl_patterns::get(curl,readBuffer,DRIVER_IP+"/session/"+session["sessionId"].asString()+"/url");
}