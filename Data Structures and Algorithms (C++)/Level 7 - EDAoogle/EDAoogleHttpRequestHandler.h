/**
 * @file EDAoogleHttpRequestHandler.h
 * @author Marc S. Ressl
 * @brief EDAoggle search engine
 * @version 0.1
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef EDAOOGLEHTTPREQUESTHANDLER_H
#define EDAOOGLEHTTPREQUESTHANDLER_H

#include "ServeHttpRequestHandler.h"
#include <vector>
#include <string>
#include <map>
using namespace std;
class EDAoogleHttpRequestHandler : public ServeHttpRequestHandler
{
public:
    EDAoogleHttpRequestHandler(std::string homePath);

    bool handleRequest(std::string url, HttpArguments arguments, std::vector<char> &response);
private:
    void resultFinder(vector<string> &results, string searchString);

    map <int,string> HTMLfileNumber;
    map <string, vector <int>> searchIndex;
    string homePath;
};

#endif
