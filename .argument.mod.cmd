savedcmd_argument.mod := printf '%s\n'   argument.o | awk '!x[$$0]++ { print("./"$$0) }' > argument.mod
