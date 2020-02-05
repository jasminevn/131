#pragma once

#include <string>
using namespace std;

class GroceryItem {
private:
    string _name;
    int _quantity;
    float _unitPrice;
    bool _taxable;

public:
    
    //Default constructor
    GroceryItem(){
        _name = "NULL";
        _quantity = 0;
        _unitPrice = 0;
        _taxable = true;
    };
    
    //Pass items into variables
    GroceryItem(const string& name, const int& quant, const float& price, const bool& taxable){
        _name = name;
        _quantity = quant;
        _unitPrice = price;
        _taxable = taxable;
    }

    //Function to get name
    string getName() const{
        return _name;
    };
    //Function to set name
    void setName(const string& name){
        _name = name;
    };
    //Function to get quantity
    int getQuantity() const{
        return _quantity;
    };
    //Function to set quantity
    void setQuantity(const int& q){
        _quantity = q;
    };
    //Function to get unit price
    float getUnitPrice() const{
        return _unitPrice;
    };
    //Function to set unit price
    void setUnitPrice(const float& price){
        _unitPrice = price;
    };
    //Function to get if taxable
    bool isTaxable() const{
        return _taxable;
    };
    //Function to set if taxable
    void setTaxable(const bool& tax){
        _taxable = tax;
    };
};
