#include <iostream>
#include <cstdlib>
#include <iostream>
#include "MyStack.hpp"

using namespace std;

MyStack::MyStack()
{
	head = NULL;
}

MyStack::~MyStack()
{
	while (head != nullptr) {
		pop();
	}

}

bool MyStack::isEmpty()
{
	if (head != nullptr) {
		return false;
	}
	return true;
}

void MyStack::push(int val)
{
	Node* tmp = new Node{val, head};
	head = tmp;
}

void MyStack::pop()
{   
	Node* tmp = head;
	if (isEmpty()) {
		cout << "Stack empty, cannot pop an item!" << endl;
	} else {
		head = head->next;
		delete tmp;
	}
	
}

Node* MyStack::peek()
{	
	if (isEmpty()) {
		cout << "Stack empty, cannot peek!" << endl;
	} else {
		return head;
	}
	
}
