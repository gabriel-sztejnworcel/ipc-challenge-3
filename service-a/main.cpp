
#include "WebServer.h"

#include <stdexcept>
#include <iostream>

int main()
{
    try
    {
        WebServer web_server;
        web_server.run();
    }
    catch (const std::exception& ex)
    {
        std::cerr << "ERROR: " << ex.what() << std::endl;
    }
}
