#include <iostream>
#include <stack>
#include <string>
#include <cmath>

using namespace std;

class Stack {
public:
    stack<int> data;

    bool isEmpty() {
        return data.empty();
    }

    void push(int value) {
        data.push(value);
    }

    int pop() {
        int top = data.top();
        data.pop();
        return top;
    }

    int peek() {
        return data.top();
    }
};

int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return -1;
    }
}

string infixToPostfix(string expression) {
    Stack operators;
    string postfix;

    for (char token : expression) {
        if (isdigit(token)) {
            postfix += token;
        } else if (token == '(') {
            operators.push(token);
        } else if (token == ')') {
            while (!operators.isEmpty() && operators.peek() != '(') {
                postfix += operators.pop();
            }
            operators.pop(); 
        } else {
            while (!operators.isEmpty() && precedence(token) <= precedence(operators.peek())) {
                postfix += operators.pop();
            }
            operators.push(token);
        }
    }

    while (!operators.isEmpty()) {
        postfix += operators.pop();
    }

    return postfix;
}

int evaluatePostfix(string postfix) {
    Stack operands;

    for (char token : postfix) {
        if (isdigit(token)) {
            operands.push(token - '0'); 
        } else {
            int operand2 = operands.pop();
            int operand1 = operands.pop();
            switch (token) {
                case '+':
                    operands.push(operand1 + operand2);
                    break;
                case '-':
                    operands.push(operand1 - operand2);
                    break;
                case '*':
                    operands.push(operand1 * operand2);
                    break;
                case '/':
                    operands.push(operand1 / operand2);
                    break;
                case '^':
                    operands.push(pow(operand1, operand2)); 
                    break;
                default:
                    cerr << "Invalid operator: " << token << endl;
                    return 0;
            }
        }
    }

    return operands.pop();
}

int main() {
    while (true) {
        cout << "Enter an operation (or 'q' to quit): ";
        string expression;
        getline(cin, expression);

        if (expression == "q") {
            break;
        }

        string postfix = infixToPostfix(expression);
        int result = evaluatePostfix(postfix);
        cout << "Result: " << result << endl;
    }

    return 0;
}