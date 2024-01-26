#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE

void ULListStr::push_back(const std::string& val) {
    if (tail_ == nullptr) {  
        Item* newItem = new Item();
        newItem->val[newItem->last] = val;
        newItem->first = 0;
        newItem->last = 1;
        head_ = tail_ = newItem;
    } 
    else if (tail_->last == ARRSIZE) {  
        Item* newItem2 = new Item();
        newItem2->val[newItem2->last] = val;
        newItem2->first = 0;
        newItem2->last = 1;
        Item* temp = tail_;
        newItem2->prev = temp;
        newItem2->next = nullptr;
        temp->next = newItem2;
        tail_ = newItem2;
    }
    else{
      tail_->val[tail_->last] = val;
      tail_->last++;
    }
    size_++;
}

void ULListStr::push_front(const std::string& val) {
    if (head_ == nullptr) {  
    head_ = new Item();
    head_->first = ARRSIZE - 1;
    head_->val[head_->first] = val;
    head_->last = ARRSIZE;
    tail_ = head_;
    } 
    else {
        if (head_->first == 0) {  
            Item* newItem = new Item();
            newItem->first = ARRSIZE - 1;
            newItem->val[newItem->first] = val;
            newItem->last = ARRSIZE;
            newItem->next = head_;
            head_->prev = newItem;
            head_ = newItem;
        } 
        else {
            head_->first--;
            head_->val[head_->first] = val;
        }
    }
    size_++;
}

void ULListStr::pop_back() {
    if (empty()) {
        throw std::out_of_range("List is empty");
    }
    tail_->last--;
    size_--;
    if (tail_->last == tail_->first) {  
        Item* temp = tail_;
        tail_ = tail_->prev;
        delete temp;
        if (tail_) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }
    }
}

void ULListStr::pop_front() {
    if (empty()) {
        throw std::out_of_range("List is empty");
    }
    head_->first++;
    size_--;
    if (head_->first == head_->last) {  
        Item* temp = head_;
        head_ = head_->next;
        if (head_) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }
        delete temp;
    }
}

std::string const & ULListStr::back() const {
    if (empty()) {
        throw std::out_of_range("List is empty");
    }
    return tail_->val[tail_->last - 1];
}

std::string const & ULListStr::front() const {
    if (empty()) {
        throw std::out_of_range("List is empty");
    }
    return head_->val[head_->first];
}

std::string* ULListStr::getValAtLoc(size_t loc) const {
    if (loc >= size_) {
        return nullptr;  
    }

    Item* current = head_;
    while (current != nullptr) {
        size_t currentSize = current->last - current->first;
        if (loc < currentSize) {
            return &current->val[current->first + loc]; 
        }
        loc -= currentSize;
        current = current->next;
    }

    return nullptr; 
}







void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
