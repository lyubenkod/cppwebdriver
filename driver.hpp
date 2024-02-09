#pragma once
#include <curl/curl.h>
#include <json/json.h>
#include <string>

class webdriver{
    CURL* curl;
    Json::Value session;
	std::string readBuffer;
    const std::string DRIVER_IP = "127.0.0.1:4444";

public:
    webdriver();
    ~webdriver();

    Json::Value start_session();
    Json::Value stop_session();
    Json::Value status();
    Json::Value get_timeouts();
    Json::Value set_timeouts(int implicit, int pageLoad, int script);
    Json::Value navigate_to(std::string url);
    Json::Value get_url();
    Json::Value go_back();
    Json::Value go_forward();
    Json::Value refresh();
    Json::Value title();
    Json::Value get_window_handle();
    Json::Value close_window();
    Json::Value switch_to_window(std::string handle);
    Json::Value get_window_handles();
    Json::Value new_window(std::string hint = "tab");
    // Json::Value switch_to_frame();
    Json::Value switch_to_parent_frame();
    Json::Value get_window_rect();
    Json::Value set_window_rect(int width, int height);
    Json::Value maximize_window();
    Json::Value minimize_window();
    Json::Value fullscreen_window();
    Json::Value get_active_element();
    Json::Value get_element_shadow_root(std::string element_id);
    // Json::Value find_element();
    // Json::Value find_elements();
    // Json::Value find_element_from_element();
    // Json::Value find_elements_from_element();
    // Json::Value find_element_from_shadow_root();
    // Json::Value find_elements_from_shadow_root();
    // Json::Value is_element_selected();
    // Json::Value get_element_attribute();
    // Json::Value get_element_property();
    // Json::Value get_element_css_value();
    // Json::Value get_element_text();
    // Json::Value get_element_tag_name();
    // Json::Value get_element_rect();
    // Json::Value is_element_enabled();
    // Json::Value get_computed_role();
    // Json::Value get_computed_label();
    // Json::Value element_click();
    // Json::Value element_clear();
    // Json::Value element_send_keys();
    // Json::Value get_page_source();
    // Json::Value execute_script();
    // Json::Value execute_async_script();
    // Json::Value get_all_cookies();
    // Json::Value get_named_cookie();
    // Json::Value add_cookie();
    // Json::Value delete_cookie();
    // Json::Value delete_all_cookies();
    // Json::Value perform_actions();
    // Json::Value release_actions();
    // Json::Value dismiss_alert();
    // Json::Value accept_alert();
    // Json::Value get_alert_text();
    // Json::Value send_alert_text();
    // Json::Value take_screenshot();
    // Json::Value take_element_screenshot();
    // Json::Value print_page();
};