#!/bin/sh
cat <<EOD
# ===
# Cheat sheet
# (lldb) breakpoint set --file foo.c --line 12
# (lldb) watch set var global
# (lldb) watch modify -c '(grobal==5)'
# (lldb) process launch
# (lldb) thread continue
# (lldb) thread step-in
# (lldb) thread step-over
# (lldb) thread step-out
# (lldb) frame variable
# ===
EOD
lldb $1
