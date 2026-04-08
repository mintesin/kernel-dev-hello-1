# TODO: Fix try.c compilation warning

- [x] Step 1: Add #include <sys/wait.h> for wait()
- [x] Step 2: Replace sprintf(stderr, ...) with char buffer + sprintf + fprintf(stderr)
- [x] Step 3: Verify compilation with gcc try.c -o try
- [x] Step 4: Test ./try
