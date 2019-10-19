#include <pf.h>
#include <stdio.h>
#include "map.h"

pf_size judge(pf_data u, pf_node location, pf_node goal) {
    (void) u;
    // u: pf_create(From here, ?)
    // determine if you have reached your goal
    return location == goal;
}

pf_size heuristic(pf_data u, pf_node location, pf_node goal) {
    (void) u;
    (void) goal;
    (void) location;
    // goal: pf_invoke(?, ?, ?, From here, ?)
    // cost from current location to goal
    return 1;
}

pf_size successors(pf_data u, pf_node location, pf_successor* successors) {
    (void) u;
    // len(successors): pf_create(?, From here)
    struct node* loc = location;
    for (pf_size i = 0; i < loc->neighbour_num; ++ i) {
        successors[i].node = loc->neighbours[i].node;
        successors[i].cost = loc->neighbours[i].cost;
    }
    // number of successor
    return loc->neighbour_num;
}

int main() {
    #define INDEX(NODE) ((#NODE)[0] - 'A')
    #define ADDRESS_OF_NODE(NODE) &map[INDEX(NODE)]
    #define MAKE_NEIGHBOUR(COST, NODE) create_cost(COST, ADDRESS_OF_NODE(NODE))

/**************
 *   Game Map
 *  ___A__(B)__
 * |     \ |   |
 * E___D___C   |
 * |   |   | \ |
 * ___(F)__G___H
 * cost(__) 10, cost(|) 10, cost(\) 12
 */

    struct node map[] = {
        create_node('A', 3,
            MAKE_NEIGHBOUR(10, B),
            MAKE_NEIGHBOUR(20, E),
            MAKE_NEIGHBOUR(12, C)),
        create_node('B', 3,
            MAKE_NEIGHBOUR(10, A),
            MAKE_NEIGHBOUR(10, C),
            MAKE_NEIGHBOUR(30, H)),
        create_node('C', 5,
            MAKE_NEIGHBOUR(12, A),
            MAKE_NEIGHBOUR(10, B),
            MAKE_NEIGHBOUR(10, D),
            MAKE_NEIGHBOUR(10, G),
            MAKE_NEIGHBOUR(12, H)),
        create_node('D', 3,
            MAKE_NEIGHBOUR(10, C),
            MAKE_NEIGHBOUR(10, E),
            MAKE_NEIGHBOUR(10, F)),
        create_node('E', 3,
            MAKE_NEIGHBOUR(20, A),
            MAKE_NEIGHBOUR(10, D),
            MAKE_NEIGHBOUR(20, F)),
        create_node('F', 3,
            MAKE_NEIGHBOUR(20, E),
            MAKE_NEIGHBOUR(10, D),
            MAKE_NEIGHBOUR(10, G)),
        create_node('G', 3,
            MAKE_NEIGHBOUR(10, C),
            MAKE_NEIGHBOUR(10, F),
            MAKE_NEIGHBOUR(10, H)),
        create_node('H', 3,
            MAKE_NEIGHBOUR(30, B),
            MAKE_NEIGHBOUR(12, C),
            MAKE_NEIGHBOUR(10, G)),
    };

    pf_callback callback;
    callback.c3.fn_successors = successors;
    callback.c3.fn_heuristic = heuristic;
    callback.c3.fn_judge = judge;

    pf_handle handle = pf_create(NULL, MAX_NEIGHBOUR_NUM);
    pf_size len = pf_invoke(handle, PF_A_STAR, ADDRESS_OF_NODE(B), ADDRESS_OF_NODE(F), &callback);

    // [B] -> [C] -> [G] -> [F]
    for (pf_size i = 0; i < len; ++ i) {
        struct node* p = pf_inspector(handle, i);
        printf("[%c] %s", p->name, i+1 == len ? "\n":"-> ");
    }
    pf_destroy(handle);
    return 0;
}