//
// Created by hyu on 2019/10/19.
//

#ifndef MAP_H
#define MAP_H

#include <stdarg.h>
#include "../include/pf.h"

struct node;

#define MAX_NEIGHBOUR_NUM 5

struct cost {
    pf_size cost;
    struct node* node;
};

struct node {
    char name;
    pf_size neighbour_num;
    struct cost neighbours[MAX_NEIGHBOUR_NUM];
};

struct node create_node(char name, pf_size num, ...);
struct cost create_cost(pf_size cost, struct node* node);

#endif //MAP_H
