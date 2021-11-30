#include "py/runtime.h"
#include "ffi.h"

typedef union {
  ffi_sarg sint;
  ffi_arg  uint;
  float    flt;
  double   dbl;
  void*    ptr;
} ffi_value;

STATIC mp_obj_t example_printf(size_t n_args, const mp_obj_t *args) {
	ffi_cif cif;
	ffi_type **types = alloca(n_args * sizeof(ffi_type *));
	ffi_value *values = alloca(n_args * sizeof(ffi_value));
	void **arg_values = alloca(n_args * sizeof(void *));

	ffi_arg result;

	size_t i;
	for (i = 0; i < n_args; i++) {
		if (mp_obj_get_int_maybe(args[i], (mp_int_t *)&values[i].sint)) {
			types[i] = &ffi_type_sint;
		} else if (mp_obj_is_float(args[i])) {
			types[i] = &ffi_type_double;
			values[i].dbl = mp_obj_get_float_to_d(args[i]);
		} else if (mp_obj_is_str(args[i])) {
			types[i] = &ffi_type_pointer;
			values[i].ptr = (void *)mp_obj_str_get_str(args[i]);
		} else {
			// ERROR
			mp_raise_TypeError(MP_ERROR_TEXT("not supported type is specified"));
		}
		arg_values[i] = &values[i];
	}

	ffi_prep_cif_var(&cif, FFI_DEFAULT_ABI, 1, n_args, &ffi_type_sint, types);
	ffi_call(&cif, FFI_FN(printf), &result, arg_values);

	return mp_obj_new_int(result);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR(example_printf_obj, 1, example_printf);

STATIC const mp_rom_map_elem_t example_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_cexample) },
    { MP_ROM_QSTR(MP_QSTR_printf)  , MP_ROM_PTR(&example_printf_obj) },
};
STATIC MP_DEFINE_CONST_DICT(example_module_globals, example_module_globals_table);

const mp_obj_module_t example_user_cmodule = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&example_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_cexample, example_user_cmodule, 1);
