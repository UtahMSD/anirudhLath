#pragma once

////////////////////////////////////////////////////////////////////////
//
// Author: Anirudh Lath
// Date: April 11, 2022
//
// CS 6013
//
// Outline for SerialQueue class.  Fill in the missing data, comments, etc.
//
////////////////////////////////////////////////////////////////////////

template <typename T>
class SerialQueue {

public:
   SerialQueue() :
      head_( new Node{ T{}, nullptr } ), size_( 0 )
   {
      tail_ = head_;
   }

   void enqueue( const T & x ) {
       tail_->next = new Node{x, nullptr};
       tail_ = tail_->next;
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
       Node *temp = head_;
       if(temp->next == nullptr) {
           return false;
       }
       *ret = temp->next->data;
       head_ = temp->next;
       size_--;
       delete temp;
       return true;
   }

   ~SerialQueue() {

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
};
