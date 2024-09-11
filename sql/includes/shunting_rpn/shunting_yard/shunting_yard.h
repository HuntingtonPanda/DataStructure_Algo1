#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H
#include <iostream>
#include <iomanip>
#include "assert.h"

#include "../node/node.h"
#include "../linked_list_functions/linked_list_functions.h"
#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"

#include "../new_token/token.h"
#include "../new_token/new_token.h"
#include "../new_token/leftparen.h"
#include "../new_token/rightparen.h"

using namespace std;


class ShuntingYard{
    public:
        ShuntingYard();
        
        ShuntingYard(Queue<Token*> preFix);

        void infix(Queue<Token*> preFix);

        Queue<Token*> postfix();

        Queue<Token*> postfix(Queue<Token*> preFix);

        void print();

    private:
        Queue<Token*> _infix;
        Queue<Token*> _postfix;
};
    
    

#endif