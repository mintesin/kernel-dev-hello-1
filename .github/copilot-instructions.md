# Copilot Workspace Instructions

## Purpose
This repo hosts Linux kernel module examples for OS and systems programming practice. These instructions help Copilot Chat reason about build/test flow and common kernel module patterns.

## Project overview
- Kernel modules: `hello-3`, `argument`, `procfs1`, `chardev`.
- Additional module pair in `Module_Spanning/`.
- Primary learning focus: module lifecycle, procfs / char device, user-space data transfer, kernel logging.

## Build/test commands
- `make` (compile against `/lib/modules/$(uname -r)/build`)
- `make clean`
- `sudo insmod <module>.ko`
- `sudo rmmod <module>`
- `dmesg | tail`

## Code conventions
- Use `module_init` / `module_exit` and proper cleanup.
- Logging via `printk` / `pr_info` and check error paths.
- Prefer `copy_to_user` / `copy_from_user` safety checks.
- Keep kernel-space and user-space APIs separate.

## Key files
- `Makefile`
- `hello-3.c`, `argument.c`, `procfs1.c`, `chardev.c`
- `Module_Spanning/` group for multi-module interactions

## Common examiner tasks for AI
- Fix syntax/compile errors in kernel-style C.
- Convert `procfs` code to current kernel `proc_ops` API.
- Hardening around user-copy functions and `GFP` context.
- Add module metadata (`MODULE_LICENSE`, `MODULE_AUTHOR`, etc.).

## Pitfalls
- Invalid use of `struct procfs_name` (should use `struct proc_dir_entry`).
- Wrong callback names for `proc_ops` (`.proc_read` vs `.read`).
- Direct user-space pointer dereference instead of `copy_to_user`/`copy_from_user`.
- Running on host kernel can crash; test in VM.

## Future improvements
- Add `AGENTS.md` for scoped agent instructions (`/procfs/**`, `/Module_Spanning/**`).
- Add `README.md` usage examples with `insmod`/`rmmod`/`dmesg` and expected output.
