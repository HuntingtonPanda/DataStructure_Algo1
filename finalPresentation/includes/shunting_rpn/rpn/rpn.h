#ifndef RPN_H
#define RPN_H
#include <iostream>
#include <iomanip>
#include <cmath>
#include "assert.h"

#include "../node/node.h"
#include "../linked_list_functions/linked_list_functions.h"
#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"


#include "../new_token/new_token.h"
#include "../new_token/leftparen.h"
#include "../new_token/rightparen.h"
#include "../new_token/token.h"

#include "../../table/typedefs.h"

using namespace std;

class RPN{
    public:
    RPN();
    RPN(Queue<Token*> a);
    void set_input(Queue<Token*> a);

    vectorlong operator()();

    //double rpn(int varValue);


    private:
    void eval();

    Queue<Token *> _postfix;
    vectorlong answer;
};

#endif