#include "rpn.h"
#include "assert.h"

RPN::RPN():_postfix(){}

RPN::RPN(Queue<Token*> a){}

void RPN::set_input(Queue<Token*> a){
    _postfix = a;
}

vectorlong RPN::operator()(){
    Stack<Token*> stack;
    Queue<Token*> tempPostfix(_postfix);

    Token* tokenIt;

    // Integer* first;
    // Integer* second;

    // Operator* queueOper;

    // Function* queueFunc;
    TokenStr* first;
    TokenStr* second;

    Relational* queueRel;
    Logical* queueLog;


    // while(tempPostfix.begin() != tempPostfix.end()){
    //     tokenIt = tempPostfix.pop();
        
    //     switch(tokenIt->type()){
    //         case STRING: stack.push(tokenIt);
    //                       break;
    //         case RELATIONAL:
    //             //cout << "Hello\n"; 
    //             queueRel = static_cast<Relational*>(tokenIt);
    //             first = static_cast<TokenStr*>(stack.pop());
    //             second = static_cast<TokenStr*>(stack.pop());
                
    //             double firstValue = first -> getVal();

    //             switch(queueFunc -> getTrigType()){
    //                 case SIN: stack.push(new Integer(sin(firstValue)));
    //                             break;
    //                 case COS: stack.push(new Integer(cos(firstValue)));
    //                             break;
    //                 case TAN: stack.push(new Integer(tan(firstValue)));
    //                             break;
    //                 case ASIN: stack.push(new Integer(asin(firstValue)));
    //                             break;
    //                 case ACOS: stack.push(new Integer(acos(firstValue)));
    //                             break;
    //                 case ATAN: stack.push(new Integer(atan(firstValue)));
    //                             break;
    //                 default: //cout << "YOU SUCK\n";
    //                         assert(false);
    //             }
    //             break;
    //         case OPERATION:
    //             queueOper = static_cast<Operator*> (tokenIt);
    //             stack.push(queueOper -> eval(stack.pop(), stack.pop()));
    //             break;
            
    //         default: //cout << "YOU SUCK ALOT\n";
    //                 assert(false);

    //     }
    // }

    // first = static_cast<Integer*>(stack.pop());
    // return first -> getVal();
    return {(long)10, 20};
}

void eval(){

}