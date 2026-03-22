savedcmd_assignment_one.mod := printf '%s\n'   assignment_one.o | awk '!x[$$0]++ { print("./"$$0) }' > assignment_one.mod
