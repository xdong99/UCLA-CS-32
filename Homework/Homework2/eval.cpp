#include<iostream>
#include<string>
#include<cctype>
#include<stack>
#include<cassert>
#include "Map.h"
using namespace std;

const char DIVIDE = '/';
const char ADD = '+';
const char SUBTRACT = '-';
const char MULTIPLY = '*';
const char OPEN_PAREN = '(';
const char CLOSED_PAREN = ')';

//Self-defined helper functions
string cleanSpaces(string infix);
bool valuesInMap(string infix, const Map& values);
bool isValidInfix(string infix);
void convertToPf(string infix, string& postfix);
bool operatorPrec(char first, char second);
bool isOperator(char x);
bool isOperand(char y);
bool isParenthesis(char x);

//Evaluate function
int evaluate(string infix, const Map& values, string& postfix, int& result) 
{
    if (!isValidInfix(infix)) 
    {
        return 1;
    }
    else 
    {
        convertToPf(infix, postfix);
        if (!valuesInMap(infix, values)) 
        {
            return 2;
        }
        else 
        {
            stack<int> operands;
            for (int i = 0; i < postfix.size(); i++) 
            {
                if (isOperand(postfix[i])) 
                {
                    int value;
                    values.get(postfix[i], value);
                    operands.push(value);
                }
                else 
                {
                    int operand2 = operands.top();
                    operands.pop();
                    int operand1 = operands.top();
                    operands.pop();
                    int answer;
                    switch (postfix[i]) 
                    {
                    case ADD:
                        answer = operand1 + operand2;
                        break;
                    case SUBTRACT:
                        answer = operand1 - operand2;
                        break;
                    case MULTIPLY:
                        answer = operand1 * operand2;
                        break;
                    case DIVIDE:
                        if (operand2 == 0) //If divided by 0
                        {
                            return 3;
                        }
                        else 
                        {
                            answer = operand1 / operand2;
                            break;
                        }
                    }
                    operands.push(answer);
                }
            }
            result = operands.top();
            return 0;
        }
    }
}

