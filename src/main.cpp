#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cpr/cpr.h>

std::map<std::string, std::string> arguments;
std::map<std::string, std::string>::iterator it;

void requestGet()
{
    std::string arg = "?";
    
    for (it = arguments.begin(); it != arguments.end(); it++)
    {
        if (it != arguments.begin())
        {
            arg += "&";
        }
        arg += it->first + "=" + it->second;
                  
    }
    std::string requestWithArguments = "http://httpbin.org/get" + arg;
    cpr::Response r = cpr::Get(cpr::Url(requestWithArguments));
    std::cout << r.text << std::endl;
}

void requestPost()
{
    std::vector<cpr::Pair> pairs;
    int i = 0;
    for (auto it = arguments.begin(); it != arguments.end(); ++it, ++i)
    {
        cpr::Pair pair(it->first, it->second);
        pairs.push_back(pair);
    }

    auto responce = cpr::Post(cpr::Url("http://httpbin.org/post"),
        cpr::Payload(pairs.begin(), pairs.end())).text;

    std::cout << responce << std::endl;
}

int main()
{
    bool exit = false;
    do
    {
        std::cout << "Enter the argument and value separated by a space OR: " << std::endl;
        std::cout << "Enter a request: post or get: " << std::endl;

        std::string entered;
        
        std::getline(std::cin, entered);
        size_t spaceIndex = entered.find(' ');
        std::string argument = entered.substr(0, spaceIndex);
        std::string value = entered.substr(spaceIndex + 1, entered.size() - spaceIndex);

        system("cls");

        size_t countSpace = std::count(entered.begin(), entered.end(), ' ');
        if (countSpace == 1)
        {    
             arguments.insert(make_pair(entered.substr(0, spaceIndex), entered.substr(spaceIndex + 1, entered.size() - spaceIndex)));
             std::cout << "Argument and value added" << std::endl;    
        }
        else if (countSpace == 0)
        {
            if (argument == "post")
            {
                requestPost();
                exit = true;
            }
            else if (argument == "get")
            {
                requestGet();
                exit = true;
            }
            else
            {
                std::cerr << "Incorrect request" << std::endl;
            }       
        }
        else
        {
            std::cerr << "Incorrect enter" << std::endl;
        }       
    } while (!exit);
}