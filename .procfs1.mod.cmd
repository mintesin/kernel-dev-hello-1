savedcmd_procfs1.mod := printf '%s\n'   procfs1.o | awk '!x[$$0]++ { print("./"$$0) }' > procfs1.mod
