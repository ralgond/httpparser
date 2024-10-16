/*
 * Copyright (C) Alex Nekipelov (alex@nekipelov.net)
 * License: MIT
 */

#ifndef HTTPPARSER_REQUEST_H
#define HTTPPARSER_REQUEST_H

#include <string>
#include <vector>
#include <sstream>

namespace httpparser
{

struct Request {
    Request()
        : versionMajor(0), versionMinor(0), contentLength(0), keepAlive(false)
    {}
    
    struct HeaderItem
    {
        std::string name;
        std::string value;
    };

    std::string method;
    std::string uri;
    int versionMajor;
    int versionMinor;
    long contentLength;
    std::string xUpstreamServer;
    std::vector<HeaderItem> headers;
    std::vector<char> content;
    bool keepAlive;

    std::string inspect() const
    {
        std::stringstream stream;
        stream << method << " " << uri << " HTTP/"
               << versionMajor << "." << versionMinor << "\n";

        for(std::vector<Request::HeaderItem>::const_iterator it = headers.begin();
            it != headers.end(); ++it)
        {
            stream << it->name << ": " << it->value << "\n";
        }

        std::string data(content.begin(), content.end());
        stream << data << "\n";
        stream << "+ keep-alive: " << keepAlive << "\n";
        stream << "+ content-length: " << contentLength << "\n";
        stream << "+ x-upstream-server: " << xUpstreamServer << "\n";
        return stream.str();
    }

    std::string headerToString() const {
        std::stringstream stream;
        stream << method << " " << uri << " HTTP/"
               << versionMajor << "." << versionMinor << "\r\n";
        for(std::vector<Request::HeaderItem>::const_iterator it = headers.begin();
            it != headers.end(); ++it)
        {
            stream << it->name << ": " << it->value << "\r\n";
        }
        stream << "\r\n";
        return stream.str();
    }
};

} // namespace httpparser


#endif // HTTPPARSER_REQUEST_H
