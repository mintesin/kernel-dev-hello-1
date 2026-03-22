savedcmd_hello_procs.mod := printf '%s\n'   hello_procs.o | awk '!x[$$0]++ { print("./"$$0) }' > hello_procs.mod
