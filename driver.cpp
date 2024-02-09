#include "driver.hpp"
#include "curl_patterns.hpp"
#include <curl/curl.h>
#include <json/json.h>
#include <json/value.h>

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
	return curl_patterns::send_post(curl,readBuffer,DRIVER_IP+"/session/"+session["sessionId"].asString()+"/back",Json::objectValue);
}
Json::Value webdriver::go_forward(){
	return curl_patterns::send_post(curl,readBuffer,DRIVER_IP+"/session/"+session["sessionId"].asString()+"/forward",Json::objectValue);
}
Json::Value webdriver::refresh(){
	return curl_patterns::send_post(curl,readBuffer,DRIVER_IP+"/session/"+session["sessionId"].asString()+"/refresh",Json::objectValue);
}
Json::Value webdriver::title(){
	return curl_patterns::send_get(curl,readBuffer,DRIVER_IP+"/session/"+session["sessionId"].asString()+"/title");
}
Json::Value webdriver::get_window_handle(){
	return curl_patterns::send_get(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/window");
}

Json::Value webdriver::close_window(){
	return curl_patterns::send_delete(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/window");
}

Json::Value webdriver::switch_to_window(std::string handle){
	Json::Value msg;
	msg["handle"] = handle;
	return curl_patterns::send_post(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/window",msg);
}

Json::Value webdriver::get_window_handles(){
	return curl_patterns::send_get(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/window/handles");
}

// options for hint: "tab" | "window"
Json::Value webdriver::new_window(std::string hint){
	Json::Value msg;
	msg["hint"] = hint;
	return curl_patterns::send_post(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/window/new",msg);
}

// Json::Value webdriver::switch_to_frame(){
// 	Json::Value msg;
// 	msg["id"] = 1;
// 	return curl_patterns::send_post(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/frame",msg);
// }

Json::Value webdriver::switch_to_parent_frame(){
	return curl_patterns::send_post(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/frame/parent",Json::objectValue);
}

Json::Value webdriver::get_window_rect(){
	return curl_patterns::send_get(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/window/rect");
}

Json::Value webdriver::set_window_rect(int width, int height){
	Json::Value msg;
	msg["width"] = width;
	msg["height"] = height;
	return curl_patterns::send_post(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/window/rect",msg);
}

Json::Value webdriver::maximize_window(){
	return curl_patterns::send_post(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/window/maximize",Json::objectValue);
}

Json::Value webdriver::minimize_window(){
	return curl_patterns::send_post(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/window/minimize",Json::objectValue);
}

Json::Value webdriver::fullscreen_window(){
	return curl_patterns::send_post(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/window/fullscreen",Json::objectValue);
}

Json::Value webdriver::get_active_element(){
	return curl_patterns::send_get(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/element/active");
}

Json::Value webdriver::get_element_shadow_root(std::string element_id){
	return curl_patterns::send_get(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/element/"+element_id+"/shadow");
}

// Json::Value webdriver::find_element(){
// 	return curl_patterns::send_post(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/element",msg);
// }

// Json::Value webdriver::find_elements(){
// 	return curl_patterns::send_post(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/elements",msg);
// }

// Json::Value webdriver::find_element_from_element(){
// 	return curl_patterns::send_post(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/element/{element id}/element",msg);
// }

// Json::Value webdriver::find_elements_from_element(){
// 	return curl_patterns::send_post(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/element/{element id}/elements",msg);
// }

// Json::Value webdriver::find_element_from_shadow_root(){
// 	return curl_patterns::send_post(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/shadow/{shadow id}/element",msg);
// }

// Json::Value webdriver::find_elements_from_shadow_root(){
// 	return curl_patterns::send_post(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/shadow/{shadow id}/elements",msg);
// }

// Json::Value webdriver::is_element_selected(){
// 	return curl_patterns::send_get(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/element/{element id}/selected");
// }

// Json::Value webdriver::get_element_attribute(){
// 	return curl_patterns::send_get(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/element/{element id}/attribute/{name}");
// }

// Json::Value webdriver::get_element_property(){
// 	return curl_patterns::send_get(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/element/{element id}/property/{name}");
// }

// Json::Value webdriver::get_element_css_value(){
// 	return curl_patterns::send_get(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/element/{element id}/css/{property name}");
// }

// Json::Value webdriver::get_element_text(){
// 	return curl_patterns::send_get(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/element/{element id}/text");
// }

// Json::Value webdriver::get_element_tag_name(){
// 	return curl_patterns::send_get(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/element/{element id}/name");
// }

// Json::Value webdriver::get_element_rect(){
// 	return curl_patterns::send_get(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/element/{element id}/rect");
// }

// Json::Value webdriver::is_element_enabled(){
// 	return curl_patterns::send_get(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/element/{element id}/enabled");
// }

// Json::Value webdriver::get_computed_role(){
// 	return curl_patterns::send_get(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/element/{element id}/computedrole");
// }

// Json::Value webdriver::get_computed_label(){
// 	return curl_patterns::send_get(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/element/{element id}/computedlabel");
// }

// Json::Value webdriver::element_click(){
// 	return curl_patterns::send_post(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/element/{element id}/click",msg);
// }

// Json::Value webdriver::element_clear(){
// 	return curl_patterns::send_post(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/element/{element id}/clear",msg);
// }

// Json::Value webdriver::element_send_keys(){
// 	return curl_patterns::send_post(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/element/{element id}/value",msg);
// }

// Json::Value webdriver::get_page_source(){
// 	return curl_patterns::send_get(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/source");
// }

// Json::Value webdriver::execute_script(){
// 	return curl_patterns::send_post(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/execute/sync",msg);
// }

// Json::Value webdriver::execute_async_script(){
// 	return curl_patterns::send_post(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/execute/async",msg);
// }

// Json::Value webdriver::get_all_cookies(){
// 	return curl_patterns::send_get(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/cookie");
// }

// Json::Value webdriver::get_named_cookie(){
// 	return curl_patterns::send_get(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/cookie/{name}");
// }

// Json::Value webdriver::add_cookie(){
// 	return curl_patterns::send_post(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/cookie",msg);
// }

// Json::Value webdriver::delete_cookie(){
// 	return curl_patterns::send_delete(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/cookie/{name}");
// }

// Json::Value webdriver::delete_all_cookies(){
// 	return curl_patterns::send_delete(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/cookie");
// }

// Json::Value webdriver::perform_actions(){
// 	return curl_patterns::send_post(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/actions",msg);
// }

// Json::Value webdriver::release_actions(){
// 	return curl_patterns::send_delete(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/actions");
// }

// Json::Value webdriver::dismiss_alert(){
// 	return curl_patterns::send_post(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/alert/dismiss",msg);
// }

// Json::Value webdriver::accept_alert(){
// 	return curl_patterns::send_post(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/alert/accept",msg);
// }

// Json::Value webdriver::get_alert_text(){
// 	return curl_patterns::send_get(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/alert/text");
// }

// Json::Value webdriver::send_alert_text(){
// 	return curl_patterns::send_post(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/alert/text",msg);
// }

// Json::Value webdriver::take_screenshot(){
// 	return curl_patterns::send_get(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/screenshot");
// }

// Json::Value webdriver::take_element_screenshot(){
// 	return curl_patterns::send_get(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/element/{element id}/screenshot");
// }

// Json::Value webdriver::print_page(){
// 	return curl_patterns::send_post(curl,readBuffer,DRIVER_IP + "/session/" + session["sessionId"].asString() + "/print",msg);
// }