#pragma once

#include "httplib.h"

#include <string>

struct WebServerConfig
{
    std::string logfile_path;
};

class WebServer
{
public:
    void run();

private:
    WebServerConfig load_config();
    void write_log(const std::string& msg, const std::string& logfile_path);
};
