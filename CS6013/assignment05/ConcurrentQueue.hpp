#pragma once

////////////////////////////////////////////////////////////////////////
//
// Author: Anirudh Lath
// Date: April 11, 2022
//
// CS 6013
//
// Outline for ConcurrentQueue
//class.  Fill in the missing data, comments, etc.
//
////////////////////////////////////////////////////////////////////////

#include <iostream>

template <typename T>
class ConcurrentQueue{

public:
   ConcurrentQueue() :
      head_( new Node{ T{}, nullptr } ), size_( 0 )
   {
      tail_ = head_;
   }

   void enqueue( const T & x ) {
       std::lock_guard<std::mutex> lock(m);
       if (size_ == 0) {
           delete head_;
           head_ = new Node{x, nullptr};
           tail_ = head_;
       }
       else {
           tail_->next = new Node{x, nullptr};
           tail_ = tail_->next;
       }
       size_++;
   }
   
   void print() {
       Node *temp = head_;
       for (int i = 0; i < size_; ++i) {
           std::cout << temp->data << "\n";
           temp = temp->next;
       }
   }

   bool dequeue( T * ret ) {
       std::lock_guard<std::mutex> lock(m);
       if (size_ > 0) {
           Node *temp = head_->next;
           delete head_;
           head_ = temp;
           if (head_ != nullptr) {
               *ret = head_->data;
           } else {
               *ret = NULL;
           }
           size_--;
           return true;
       }
       else {
           return false;
       }
   }

   ~ConcurrentQueue() {
      while( head_ != nullptr ) {
         Node* temp = head_->next;
         delete head_;
         head_ = temp;
      }
   }

   int size() const { return size_; }

private:

   struct Node {
      T      data;
      Node * next;
   };

   Node * head_;
   Node * tail_;
   int    size_;
   std::mutex m;
};
