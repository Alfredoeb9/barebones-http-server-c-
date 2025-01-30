#include "WebServer.h"
#include <iostream>
#include <string>
#include <sstream>

int main()
{
	WebServer webServer("0.0.0.0", 8080);
	if (webServer.init() != 0)
		return 1;

	webServer.run();

    return 0;
}