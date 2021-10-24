
#include "WebServer.h"

#include <fstream>
#include <stdexcept>
#include <iostream>
#include <mutex>

#define SERVICE_B_PORT 8081

void WebServer::run()
{
    httplib::Server svr;

    svr.Get("/log", [this](const httplib::Request& req, httplib::Response& res)
    {
        try
        {
            auto config = load_config();

            auto it = req.params.find("msg");
            if (it == req.params.end())
            {
                throw std::runtime_error("Parameter 'msg' is missing");
            }

            std::string msg = it->second;
            write_log(msg, config.logfile_path);

            res.status = 200;
            res.set_content("OK", "text/plain");
        }
        catch (const std::exception& ex)
        {
            std::cerr << ex.what() << std::endl;
            
            res.status = 500;
            res.set_content("ERROR", "text/plain");
        }
    });

    std::cout << "[+] Web server listening on port " << SERVICE_B_PORT << std::endl;
    svr.listen("0.0.0.0", SERVICE_B_PORT);
}

WebServerConfig WebServer::load_config()
{
    WebServerConfig config;
    config.logfile_path = "app.log"; // default value

    std::ifstream config_file("app.config");

    if (!config_file.good())
    {
        throw std::runtime_error("Failed to open configuration file");
    }

    while (!config_file.eof())
    {
        std::string str;
        std::getline(config_file, str);

        if (str == "")
        {
            continue;
        }

        auto pos = str.find("=");
        if (pos == str.npos)
        {
            throw std::runtime_error("Invalid configuration file");
        }

        std::string name = str.substr(0, pos);
        std::string val = str.substr(pos + 1);

        if (name == "logfile_path")
        {
            config.logfile_path = val;
        }
    }

    return config;
}

void WebServer::write_log(const std::string& msg, const std::string& logfile_path)
{
    static std::mutex mtx;
    std::lock_guard<std::mutex> lock_guard(mtx);
    
    std::wstring path_wstr(logfile_path.begin(), logfile_path.end());
    
    HANDLE file_handle = CreateFile(
        path_wstr.c_str(),
        GENERIC_WRITE,
        FILE_SHARE_READ,
        nullptr,
        OPEN_ALWAYS,
        0,
        nullptr
    );

    if (file_handle == INVALID_HANDLE_VALUE)
    {
        throw std::runtime_error("Failed to open log file: " + std::to_string(GetLastError()));
    }

    std::string msg_with_newline = msg + "\n";
    DWORD bytes_written = 0;

    BOOL result = WriteFile(
        file_handle,
        msg_with_newline.c_str(),
        (DWORD)msg_with_newline.length(),
        &bytes_written,
        nullptr
    );

    if (!result)
    {
        CloseHandle(file_handle);
        throw std::runtime_error("Failed to write to log file: " + std::to_string(GetLastError()));
    }

    CloseHandle(file_handle);
}
