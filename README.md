# Notation_Converter
Implement a Deque (Double-Ended Queue) and use that data structure to write a class that can convert between the three common mathematical notation for arithmetic.

The three notations are:
Postfix (Reverse Polish) Notation:
Operators are written after operands A B - C + == (A - B) + C Infix Notation:
The standard notation we use where the operator is between the operands. Prefix (Polish) Notation:
Operators are written before operands: * - A B C == (A - B) * C

Example: 
 
NotationConverter nc;
std::string examplePost = "c d / a b * r r * / *";
nc.postfixToInfix(examplePost)  // Infix: ((c / d) * ((a * b) / (r * r)))
nc.postfixToPrefix(examplePost) // Prefix * / c d / * a b * r r
std::string examplePre = "* + A B - C D”;
nc.prefixToInfix(examplePre)  // Infix: ((A + B) * (C - D))
nc.prefixToPostfix(examplePre) // Postfix A B + C D - *
std::string exampleInfix = "((a / f) ((a * b) / (r * r)))";
nc.infixToPostfix(exampleInfix) // Postfix: a f / a b * r r * /
nc.infixToPrefix(exampleInfix)  // Prefix / a f / * a b * r r

**Class Project**