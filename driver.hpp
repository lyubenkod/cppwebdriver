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
    enum selector{
        css_selector,
        link_text,
        partial_link_text,
        tag_name,
        xpath
    };
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
    Json::Value find_element(webdriver::selector strategy, std::string value);
    Json::Value find_elements(webdriver::selector strategy, std::string value);
    Json::Value find_element_from_element(std::string element_id, webdriver::selector strategy, std::string value);
    Json::Value find_elements_from_element(std::string element_id, webdriver::selector strategy, std::string value);
    Json::Value find_element_from_shadow_root(std::string root_id, webdriver::selector strategy, std::string value);
    Json::Value find_elements_from_shadow_root(std::string root_id, webdriver::selector strategy, std::string value);
    Json::Value is_element_selected(std::string element_id);
    Json::Value get_element_attribute(std::string element_id, std::string attribute);
    Json::Value get_element_property(std::string element_id, std::string property);
    Json::Value get_element_css_value(std::string element_id, std::string css_value);
    Json::Value get_element_text(std::string element_id);
    Json::Value get_element_tag_name(std::string element_id);
    Json::Value get_element_rect(std::string element_id);
    Json::Value is_element_enabled(std::string element_id);
    Json::Value get_computed_role(std::string element_id);
    Json::Value get_computed_label(std::string element_id);
    Json::Value element_click(std::string element_id);
    Json::Value element_clear(std::string element_id);
    Json::Value element_send_keys(std::string element_id, std::string text);
    Json::Value get_page_source();
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