//
// Created by hyu on 2019/10/19.
//

#include "map.h"

struct node create_node(char name, pf_size num, ...) {
    struct node r;
    r.name = name;
    r.neighbour_num = num;
    va_list neighbours;
    va_start (neighbours, num);
    while (num -- > 0) {
        r.neighbours[num] = va_arg(neighbours, struct cost);
    }
    va_end(neighbours);
    return r;
}

struct cost create_cost(pf_size cost, struct node* node) {
    struct cost r;
    r.cost = cost;
    r.node = node;
    return r;
}