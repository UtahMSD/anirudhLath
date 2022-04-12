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
/*       if (size_ < 1) {
           head_ = new Node{x, nullptr};
           tail_ = head_;
       }
       else if (size_ == 1) {
           Node temp = new Node{x, nullptr};
           tail_ = temp;
           head_->next = tail_;
       }
       else {
           Node temp = tail_;
           temp.next = tail_;
           tail_ = new Node{x, nullptr};

       }*/

   }
   
   void print() {
       Node *temp = head_;
       for (int i = 0; i < size_; ++i) {
           std::cout << temp->data << "\n";
           temp = temp->next;
       }
   }

   bool dequeue( T * ret ) {
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
