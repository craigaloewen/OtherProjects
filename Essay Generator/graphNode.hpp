// DoublyLinkedList.hpp
// DoublyLinkedList implements a list using a doubly linked set of nodes.
// No memory is allocated on creation, but only as elements are added
// to the list.

#ifndef GRAPHNODE_HPP
#define GRAPHNODE_HPP

#include "DoublyLinkedList.hpp"


struct graphNode {
		
		graphNode(std::string newWord) {
			word = newWord;
		}
		
		std::string word;
		
		//DoublyLinkedList edgeList;
		
	};



#endif  //GRAPHNODE_HPP
