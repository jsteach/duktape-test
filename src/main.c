#define NOB_STRIP_PREFIX
#define NOB_IMPLEMENTATION
#include "nob.h"
#include <stdio.h>
#include "duktape.h"
#include "duk_module_duktape.h"


static duk_ret_t native_print(duk_context *ctx) {
    const char* str = duk_to_string(ctx, 0);
    printf("%s\n", str);
    return 0;  /* no return value (= undefined) */
}

//We need to add modSearch for real: https://stackoverflow.com/a/57116140

#define FILE_TO_RUN "assets/dtsc.js"
extern duk_ret_t duk__require(duk_context *ctx);
int main(int argc, char *argv[]) {
    (void)argc;(void)argv;
    duk_context *ctx = duk_create_heap_default();
    // duk__require(ctx);
    duk_push_c_function(ctx, native_print, 1 /*nargs*/);
    duk_put_global_string(ctx, "print");
    duk_module_duktape_init(ctx);
    printf("top after init: %ld\n", (long) duk_get_top(ctx));

    String_Builder sb = {0};
    if(!read_entire_file(FILE_TO_RUN,&sb)){
        nob_log(NOB_ERROR,"Couldn't load file: %s",FILE_TO_RUN);
        return 1;
    }
    sb_append_null(&sb);
    duk_eval_string(ctx, "var exports = {}");
    duk_eval_string(ctx, "Duktape.modSearch = function(id) {return readFileAsString(id);}");
    duk_eval_string(ctx, sb.items);
    /* Dump the bytecode
    duk_eval_string(ctx, "(function myfunc() { print('hello world'); })");
    duk_dump_function(ctx);
    void* bc_ptr = NULL;
    duk_size_t bc_len;
    unsigned char *p;
	duk_size_t i, sz;
    p = (unsigned char *) duk_get_buffer(ctx, -1, &sz);
	for (i = 0; i < sz; i++) {
		printf("%02x", (int) p[i]);
	}
	printf("\n");
    */
    // bc_ptr = duk_require_buffer_data(ctx, -1, &bc_len);
    // nob_write_entire_file("./test.bc",bc_ptr,(size_t)bc_len);
    duk_destroy_heap(ctx);
    return 0;
}