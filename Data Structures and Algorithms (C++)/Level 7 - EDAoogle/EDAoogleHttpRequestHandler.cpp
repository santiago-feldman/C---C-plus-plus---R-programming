/**
 * @file EDAoogleHttpRequestHandler.h
 * @author Marc S. Ressl
 * @brief EDAoggle search engine
 * @version 0.1
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <string>
#include <sstream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include "EDAoogleHttpRequestHandler.h"

using namespace std;

/**
 * @brief Construct a new EDAoogleHttpRequestHandler object
 * 
 * @param homePath
 */
EDAoogleHttpRequestHandler::EDAoogleHttpRequestHandler(string homePath) : ServeHttpRequestHandler(homePath)
{
    //------------- HTML CLEAN ----------------------------//
    // @brief for every html file in ./www/wiki, extract content without tags.
    string wikiPath = homePath + "/wiki";
    for (auto &nameFile : filesystem::directory_iterator(wikiPath))
    {
        ifstream inFile(nameFile.path()); //open the input file
        stringstream strStream;
        strStream << inFile.rdbuf(); //read the file
        string str = strStream.str(); //str holds the content of the file
        static int i = 0;
        cout << "Loading File No. " << i +1 << " of 1284" << endl;
        HTMLfileNumber.insert(std::pair<int, string>(i, nameFile.path()));
        
        while (str.find("<") != std::string::npos)
        {
            auto startpos = str.find("<");
            auto endpos = str.find(">") + 1;

            if (endpos != std::string::npos)
            {
                str.erase(startpos, endpos - startpos);
            }
        }
        string word;
    
    //--------------------- ADD TO SEARCH INDEX -------------//

        for (char c : str)
        {
            static bool insideWord = false;
            if (c != ' ' && c != '\r' && c != '\n' && c != ',' && c != '.' && c != '\t')
            {
                word.push_back(c);
                insideWord = true;
            }
            else if (insideWord == true)
            {
                searchIndex[word].push_back(i);
                word.clear();
                insideWord=false;
            }
        }
        i++;
    //--------------------------------------------------------//

    }
}

bool EDAoogleHttpRequestHandler::handleRequest(string url,
                                               HttpArguments arguments,
                                               vector<char> &response)
{
    string searchPage = "/search";
    if (url.substr(0, searchPage.size()) == searchPage)
    {
        string searchString;
        if (arguments.find("q") != arguments.end())
            searchString = arguments["q"];

        // Header
        string responseString = string("<!DOCTYPE html>\
<html>\
\
<head>\
    <meta charset=\"utf-8\" />\
    <title>EDAoogle</title>\
    <link rel=\"preload\" href=\"https://fonts.googleapis.com\" />\
    <link rel=\"preload\" href=\"https://fonts.gstatic.com\" crossorigin />\
    <link href=\"https://fonts.googleapis.com/css2?family=Inter:wght@400;800&display=swap\" rel=\"stylesheet\" />\
    <link rel=\"preload\" href=\"../css/style.css\" />\
    <link rel=\"stylesheet\" href=\"../css/style.css\" />\
</head>\
\
<body>\
    <article class=\"edaoogle\">\
        <div class=\"title\"><a href=\"/\">EDAoogle</a></div>\
        <div class=\"search\">\
            <form action=\"/search\" method=\"get\">\
                <input type=\"text\" name=\"q\" value=\"" +
                                       searchString + "\" autofocus>\
            </form>\
        </div>\
        ");

        float searchTime = 0.1F;
        vector<string> results;
        results.push_back(HTMLfileNumber[rand()%1284]);
        results.push_back(HTMLfileNumber[rand()%1284]);

        resultFinder(results, searchString);        // Fill in results vector
        // Print search results
        responseString += "<div class=\"results\">" + to_string(results.size()) +
                          " results (" + to_string(searchTime) + " seconds):</div>";
        for (auto &result : results)
        {
            responseString += "<div class=\"result\"><a href=\"" +
                              result + "\">" + result + "</a></div>";
        }

        // Trailer
        responseString += "    </article>\
</body>\
</html>";

        response.assign(responseString.begin(), responseString.end());

        return true;
    }
    else
        return serve(url, response);

    return false;
}

void EDAoogleHttpRequestHandler::resultFinder(vector<string> &results, string searchString)
{
    //--------- Search in disk ------------//
    // Service currently unavailable
    //--------- Not in Disk ---------------//
    string wikiPath = homePath + "/wiki";

    // Filtramos el string como sub string separados por espacios

    string space = " ";
    vector<string> words;
    int pos = 0;
    while ((pos = searchString.find(space)) != string::npos)
    {
        words.push_back(searchString.substr(0, pos));
        searchString.erase(0, pos + space.length());
    }

    //---------- SEARCH IN SEARCH INDEX -----//

    vector<int> index;
    for (auto word : words)
    {
        map <string,vector<int>>::iterator itmap= searchIndex.find(word);      // Search for keyword

        if (itmap != searchIndex.end())
        {
            vector<int> indexPages = itmap->second;     // Access pages found with that keyword
            for (auto i : indexPages)
            {
                vector<int>::iterator it;
                it = find(index.begin(), index.end(), i);
                
                if (it == index.end())
                {
                    index.push_back(i);     //if found, add to provisional vector with pageNumbers
                }
            }
        }
    }

    for (auto i : index)
    {
        results.push_back(HTMLfileNumber[i]);      // Push results to results vector
    }

}
