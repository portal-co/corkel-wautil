#ifndef RB_WASM_SUPPORT_ASYNCIFY_H
#define RB_WASM_SUPPORT_ASYNCIFY_H

__attribute__((import_module("asyncify"), import_name("start_unwind"))) void
_asyncify_start_unwind(void *buf);
static inline void asyncify_start_unwind(void *buf) {
  extern void *rb_asyncify_unwind_buf;
  rb_asyncify_unwind_buf = (buf);
  asyncify_start_unwind((buf));
}
__attribute__((import_module("asyncify"), import_name("stop_unwind"))) void
_asyncify_stop_unwind(void);
static inline void asyncify_stop_unwind(void) {
  extern void *rb_asyncify_unwind_buf;
  rb_asyncify_unwind_buf = (void*)0;
  asyncify_stop_unwind();
}
__attribute__((import_module("asyncify"), import_name("start_rewind"))) void
asyncify_start_rewind(void *buf);
__attribute__((import_module("asyncify"), import_name("stop_rewind"))) void
asyncify_stop_rewind(void);

#endif