#include "driver.hpp"
#include <iostream>
#include <json/json.h>


int main(void){
	int d;
	webdriver wd;
	auto msg = wd.start_session();//("https://google.com");
	std::cout << msg << std::endl;
	std::cout << "Waiting on input" << std::endl;
	std::cin >> d;
	std::cout << wd.stop_session() << std::endl;
	return 0;
}
