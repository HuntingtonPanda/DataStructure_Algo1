#ifndef Co_TYPEDEFS_H
#define Co_TYPEDEFS_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <queue>

#include "../shunting_rpn/queue/MyQueue.h"
#include "../bplustree/map.h"
#include "../bplustree/multimap.h"
#include "assert.h"

using namespace std;

typedef Map<string, string> map_ss;
typedef MMap<string, string> mmap_ss;

typedef Map<string, long> map_sl;
typedef MMap<string, long> mmap_sl;

typedef vector<string> vectorstr;
typedef vector<long> vectorlong;

typedef vector<mmap_sl> vectorMMap;

typedef Queue<string> queuestr;
#endif