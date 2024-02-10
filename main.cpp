#include "driver.hpp"
#include <iostream>
#include <json/json.h>



int main(void){
	int d;
	webdriver wd;
	auto msg = wd.start_session();//("https://google.com");
	// std::cout << msg << std::endl;
	// std::cout << wd.status() << std::endl;
	// std::cout << wd.get_timeouts() << std::endl;
	// std::cout << "Setting timeouts...\n" << wd.set_timeouts(0,150000,15000) << std::endl;
	// std::cout << wd.get_timeouts() << std::endl;
	// std::cout << "Waiting on input" << std::endl;
	wd.navigate_to("https://google.com");
	// std::cout << wd.get_url() << std::endl;
	// std::cin >> d;
	// std::cout << wd.go_back() << std::endl;
	// std::cin >> d;
	// std::cout << wd.go_forward() << std::endl;
	// std::cin >> d;
	// std::cout << wd.refresh() << std::endl;
	// std::cout << wd.switch_to_parent_frame() << std::endl;
	// std::cout << wd.title() << std::endl;
	// auto current_handle = wd.get_window_handle().asString();
	// std::cout << current_handle << std::endl;
	// auto new_handle = wd.new_window()["handle"].asString();
	// std::cout << new_handle << std::endl;
	// std::cout << wd.switch_to_window(new_handle) << std::endl;
	// std::cout << wd.get_window_handles() << std::endl;
	// std::cout << wd.get_window_rect() << std::endl;
	// std::cout << wd.set_window_rect(500, 500) << std::endl;
	// std::cout << wd.minimize_window() << std::endl;
	// std::cout << wd.fullscreen_window() << std::endl;
	// std::cout << wd.maximize_window() << std::endl;
	// auto el = wd.find_element(webdriver::selector::css_selector,"#APjFqb");
	// std::cin >> d;
	// std::cout << wd.element_send_keys(el[el.getMemberNames()[0]].asString(), "Hello :)") << std::endl;
	// std::cout << wd.element_clear(el[el.getMemberNames()[0]].asString()) << std::endl;
	// std::cout << wd.element_click(el[el.getMemberNames()[0]].asString()) << std::endl;
	// std::cout << << std::endl;
	// std::cout << wd.get_element_shadow_root(el[el.getMemberNames()[0]].asString()) << std::endl;
	// std::cout << wd.find_elements(webdriver::selector::css_selector, ".a4bIc") << std::endl;
	// std::cout << wd.find_element_from_element(el[el.getMemberNames()[0]].asString(),webdriver::selector::xpath, "//*[@id=\"APjFqb\"]") << std::endl;
	// std::cout << wd.find_elements_from_element(el[el.getMemberNames()[0]].asString(),webdriver::selector::xpath, "//*[@id=\"APjFqb\"]") << std::endl;
	// std::cout << wd.find_element_from_shadow_root(el[el.getMemberNames()[0]].asString(),webdriver::selector::css_selector, ".a4bIc") << std::endl;
	// std::cout << wd.find_elements_from_shadow_root(el[el.getMemberNames()[0]].asString(),webdriver::selector::css_selector, ".a4bIc") << std::endl;
	// std::cout << wd.is_element_selected(el[el.getMemberNames()[0]].asString()) << std::endl;
	// std::cout << wd.get_element_text(el[el.getMemberNames()[0]].asString()) << std::endl;
	// std::cout << wd.get_element_property(el[el.getMemberNames()[0]].asString(),"title") << std::endl;
	// std::cout << wd.get_element_attribute(el[el.getMemberNames()[0]].asString(),"title") << std::endl;
	// std::cout << wd.get_element_css_value(el[el.getMemberNames()[0]].asString(),"title") << std::endl;
	// std::cout << wd.get_element_tag_name(el[el.getMemberNames()[0]].asString()) << std::endl;
	// std::cout << wd.get_element_rect(el[el.getMemberNames()[0]].asString()) << std::endl;
	// std::cout << wd.get_computed_label(el[el.getMemberNames()[0]].asString()) << std::endl;
	// std::cout << wd.get_computed_role(el[el.getMemberNames()[0]].asString()) << std::endl;
	// std::cout << wd.is_element_enabled(el[el.getMemberNames()[0]].asString()) << std::endl;
	// std::cout << wd.get_page_source() << std::endl;
	std::cin >> d;
	wd.stop_session();
	// Json::Reader reader;
	// Json::Value val;
	// std::cout << reader.parse("{\"value\":null}",val) << std::endl;
	// std::cout << val << std::endl;
	return 0;
}
