#include "NotationConverter.hpp"
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <algorithm>

//Constuctor that just sets the string in the node as empty
node::node()
{
    data = " ";
}

//Just creates the head and tail of the node.
NotationConverter::NotationConverter()
{
    start = " ";
    head = nullptr;
    tail=nullptr;
}

//Utilizes the pop() to deallocate the list
NotationConverter::~NotationConverter()
{
    while(listLength != 0 )
        pop();
    delete head;
    delete tail;
}

std::string NotationConverter::infixToPostfix(std::string inStr)
{
    if(validity(inStr) == false)
        throw "Invalid Input";

    result = " ";   //Necessary to clear out the string. 

    start = inStr; //Just uses a another copy

    for(int i = 0; (unsigned) i < start.length(); i++)
    {
        if(start[i] == ' ')
            continue; //Disregards the spaces

    //Don't need to do anything with the operands. Just output them
        else if(isalpha(start[i]))
        {
            std::stringstream temp; //stringstreams are buffers to allow for the character to become a string 
            temp << start[i];
            result = result + temp.str() + " ";
            continue; 
        }
    
    //Stores the open parenthesis
        else if(start[i] == '(')
        {
            std::stringstream temp;
            temp << start[i];
            frontAddNode(temp.str());  
        }

    //Assumes that the open parenthesis and the operations has been stored. Prints until it finds the '('
        else if(start[i] == ')')
        {
            while(top() != "(")
            {
                result = result + top() + " ";
                pop();
            }
            pop(); //removes the '('
        }
        
        //stores the operators
        else
        {
            if(top() == "(" || isEmpty())
            {
                std::stringstream temp;
                temp << start[i];
                frontAddNode(temp.str());
            }
        }
    }
    return result;
}

std::string NotationConverter::infixToPrefix(std::string inStr)
{
    if(validity(inStr) == false)
        throw "Invalid Input";
    
    result = " ";
    start = inStr;
    reverse(start.begin(), start.end()); //Reverse the string to begin with 

    //This is responsible for swapping the parenthesis
    for(int i = 0; (unsigned)i < start.length(); i++)
    {
        if(start[i] == '(')
            start[i] = ')';
        else if(start[i] == ')')
            start[i] = '(';     
    }

    result = infixToPostfix(start); //Utilize the other function

    reverse(result.begin(), result.end()); //reverse it back
    return result;
}

std::string NotationConverter::postfixToInfix(std::string inStr)
{
    if(validity(inStr) == false)
        throw "Invalid Input";

    result = " "; //clear the string
    start = inStr;

    for(int i = 0; (unsigned)i<start.length(); i++)
    {
        if(isalpha(start[i]))
        {
            std::stringstream temp;
            temp <<start[i];
            frontAddNode(temp.str());
        }
        if(isOperator(start[i]) == true)
        {
            //temporary variables needed to house the strings   
            std::string temp1 = top();
            pop();
            std::string temp2 = top();
            pop();
            
            //it's necessary to create the parenthesis
            result = "(" + temp2 +" "+ start[i] +" " + temp1+ ")"; 
            frontAddNode(result);
        }
    }
    return result;
}

std::string NotationConverter::prefixToPostfix(std::string inStr)
{
    if(validity(inStr) == false)
        throw "Invalid Input";

    start = inStr;
    result = " ";

    //reverse it again 
    reverse(start.begin(), start.end());

    for(int i = 0; (unsigned)i<start.length(); i++)
    {
        if(isalpha(start[i]))
        {
            std::stringstream temp;
            temp << start[i];
            frontAddNode(temp.str());
        }

        //same logic as post to infix but without the parenthesis
        if(isOperator(start[i]) == true)
        {
            //necessary temporary strings to hold the top of the deque
            std::string temp1 = top();
            pop();
            std::string temp2 = top();
            pop();
            result = temp1 +" " + temp2 + " "+ start[i];
            frontAddNode(result);
        }
    }
    return result;
}

std::string NotationConverter::postfixToPrefix(std::string inStr)
{
    return NotationConverter::infixToPrefix(NotationConverter::postfixToInfix(inStr));    
}   

std::string NotationConverter::prefixToInfix(std::string inStr)
{
    return NotationConverter::postfixToInfix(NotationConverter::prefixToPostfix(inStr));
}

void NotationConverter::frontAddNode(std::string input)
{
    node* newNode = new node;
    newNode->data = input;

    //accounts for empty lists. Necessary. 
    if(head == nullptr)
    {
        newNode->next = nullptr;
        newNode->prev = nullptr;
        head = newNode;
        tail = newNode;
        listLength++;
    }

    //connects the node to the existing list 
    else
    {
        newNode->prev = nullptr;
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        listLength++;
        //important to have the listlength increased 
    }
}

//deletes the head of the list 
void NotationConverter::pop()
{
    node* deletion = new node; 
    deletion = head; 

     //responsible for deconstructing the list
    if(tail == head)
    {
        head = nullptr;
        tail = nullptr;
    }

    //change what head is pointing to
    else
    {
        head = head->next;
        head->prev = nullptr;
    }

    //important to reduce listlength
    listLength--;
    delete deletion;
}


//returns the top node
std::string NotationConverter::top()
{
    if(head == nullptr)
        return " "; //accounts for a no list 
    else
        return head->data; 
}

//self explanatory. Just tests to see if the character is a valir operator or not
bool NotationConverter::isOperator(char input)
{
    if(input == '+' || input == '-' || input == '/' || input == '*')
        return true;
    else
        return false;
}

//tests the listLength to see if it's empty or not 
bool NotationConverter::isEmpty()
{
    if(listLength == 0)
        return true;
    else
        return false;
}

//throw case function. Tests to see if the string is valid.
bool NotationConverter::validity(std::string input)
{
    for(int i = 0; (unsigned) i< input.length(); i++)
    {
        if((input[i] == ' ') || (input[i] == '(') || (input[i] == ')') || isalpha(input[i]) || isOperator(input[i]))
            continue;
        else return false;
    }
    return true;
}