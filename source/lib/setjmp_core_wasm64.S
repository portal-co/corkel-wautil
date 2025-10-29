
	# extern int _rb_wasm_setjmp_internal(rb_wasm_jmp_buf *env);
	.functype	_rb_wasm_setjmp_internal (i64) -> (i64)
	# extern int __stack_pointer;
	.globaltype 	__stack_pointer, i64

	# A wrapper of _rb_wasm_setjmp_internal to save and restore stack pointer
	# This cannot be implemented in C because there is no way to manipulate stack pointer
	# without C-epilogue.

	# extern int _rb_wasm_setjmp(rb_wasm_jmp_buf *env);
	.section	.text._rb_wasm_setjmp,"",@
	.globl		_rb_wasm_setjmp
	.type		_rb_wasm_setjmp,@function
_rb_wasm_setjmp:
	.functype	_rb_wasm_setjmp (i64) -> (i64)
	.local		i64, i64
	# save sp (this local is stored in asyncify stack and restored when rewinding)
	global.get	__stack_pointer
	local.set	1

	local.get	0
	call		_rb_wasm_setjmp_internal

	# restore sp
	local.get	1
	global.set	__stack_pointer
	end_function
