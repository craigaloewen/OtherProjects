#include "DoublyLinkedList.hpp"
#include <iostream>


DoublyLinkedList::Node::Node(DataType data)
{
                                      this->value = data;
                                      this->prev = NULL;
                                      
}

DoublyLinkedList::DoublyLinkedList()
{
	this->size_ = 0;
	(*this).head_ = NULL;
	(*this).tail_ = NULL;
}

DoublyLinkedList::~DoublyLinkedList()
{
	
	if (head_ != NULL) {
    for (int i = 1; i < size_; i++) {
        Node* visitor = head_;
        head_ = head_->next;
        delete visitor;
        }   
    delete head_;              
    }
}

bool DoublyLinkedList::empty() const
{
	return this->size_ == 0;
}

unsigned int DoublyLinkedList::size() const
{
	return this->size_;
}

void DoublyLinkedList::print() const
{
	std::cout << "--Start of Linked List--" << std::endl;
	Node *visitor = this->head_;
	if (visitor == NULL) {
       std::cout << "The list is empty.\n";
    } else {
	   std::cout << "[";           
	   do {
		    std::cout << " " << visitor->value;
		    visitor = visitor->next;
	   } while (visitor != NULL);
    }
    std::cout << " ]" << std::endl;
    std::cout << "--End of Linked List--" << std::endl;
}

bool DoublyLinkedList::insert_front(DataType value)
{
	if (size_ == CAPACITY) {
		return false;
	}
	Node *n;
	n = new Node(value);
	n->prev = NULL;
	if (this->empty()) {
		this->head_ = n;
		this->tail_ = n;
		this->size_ = 1;
		n->next = NULL;
	} else {
		n->next = this->head_;
		this->head_ = n;
		this->size_++;
	}
	return true;
}

bool DoublyLinkedList::remove_front()
{
	if (this->size_ == 0) {
		return false;
	} else if (this->size_ == 1) {
		delete this->head_;
		this->head_ = NULL;
		this->size_ = 0;
	} else {
		Node *temp = this->head_;
		this->head_ = this->head_->next;
		delete temp;
		this->size_--;
	}
	return true;
}

bool DoublyLinkedList::insert_back(DataType value)
{
	if (size_ == CAPACITY) {
		return false;
	}
	Node *n;
	n = new Node(value);
	n->next = NULL;
	if (this->size_ == 0) {
		this->head_ = n;
		this->tail_ = n;
		this->size_ = 1;
		n->prev = NULL;
	} else {
		n->prev = this->tail_;
		this->tail_->next = n;
		this->tail_ = n;
		this->size_++;
	}
	return true;
}

bool DoublyLinkedList::remove_back()
{
	if (this->size_ == 0) {
		return false;
	} else if (this->size_ == 1) {
		delete(this->head_);
		this->head_ = NULL;
		this->tail_ = NULL;
		this->size_ = 0;
	} else {
		Node *temp = this->tail_;
		this->tail_ = this->tail_->prev;
		delete(temp);
		this->size_--;
	}
	return true;
}

bool DoublyLinkedList::insert(DataType value, unsigned int pos)
{
	if (size_ == CAPACITY) {
		return false;
	}
	if (pos > this->size_) {
		return false;
	} else if (pos == 0){
		return this->insert_front(value);
	} else if (pos == this->size_) {
		return this->insert_back(value);
	}
	Node *n;
	n = new Node(value);
	//get item before insert position
	Node *visitor = this->getNode(pos - 1);
	n->next = visitor->next;
	n->prev = visitor;
	visitor->next->prev = n;
	visitor->next = n;
	this->size_++;
	return true;
}

bool DoublyLinkedList::remove(unsigned int pos)
{
	if (pos > this->size_ - 1) {
		return false;
	} else if (pos == 0){
		return this->remove_front();
	} else if (pos == this->size_ - 1) {
		return this->remove_back();
	}
	Node *temp = this->getNode(pos);
	temp->next->prev = temp->prev;
	temp->prev->next = temp->next;
	this->size_--;
	delete temp;
	return true;
}

unsigned int DoublyLinkedList::search(DataType value) const
{
	Node *visitor = this->head_;
	for (int i = 0; i < this->size_; i++) {
		if (visitor->value == value) {
			return i;
		} else {
			visitor = visitor->next;
		}
	}
	return this->size_;
}

DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int pos) const
{
	if (size_ == 0) {
		return 0;
	}
	if (pos >= size_) {
		pos = size_-1;
	}
	Node *n = this->getNode(pos);
	if (n == NULL) {
		return this->size_;
	} else {
		return n->value;
	}
}

bool DoublyLinkedList::replace(unsigned int pos, DataType value)
{
	Node *n = this->getNode(pos);
	if (n == NULL) {
		return false;
	} else {
		n->value = value;
		return true;
	}
}

bool DoublyLinkedList::shorten(unsigned int pos) {
	if (head_ == NULL) {
		return false;
	}
	if (pos >= size_-1) {
		return false;
	}
	Node* visitor = head_;
	for (int i = 0; i < pos; i++) {
    visitor = visitor->next;
	std::cout << "Deleting: " << visitor->prev << std::endl;
	delete visitor->prev;
	size_--;
	}
	head_=visitor;
	head_->prev = NULL;
	return true;
	
}

DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int pos) const
{
	if (pos > this->size_ - 1) {
		return NULL;
	}
	Node *visitor = this->head_;
	for (int i = 0; i < pos; i++) {
		visitor = visitor->next;
	}
	return visitor;
}
bool DoublyLinkedList::full() const
{
	return this->size_ == CAPACITY;
}
