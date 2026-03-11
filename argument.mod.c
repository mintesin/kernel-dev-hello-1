#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0x90a48d82, "__ubsan_handle_out_of_bounds" },
	{ 0x0040afbe, "param_array_ops" },
	{ 0x0040afbe, "param_ops_int" },
	{ 0x0040afbe, "param_ops_charp" },
	{ 0x0040afbe, "param_ops_long" },
	{ 0x0040afbe, "param_ops_short" },
	{ 0xd272d446, "__fentry__" },
	{ 0xe8213e80, "_printk" },
	{ 0xbebe66ff, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0xd272d446,
	0x90a48d82,
	0x0040afbe,
	0x0040afbe,
	0x0040afbe,
	0x0040afbe,
	0x0040afbe,
	0xd272d446,
	0xe8213e80,
	0xbebe66ff,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"__x86_return_thunk\0"
	"__ubsan_handle_out_of_bounds\0"
	"param_array_ops\0"
	"param_ops_int\0"
	"param_ops_charp\0"
	"param_ops_long\0"
	"param_ops_short\0"
	"__fentry__\0"
	"_printk\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "FCBFE9917E11D801A31C5EF");
