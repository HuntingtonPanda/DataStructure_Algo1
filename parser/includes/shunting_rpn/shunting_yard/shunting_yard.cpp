#include "shunting_yard.h"
#include "assert.h"

ShuntingYard::ShuntingYard(): _infix(), _postfix(){}

ShuntingYard::ShuntingYard(Queue<Token*> preFix): _infix(preFix), _postfix(){
    infix(_infix);
}
    
void ShuntingYard::infix(Queue<Token*> preFix){   
    while(!(_postfix.empty())){
        _postfix.pop();
    }
    _infix = preFix;

    Stack<Token*> stack;
    typename Stack<Token*>:: Iterator stackIt;

    Token* tokenIt;

    Relational* queueRelational;
    Relational* stackRelational;

    Logical* queueLogic;
    Logical* stackLogic;

    int currentPrec = 0;

    done:while(preFix.begin() != preFix.end()){
        tokenIt = preFix.pop();
        switch(tokenIt->type()){
            case STRING: _postfix.push(tokenIt); //tokenIt is a pointer but push wants a item
                          break;
            
            case LOGICAL:
                 currentPrec = 0;
                 queueLogic = static_cast<Logical*> (tokenIt);

                 while(!stack.empty() && stack.top()->type() != LEFTPARENTH){
                    stackLogic = static_cast<Logical*> (stack.top());
                    currentPrec = stackLogic -> get_prec();
                    if(queueLogic -> get_prec() <= currentPrec){
                        _postfix.push(stack.pop());
                    }else{
                        stack.push(queueLogic);
                        goto done;
                    }
                 }
                 
                 stack.push(queueLogic);
                 break;
            
            case RELATIONAL:
                 currentPrec = 0;
                 queueRelational = static_cast<Relational*> (tokenIt);

                 while(!stack.empty() && stack.top()->type() != LEFTPARENTH){
                    stackRelational = static_cast<Relational*> (stack.top());
                    currentPrec = stackRelational -> get_prec();
                    if(queueRelational -> get_prec() <= currentPrec){
                        _postfix.push(stack.pop());
                    }else{
                        stack.push(queueRelational);
                        goto done;
                    }
                 }
                 
                 stack.push(queueRelational);
                 break;
            
            case LEFTPARENTH:
                stack.push(tokenIt);
                currentPrec = 0;
                break;

            case RIGHTPARENTH: 
                while((stack.top())->type() != LEFTPARENTH){
                    _postfix.push(stack.pop());
                }
                stack.pop();
                break;

            default:
                assert(false);
        }

    }

    while(!stack.empty()){
        tokenIt = static_cast<Token*> (stack.pop());
        switch(tokenIt->type()){
            case LOGICAL:
                        _postfix.push(static_cast<Logical*>(tokenIt));
                        break;
            case RELATIONAL:
                        _postfix.push(static_cast<Relational*>(tokenIt));
                        break;
        }
    }   
}


Queue<Token*> ShuntingYard::postfix(){
    return _postfix;
}


Queue<Token*> ShuntingYard::postfix(Queue<Token*> preFix){
    //infix(preFix);
    return _postfix;
}

void ShuntingYard::print(){
    for (Queue<Token *>::Iterator it = _postfix.begin(); it != _postfix.end(); it++){
        cout <<setw(3)<< *it;
    } 
    cout << "\n\n";
}