//
// Created by 马睿赢 on 2023/2/21.
//
#include "stack_vector.h"
const char pri[9][9] = {
        {'>', '>', '<', '<', '<', '<', '<', '>', '>'},
        {'>', '>', '<', '<', '<', '<', '<', '>', '>'},
        {'>', '>', '>', '>', '<', '<', '<', '>', '>'},
        {'>', '>', '>', '>', '<', '<', '<', '>', '>'},
        {'>', '>', '>', '>', '>', '<', '<', '>', '>'},
        {'>', '>', '>', '>', '>', '>', ' ', '>', '>'},
        {'<', '<', '<', '<', '<', '<', '<', '=', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'<', '<', '<', '<', '<', '<', '<', ' ', '='}
};
inline bool isdigit (char c) {
    return (('0' <= c ) && (c <= '9'));
}
void readNumber(char* &S, Stack<double> &opnd); // must use reference '&' for S and opnd
inline int optr_2_index (char& optr) {
    switch (optr) {
        case '+': return 0;
        case '-': return 1;
        case '*': return 2;
        case '/': return 3;
        case '^': return 4;
        case '!': return 5;
        case '(': return 6;
        case ')': return 7;
        case '\0': return 8;
        default: return -1;
    }
}
inline char priority(char& top_optr, char& cur_optr) {
    return pri[optr_2_index(top_optr)][optr_2_index(cur_optr)];
}
double calcu (char optr, double opnd);
double calcu (char optr, double opnd_l, double opnd_r) ;
double evaluate(char* S, char* RPN);

void readNumber(char* &S, Stack<double> &opnd) {
    double num = 0;
    while (isdigit(*S)) {
        num = num*10 + (double)((*S) - '0');
        S++;
    }
    opnd.push(num);
    return; // now S points to a non-digit char
}
double calcu (char optr, double opnd) {
    double res = 1;
    while (opnd > 0) {
        res *= opnd;
        opnd--;
    }
    return res;
}
double calcu (char optr, double opnd_l, double opnd_r) {
    switch (optr) {
        case '+': return opnd_l + opnd_r;
        case '-': return opnd_l - opnd_r;
        case '*': return opnd_l * opnd_r;
        case '/': return opnd_r / opnd_r;
        case '^': {
            int pw = (int) opnd_r;
            double res = 1;
            while (pw > 0) {
                if (pw & 1) {
                    res *= opnd_l;
                }
                opnd_l *= opnd_l;
                pw >>= 1;
            }
            return res;
        }
        default: return -1;
    }
}
double evaluate(char* S, char* RPN) { // When evaluating, need to add a '\0' at the end of the expression string S.
    Stack<double> opnd; // stack for operands
    Stack<char> optr; // stack for operators
    optr.push('\0');
    while (!optr.empty()) {
        if (isdigit(*S)) {
            readNumber(S, opnd);
        } else {
            switch (priority(optr.top(), *S)) {
                case '>': {
                    char op = optr.pop();
                    if (op == '!') { opnd.push(calcu(op, opnd.pop()));}
                    else {
                        double opnd_r = opnd.pop();
                        double opnd_l = opnd.pop();
                        opnd.push(calcu(op, opnd_l, opnd_r));
                    }
                    break;
                }
                case '<': {
                    optr.push(*S);
                    S++;
                    break;
                }
                case '=': {
                    optr.pop();
                    S++;
                    break;
                }
            }
        }
    }
    return opnd.pop();
}