void convertToPf(string infix, string& postfix) 
{
    infix = cleanSpaces(infix);
    postfix = "";
    stack<char> operators;
    for (int i = 0; i < infix.size(); i++) 
    {
        if (isOperand(infix[i])) 
        {
            postfix += infix[i];
            continue;
        }
        switch (infix[i]) 
        {
        // parentheses cases
        case OPEN_PAREN:
            operators.push(infix[i]);
            break;
        case CLOSED_PAREN:
            //Closed parenthesis cannot be the first, cannot directly follow an open parenthesis or an operator
            while (!operators.empty() && operators.top() != OPEN_PAREN && isOperator(operators.top())) 
            {
                postfix += operators.top();
                operators.pop();
            }
            operators.pop();
            break;
        // operator cases
        case DIVIDE:
        case ADD:
        case SUBTRACT:
        case MULTIPLY:
            while (!operators.empty()
                && operators.top() != OPEN_PAREN
                && operatorPrec(infix[i], operators.top())) 
            {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(infix[i]);
            break;
        }
    }
    while (!operators.empty()) 
    {
        postfix += operators.top();
        operators.pop();
    }
}

string cleanSpaces(string infix) 
{
    //Clean infix by moving spaces and storing in a new string
    string newInfix;
    for (int i = 0; i < infix.size(); i++) 
    {
        if (infix[i] != ' ') 
        {
            newInfix += infix[i];
        }
    }
    return newInfix;
}

bool valuesInMap(string infix, const Map& values) 
{
    for (int i = 0; i < infix.size(); i++) 
    {
        char c = infix[i];
        if (isalpha(c) && !values.contains(c)) 
        {
            return false;
        }
    }
    return true;
}

bool isValidInfix(string infix) 
{
    string testInfix = cleanSpaces(infix);

    if (testInfix.size() == 0) return false;                                //If empty
    if (testInfix.size() == 1 && isOperator(testInfix[0])) return false;    //If only one operator

    //Ensure the number of each type is valid
    int operatorCount = 0;
    int leftParenthesisCount = 0;
    int rightParenthesisCount = 0;
    int operandCount = 0;

    for (int i = 0; i < testInfix.size(); i++) 
    {
        char x = testInfix[i];
        if (!isOperand(x) && !isOperator(x) && !isParenthesis(x)) 
        {
            return false;
        }
        if (isOperator(x) || isParenthesis(x)) 
        {
            if (x == OPEN_PAREN) 
            {
                leftParenthesisCount++;
            }
            else if (x == CLOSED_PAREN) 
            {
                rightParenthesisCount++;
            }
            else
            {
                operatorCount++;
            }
        }
        if (isOperand(x)) 
        {
            operandCount++;
        }
    }

    if (leftParenthesisCount != rightParenthesisCount
        || operatorCount != operandCount - 1
        || operandCount < 1) 
    {
        return false;
    }

    // check that syntax in correct ordering
    for (int i = 0; i < testInfix.size() - 1; i++) 
    {
        char current = testInfix[i];
        char next = testInfix[i + 1];
        if (isOperator(current) && isOperator(next)) 
        {      
            return false;
        }
        if (isOperand(current) && isOperand(next)) 
        {       
            return false;
        }
        if (isParenthesis(current) && isOperator(next)) 
        {
            return false;
        }
        if (current == OPEN_PAREN && next == CLOSED_PAREN) 
        {
            return false;
        }
    }

    // check parentheses in right order
    string onlyParentheses;
    for (int i = 0; i < testInfix.size(); i++) 
    {
        if (isParenthesis(testInfix[i])) 
        {
            onlyParentheses += testInfix[i];
        }
    }
    if (onlyParentheses.size() != 0 
        && (onlyParentheses[0] != OPEN_PAREN 
        || onlyParentheses[onlyParentheses.size() - 1] != CLOSED_PAREN)) 
    {
        return false;
    }

    return true;
}

bool operatorPrec(char first, char second) 
{
    if ((first == ADD || first == SUBTRACT) 
        && (second == ADD || second == SUBTRACT)) 
    {
        return true;
    }
    if ((first == ADD || first == SUBTRACT) 
        && (second == MULTIPLY || second == DIVIDE)) 
    {
        return true;
    }
    if ((first == MULTIPLY || first == DIVIDE) 
        && (second == ADD || second == SUBTRACT)) 
    {
        return false;
    }
    return true;
}

bool isOperator(char x)
{
    return (x == ADD || x == SUBTRACT || x == MULTIPLY || x == DIVIDE);
}

bool isParenthesis(char x) {
    return (x == OPEN_PAREN || x == CLOSED_PAREN);
}

bool isOperand(char y) {
    return (isalpha(y) && islower(y));
}


//int main()
//{
//    char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
//    int  vals[] = { 3,  -9,   6,   2,   4,   1 };
//    Map m;
//    for (int k = 0; vars[k] != '#'; k++)
//        m.insert(vars[k], vals[k]);
//    string pf;
//    int answer;
//    assert(evaluate("a+ e", m, pf, answer) == 0 &&
//        pf == "ae+" && answer == -6);
//    answer = 999;
//    assert(evaluate("", m, pf, answer) == 1 && answer == 999);
//    assert(evaluate("a+", m, pf, answer) == 1 && answer == 999);
//    assert(evaluate("a i", m, pf, answer) == 1 && answer == 999);
//    assert(evaluate("ai", m, pf, answer) == 1 && answer == 999);
//    assert(evaluate("()", m, pf, answer) == 1 && answer == 999);
//    assert(evaluate("()o", m, pf, answer) == 1 && answer == 999);
//    assert(evaluate("y(o+u)", m, pf, answer) == 1 && answer == 999);
//    assert(evaluate("y(*o)", m, pf, answer) == 1 && answer == 999);
//    assert(evaluate("a+E", m, pf, answer) == 1 && answer == 999);
//    assert(evaluate("(a+(i-o)", m, pf, answer) == 1 && answer == 999);
//    // unary operators not allowed:
//    assert(evaluate("-a", m, pf, answer) == 1 && answer == 999);
//    assert(evaluate("a*b", m, pf, answer) == 2 &&
//        pf == "ab*" && answer == 999);
//    assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0 &&
//        pf == "yoau-*+" && answer == -1);
//    answer = 999;
//    assert(evaluate("o/(y-y)", m, pf, answer) == 3 &&
//        pf == "oyy-/" && answer == 999);
//    assert(evaluate(" a  ", m, pf, answer) == 0 &&
//        pf == "a" && answer == 3);
//    assert(evaluate("((a))", m, pf, answer) == 0 &&
//        pf == "a" && answer == 3);
//    cout << "Passed all tests" << endl;
//}