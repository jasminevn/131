//
//  minideque.h
//  minidequeproject
//

#ifndef minideque_h
#define minideque_h

#include <vector>
#include <stack>
#include <algorithm>
#include <string>
#include <iostream>


template <typename T>
class minideque {
private:
    std::vector<T> fronthalf_;
    std::vector<T> backhalf_;

public:
    minideque() = default;                                   // do not change, C++ defaults are ok
    minideque(const minideque<T>& other) = default;          // rule of three
    minideque& operator=(const minideque<T>& other) = default;
    ~minideque() = default;

    //returns total size of both vectors
    size_t size() const{
        return fronthalfsize() + backhalfsize();
    }
    
    //returns size of the first half
    size_t fronthalfsize() const{
        return fronthalf_.size();
    }
    
    //returns the size of the back half
    size_t backhalfsize() const{
        return backhalf_.size();
    }
    
    //returns true if the dequeue is empty
    bool empty()  const{
        return (size() == 0);
        //if (size() == 0)
        //return true;
        //else return false
    }

    // balance queue across both vectors if pop_front/back is requested on an empty vector
    // e.g., minideque has this:                  | ABCDEFG
    // after pop_front                        BCD | EFG (A discarded)
    // symmetric logic for converse case: ABCDEFG | ===> ABC | DEF (G discarded) after pop_back
    
    //Function to pop front of dequeue
    void pop_front(){
        //if front half is not empty
        if (fronthalfsize() != 0)
        {
            fronthalf_.pop_back();
        }
        //else move half elements from back half into front half
        else
        {
            for(int i = (backhalf_.size()/2); i >= 0; i--)
            {
                fronthalf_.push_back(backhalf_[i]);
                backhalf_.erase(backhalf_.begin() + i);
            }
            fronthalf_.pop_back();
        }
    }
    
    //Function to pop back of dequeue
    void pop_back(){
        //if back half is not empty
        if(backhalfsize() != 0)
        {
            backhalf_.pop_back();
        }
        //else move half elements from front half into back half
        else
        {
            for(int i = (fronthalf_.size()/2); i >= 0; i--)
            {
                backhalf_.push_back(fronthalf_[i]);
                fronthalf_.erase(fronthalf_.begin() + i);
            }
            backhalf_.pop_back();
        }
    }
    
    //Push front of dequeue
    void push_front(const T& value){
        fronthalf_.push_back(value);
    }
    
    //Push back of dequeue
    void push_back(const T& value){
        backhalf_.push_back(value);
    }

    //Return front of dequeue
    const T& front() const{
        if (!fronthalf_.empty())
        {
            return fronthalf_.back();
        }
        return backhalf_.front();
    }
    
    //Return back of dequeue
    const T& back() const{
        return backhalf_.front();
    }
    
    //Return front of dequeue
    T& front(){
        if (!fronthalf_.empty())
        {
            return fronthalf_.back();
        }
        return backhalf_.front();
    }
    
    //Return back of dequeue
    T& back(){
        return backhalf_.back();
    }

    //Operator function
    const T& operator[](size_t index) const{
        if (index >= fronthalfsize() - 1)
            return backhalf_[index - fronthalfsize()];
        else
            return fronthalf_[(fronthalfsize() - 1) - index];
    }
    //Operator function
    T& operator[](size_t index){
        if (index >= fronthalfsize())
            return backhalf_[index - fronthalfsize()];
        else
            return fronthalf_[(fronthalfsize() - 1) - index];
    }

    //Clear the entire dequeue
    void clear(){
        fronthalf_.clear();
        backhalf_.clear();
    }


    friend std::ostream& operator<<(std::ostream& os, const minideque<T>& dq) {    // do not change
        if (dq.empty()) { return os << "minideque is empty"; }

        dq.printFronthalf(os);
        os << "| ";
        dq.printBackhalf(os);
        os << ", front:" << dq.front() << ", back:" << dq.back() << ", size:" << dq.size();
    return os;
    }

    void printFronthalf(std::ostream& os=std::cout) const {                    // do not change
        if (empty()) { std::cout << "fronthalf vector is empty"; }

        for (typename std::vector<T>::const_reverse_iterator crit = fronthalf_.crbegin();
             crit != fronthalf_.crend(); ++crit) {
            os << *crit << " ";
        }
    }

    void printBackhalf(std::ostream& os=std::cout) const {                     // do not change
        if (empty()) { os << "backhalf vector is empty"; }

        for (typename std::vector<T>::const_iterator cit = backhalf_.cbegin();
             cit != backhalf_.cend(); ++cit) {
        os << *cit << " ";
        }
    }
};

#endif /* minideque_h */
