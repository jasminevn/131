#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <stdexcept>
#include "Webpage.h"
using namespace std;

class BrowserHistory {
public:
    
    //Default constructor
    BrowserHistory(){
        navPos = navHistory.begin();
        numSites = 0;
    };

    void visitSite(Webpage newSite);
    string back();
    string forward();

    void readHistory(string fileName);

    string getUrl();
    size_t getNavSize();
    list<Webpage> getSitesVisited();

private:
    list<Webpage> navHistory;
    list<Webpage>::iterator navPos;
    list<Webpage> sitesVisited;
    int numSites;
};


//Enters new site to put in navHistory
void BrowserHistory::visitSite(Webpage newSite){
    //If the website not the most forward, delete all forward websites
    while(navPos != --navHistory.end()){
        navHistory.pop_back();
    }
    //Then push newsites to both lists
    navHistory.push_back(newSite);
    sitesVisited.push_back(newSite);
    navPos++;
}

//Function to go backwards from position page
string BrowserHistory::back(){
    navPos--;
    return navPos->getUrl();
}

//Function to go forward from history to the next page
string BrowserHistory::forward(){
    navPos++;
    return navPos->getUrl();
};

//Returns the url of the current website
string BrowserHistory::getUrl(){
    //Throw if there is no history
    if(navHistory.empty()){
        throw std::logic_error("Empty history");
    }
    return navPos->getUrl();
}

//Return size of navigation history
size_t BrowserHistory::getNavSize(){
    return navHistory.size();
}

//Returns the sites visited
list<Webpage> BrowserHistory::getSitesVisited(){
    return sitesVisited;
}

void BrowserHistory::readHistory(string fileName) {
    string temp;
    int newTime;
    Webpage newSite;
    ifstream inFile(fileName.c_str());

    while(inFile >> temp) {
        if(temp == "new") {
            inFile >> temp >> newTime;
            newSite = Webpage(temp, time_t(newTime));
            visitSite(newSite);
        } else if(temp == "back") {
            back();
        } else if(temp == "forward") {
            forward();
        } else {
            throw logic_error("invalid command");
        }
    }
}
