#include "MyQueue.hpp"

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

MyQueue::MyQueue(){
    queueFront = -1;
	queueEnd = -1;
}

bool MyQueue::isEmpty(){
	if (queueFront == -1) {
    	return true;
	}
	return false;

}

bool MyQueue::isFull(){
	if (counter == SIZE) {
    	return true;
	}
	return false;
}

void MyQueue::enqueue(char ch){
	if (isFull()) {
		cout << "Queue full, cannot add!" << endl;
	} else {
		if (isEmpty()) {
			queueFront = 0;
			queueEnd = 0;
			queue[queueEnd] = ch;
		} else if (queueEnd == SIZE - 1) {
			queueEnd = 0;
			queue[0] = ch;
		} else {
			queueEnd++;
			queue[queueEnd] = ch;
		}
		counter = counter + 1;
	}
}


void MyQueue::dequeue(){
	if (isEmpty()) {
		cout << "Queue empty, cannot dequeue!" << endl;
	} else {
		if (queueFront == queueEnd) {
			queueFront = -1;
			queueEnd = -1;
		} else if (queueFront == SIZE - 1) {
			queueFront = 0;
		} else {
			queueFront = queueFront + 1; 
		}
		counter--;
	}
}


char MyQueue::peek(){
	if (isEmpty()) {
		cout << "Queue empty, cannot peek!" << endl;
		return '\0';
	} 
	return queue[queueFront];
}

int MyQueue::queueSize(){
    if (!isEmpty()) {
		return counter;
	}
	return 0;
}
