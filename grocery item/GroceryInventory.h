#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "GroceryItem.h"
using namespace std;

class GroceryInventory {
private:
    vector<GroceryItem> _inventory;
    float _taxRate;
    
public:
    
    //Default constructor
    GroceryInventory(){
        //Nothing needed here
    };

    GroceryItem& getEntry(const string& s);
    void addEntry(const string&, const int&, const float&, const bool&);
    float getTaxRate() const;
    void setTaxRate(const float& tax);
    void createListFromFile(const string&);
    float calculateUnitRevenue() const;
    float calculateTaxRevenue() const;
    float calculateTotalRevenue() const;

    GroceryItem& operator[](const int&);
};

//Function that creates list from file
void GroceryInventory::createListFromFile(const string& filename) {
    ifstream input_file(filename);

    if (input_file.is_open()) {
        cout << "Successfully opened file " << filename << endl;
        string name;
        int quantity;
        float unit_price;
        bool taxable;
        while (input_file >> name >> quantity >> unit_price >> taxable) {
            addEntry(name, quantity, unit_price, taxable);
        }
        input_file.close();
    } else {
        throw invalid_argument("Could not open file " + filename);
    }
}

//Function that sets _taxRate variable
void GroceryInventory::setTaxRate(const float& tax){
    _taxRate = tax;
}

//Function that gets _taxRate variable
float GroceryInventory::getTaxRate() const{
    return _taxRate;
}

//Function to get entry from created vector
GroceryItem& GroceryInventory::getEntry(const string& food) {
    //For loop that checks every item in the list and compares with input
    for (int i = 0; i < _inventory.size(); i++){
        if(_inventory[i].getName() == food){
            return _inventory[i];
        }
    }
    //Throw if item is not found in the vector
    throw std::exception();
}

//Function to add entry at the end of the list given name, quanity, unit price, and taxable
void GroceryInventory::addEntry(const string& name, const int& quantity, const float& unitPrice, const bool& taxable){
    //Creates a temp object with passed information
    GroceryItem TempItem(name, quantity, unitPrice, taxable);
    //Pushes temp item into list
    _inventory.push_back(TempItem);
}

//Function to calculate unit revenue
float GroceryInventory::calculateUnitRevenue() const{
    //Set unit revenue to 0 in case function is ran again
    float _unitRevenue = 0;
    //For loop to multiply unit price and quantity and adds result to running total
    for (int i = 0; i < _inventory.size(); i++){
        _unitRevenue += _inventory[i].getQuantity() * _inventory[i].getUnitPrice();
    }
    return _unitRevenue;
}

//Function to calculate tax revenue
float GroceryInventory::calculateTaxRevenue() const{
    //Set unit revenue to 0 in case function is ran again
    float _taxRevenue = 0;
    //For loop to multiply unit price and quantity and taxrate and adds to running total
    for (int i = 0; i < _inventory.size(); i++){
        if (_inventory[i].isTaxable() == true){
            //Must divide tax rate by 100 to convert percentage form to decimal
            _taxRevenue += _inventory[i].getQuantity() * _inventory[i].getUnitPrice() * (getTaxRate() / 100);
        }
    }
    return _taxRevenue;
}

//Function to calculate total revenue by adding results form function calculateTaxRevenue and calculateUnitRevenue
float GroceryInventory::calculateTotalRevenue() const{
    return calculateTaxRevenue()+calculateUnitRevenue();
}
