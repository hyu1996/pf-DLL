//
// Created by hyu on 2019/10/19.
//

#ifndef PF_H
#define PF_H

#ifdef __cplusplus
#define PF_API extern "C"
#else
#define PF_API
#endif

typedef void* pf_node;
typedef void* pf_data;
typedef unsigned int pf_size;
typedef struct pf_handle* pf_handle;

typedef struct {
    pf_node node;
    pf_size cost;
} pf_successor;

typedef pf_size (*pf_judge)(pf_data u, pf_node location, pf_node goal);
typedef pf_size (*pf_heuristic)(pf_data u, pf_node location, pf_node goal);
typedef pf_size (*pf_successors)(pf_data u, pf_node location, pf_successor* successors);

typedef union {
    struct { // only for PF_DIJKSTRA
        pf_judge fn_judge;
        pf_successors fn_successors;
    } c2;
    struct { // for PF_A_STAR, PF_FRINGE, PF_ID_A_STAR
        pf_judge fn_judge;
        pf_successors fn_successors;
        pf_heuristic fn_heuristic;
    } c3;
} pf_callback;

typedef enum {
    PF_A_STAR,
    PF_FRINGE,
    PF_DIJKSTRA,
    PF_ID_A_STAR,
} pf_algorithm;

PF_API pf_handle pf_create(pf_data u, pf_size num);
PF_API pf_size pf_invoke(pf_handle handle, pf_algorithm algorithm, pf_node start, pf_node goal, const pf_callback* callback);
PF_API pf_node pf_inspector(pf_handle handle, pf_size index);
PF_API void pf_destroy(pf_handle handle);

#endif //PF_H
