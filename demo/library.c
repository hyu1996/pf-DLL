//
// Created by hyu on 2019/10/19.
//

#include <pf.h>
#include <stdio.h>
#include <windows.h>

typedef pf_handle (*pf_create_t)(pf_data, pf_size);
typedef pf_size (*pf_invoke_t)(pf_handle, pf_algorithm, pf_node, pf_node, const pf_callback*);
typedef pf_node (*pf_inspector_t)(pf_handle, pf_size);
typedef void (*pf_destroy_t)(pf_handle);

static HMODULE DLL = NULL;
static pf_create_t pf_create_impl = NULL;
static pf_invoke_t pf_invoke_impl = NULL;
static pf_inspector_t pf_inspector_impl = NULL;
static pf_destroy_t pf_destroy_impl = NULL;

static void pf_close(void) {
    if (DLL) {
        FreeModule(DLL);
        DLL = NULL;
    }
}

PF_API pf_handle pf_create(pf_data u, pf_size num) {
    if (!DLL) {
        pf_size b32 = sizeof(int*) == sizeof(int);
        DLL = LoadLibrary(b32 ? "pf32.DLL" : "pf64.DLL");
        if (DLL) {
            pf_create_impl = (pf_create_t) GetProcAddress(DLL, "pf_create");
            pf_invoke_impl = (pf_invoke_t) GetProcAddress(DLL, "pf_invoke");
            pf_inspector_impl = (pf_inspector_t) GetProcAddress(DLL, "pf_inspector");
            pf_destroy_impl = (pf_destroy_t) GetProcAddress(DLL, "pf_destroy");
            atexit(pf_close);
        } else {
            return NULL;
        }
    }
    return pf_create_impl(u, num);
}

PF_API pf_size pf_invoke(pf_handle handle, pf_algorithm algorithm, pf_node start, pf_node goal, const pf_callback* callback) {
    return pf_invoke_impl(handle, algorithm, start, goal, callback);
}

PF_API pf_node pf_inspector(pf_handle handle, pf_size index) {
    return pf_inspector_impl(handle, index);
}

PF_API void pf_destroy(pf_handle handle) {
    pf_destroy_impl(handle);
}