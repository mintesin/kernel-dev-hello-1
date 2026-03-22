savedcmd_info_timer.mod := printf '%s\n'   info_timer.o | awk '!x[$$0]++ { print("./"$$0) }' > info_timer.mod
