#!/bin/sh
cat <<EOD
# ===
# Cheat sheet
# (lldb) breakpoint set --file foo.c --line 12
# (lldb) breakpoint set --name foo
# (lldb) watch set var global
# (lldb) watch modify -c '(grobal==5)'
# (lldb) process launch // run
# (lldb) thread continue
# (lldb) thread step-in  // step or s
# (lldb) thread step-over // next or n
# (lldb) thread step-out // finish or f
# (lldb) frame variable
# (lldb) expr *(char (*)[16][3]) A
# ===
EOD
lldb $1
