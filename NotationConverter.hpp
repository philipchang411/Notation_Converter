#include "NotationConverterInterface.hpp"
#include <iostream>
#include <sstream>

class node
{
    //doesn't need a destructor as it is done in the NotationConverter
    private: 
        node();
        std::string data; //string is all you need
        node* next;
        node* prev;

        //necessary as the helper functions are found in the NotationConverter
        friend class NotationConverter;
};

class NotationConverter : public NotationConverterInterface 
{
    public:

        void frontAddNode(std::string input);
        void pop();
        bool isEmpty();
        bool isOperator(char input);
        std::string top();
        bool validity(std::string input);

        NotationConverter();
        ~NotationConverter();

        std::string postfixToInfix(std::string inStr);
        std::string postfixToPrefix(std::string inStr);

        std::string infixToPostfix(std::string inStr);
        std::string infixToPrefix(std::string inStr);

        std::string prefixToInfix(std::string inStr);
        std::string prefixToPostfix(std::string inStr);
    
    private:
        std::string start;
        node* head; 
        node* tail;
        int listLength = 0;
        
        //By declaring it in the header, I need to clear the value of the string each time in the functions 
        std::string result;
};