#pragma once

#include <string>
using namespace std;

class Webpage {
public:
    
    //Default Constructor
    Webpage(){
        url = "NULL";
        time = 0;
    };
    Webpage(const string& webpageUrl, const time_t& timeVisited);
    string getUrl();
    time_t getTime();

private:
    string url;
    time_t time;
};

//Passes items to variable
Webpage::Webpage(const string& webpageUrl, const time_t& timeVisited){
    url = webpageUrl;
    time = timeVisited;
}

//Function to get url
string Webpage::getUrl(){
    return url;
}

//Function to get time
time_t Webpage::getTime(){
    return time;
}

