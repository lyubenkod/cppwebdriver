#include "driver.hpp"
#include "curl_patterns.hpp"
#include <curl/curl.h>
#include <stdexcept>

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

	session = curl_patterns::send_post(curl,readBuffer,DRIVER_IP+"/session",msg);

	return session;
}

Json::Value webdriver::stop_session(){
	return curl_patterns::send_delete(curl,readBuffer,DRIVER_IP+"/session/"+session["sessionId"].asString());
}

Json::Value webdriver::status(){
	return curl_patterns::send_get(curl,readBuffer,DRIVER_IP+"/status");
}

Json::Value webdriver::get_timeouts(){
	return curl_patterns::send_get(curl,readBuffer,DRIVER_IP+"/session/"+session["sessionId"].asString()+"/timeouts");
}

Json::Value webdriver::set_timeouts(int implicit, int pageLoad, int script){
	Json::Value msg;
	msg["implicit"] = implicit;
	msg["pageLoad"] = pageLoad;
	msg["script"] = script;

	return curl_patterns::send_post(curl, readBuffer, DRIVER_IP+"/session/" + session["sessionId"].asString()+"/timeouts",msg);
}

Json::Value webdriver::navigate_to(std::string url){
	Json::Value msg;
	msg["url"] = url;

	return curl_patterns::send_post(curl,readBuffer,DRIVER_IP+"/session/"+session["sessionId"].asString()+"/url",msg);
}
Json::Value webdriver::get_url(){
	return curl_patterns::send_get(curl,readBuffer,DRIVER_IP+"/session/"+session["sessionId"].asString()+"/url");
}
Json::Value webdriver::go_back(){
	Json::Value msg;
	msg["text"] = "Hello :)";
	return curl_patterns::send_post(curl,readBuffer,DRIVER_IP+"/session/"+session["sessionId"].asString()+"/back",msg);
}
Json::Value webdriver::go_forward(){
	Json::Value msg;
	msg["text"] = "Hello :)";
	return curl_patterns::send_post(curl,readBuffer,DRIVER_IP+"/session/"+session["sessionId"].asString()+"/forward",msg);
}
Json::Value webdriver::refresh(){
	Json::Value msg;
	msg["text"] = "Hello :)";
	return curl_patterns::send_post(curl,readBuffer,DRIVER_IP+"/session/"+session["sessionId"].asString()+"/refresh",msg);
}
Json::Value webdriver::title(){
	return curl_patterns::send_get(curl,readBuffer,DRIVER_IP+"/session/"+session["sessionId"].asString()+"/title");
}