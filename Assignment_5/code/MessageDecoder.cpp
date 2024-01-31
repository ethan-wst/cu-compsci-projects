#include <iostream>
#include <cstdlib>
#include "MessageDecoder.hpp"

using namespace std;
# define SIZE 50

MessageDecoder::MessageDecoder()
{
	my_queue = new MyQueue();
	my_stack = new MyStack();
}

MessageDecoder::~MessageDecoder()
{
    delete my_queue;
    delete my_stack;	
}

/*
    generate_operator_queue(string jumbled_str)

    Takes the jumbled string as the input parameter and stores all the allowed operators in my_queue
*/
void MessageDecoder::generate_operator_queue(std::string jumbled_str){
    int length = jumbled_str.length();
    for (int i = 0; i < length; i++) {
        if (jumbled_str[i] == '+' || jumbled_str[i] == '-'  || jumbled_str[i] == '*' ) {
            my_queue -> enqueue(jumbled_str[i]);
        }
    }
}    

/*
    generate_postfix(string jumbled_str)

    Takes the jumbled string as the input parameter and computes a postfix expression using the populated my_queue
    returns a postfix expression
*/
string MessageDecoder::generate_postfix(std::string jumbled_str){

	string postfix = "";
    int length = jumbled_str.length();
    int count = 0;

    for (int i = 0; i < length; i++) {

        if (std::isdigit(jumbled_str[i])) {

            if (count < 2) {
                postfix+=jumbled_str[i];
                count++;

            } else {
                postfix = postfix + (my_queue -> peek());
                my_queue -> dequeue();
                postfix+=jumbled_str[i];
                count = 1;
            }
        }
    } 
    while (!my_queue->isEmpty()) {
        postfix = postfix + (my_queue -> peek());
        my_queue -> dequeue();
    }

    return postfix;
}

/* 
    evaluate_postfix(string postfix) 

    Takes the post fix string as an input parameter and evaluates the post fix string. 
    returns an integer after evaluating the postfix expression
*/

int MessageDecoder::evaluate_postfix(std::string postfix){
    int length = postfix.length();
    int val1 = 0;
    int val2 = 0;

    for (int i = 0 ; i < length ; i++) {

        if (std::isdigit(postfix[i])) {
            my_stack -> push(postfix[i] - '0');
            
         } else {
            val2 = my_stack -> peek() -> val;
            my_stack -> pop();
            val1 = my_stack -> peek() -> val;
            my_stack -> pop();
        
            if (postfix[i] == '+') {
                my_stack -> push((val1 + val2));
            } else if (postfix[i] == '-') {
                my_stack -> push((val1 - val2));
            } else {
                my_stack -> push((val1 * val2));
            }
        
        }
    } 

    return (my_stack -> peek()) -> val;
}

//For Testing purposes only!
MyQueue* MessageDecoder::getQueue(){
    return my_queue;
}

//For Testing purposes only!
MyStack* MessageDecoder::getStack(){
    return my_stack;
}