#include	<iostream>
#include    <stdexcept>
#include	"GroceryCheckout.h"

using namespace std;

bool GroceryInventory::AddItem(const string& name, int quantity,
							   float price, bool taxable)
{
    //Checks to see if the item exists
    if (mymap.find(name) == mymap.end())
    {
            GroceryItem tmp(name, quantity, price, taxable);
            mymap[name] = tmp;
            return true;
    }
    else
    {
        return false;
    }
}

void GroceryInventory::CreateFromFile(const string& fileName)
{
    ifstream	file(fileName);
	string		name;
    
	float		price;
	int			quantity;
	bool		taxable;

    //If file opens
	if (file.is_open())
	{
        //Read items
		while (1)
		{
			file >> name >> quantity >> price >> taxable;
			if (!file.fail())
				AddItem(name, quantity, price, taxable);
			else
				break;
         }
        file.close();
    }
    //If file could not be opened
	else
        cout << "Could not open " + fileName << endl;

	return;
}

Receipt GroceryInventory::CreateReceipt(const string& fileName)
{
    ifstream file(fileName);
    string name;
    Receipt MyReceipt;
    
    //Set initial amounts
    MyReceipt.subtotal_ = 0.0;
    MyReceipt.taxAmount_ = 0.0;
    MyReceipt.total_ = 0.0;
    
    
    if (file.is_open()){
        //Read items
        while (1){
            file >> name;
            
            //If item is not found
            if (!file.fail()){
                it = mymap.find(name);
            if(it == mymap.end())
                    cout << "Item was not found";

            else{
                //If item is found, add element to receipt object
                ReceiptItem temp(it->second.name_,it->second.price_);
                MyReceipt.item_.push_back(temp);
                MyReceipt.subtotal_ += it->second.price_;
                it->second.quantity_--;
                
                //Add if taxable
                if(it->second.taxable_ == true)
                    MyReceipt.taxAmount_ = it->second.price_ * (_taxrate / 100);
                }
            }
            else
                break;
        }
        //Find total and close file
        MyReceipt.total_ = MyReceipt.subtotal_ + MyReceipt.taxAmount_;
        file.close();
    }
    //If file could not be opened
    else
        cout << "Could not open " + fileName << endl;
    
    return MyReceipt;
}

GroceryItem* GroceryInventory::FindItem(const string& name)
{
	//Function to find item

	it = mymap.find(name);
	if (it == mymap.end())
			return nullptr;
	else
        //return pointer of item found
		return &it->second;
}

bool GroceryInventory::RemoveItem(const string& name)
{
    //Function to remove item
    
	it = mymap.find(name);
	if (it == mymap.end())
		return false;
    else{
        //Erase item
        mymap.erase(it);
        return true;
	}
}

void GroceryInventory::SetTaxRate(float taxRate)
{
    //Returns tax rate
	_taxrate = taxRate;
}

size_t GroceryInventory::Size()
{
    //Returns size of inventory
	return mymap.size();
}
