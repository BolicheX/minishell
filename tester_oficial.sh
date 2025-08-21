#!/usr/bin/env bash

MINISHELL=./minishell

tests=(
"/bin/ls"
" "
"   "
"/bin/ls hola adios"
"echo hola adios"
"pwd hola adios"
"cat hola adios"
"ls hola adios"
"exit"
"exit 42"
"exit 42 37"
"/bin/ls filethatdoesntexist"
'expr $? + $?'
'$? + $?'
'echo "cat lol.c | cat > lol.c"'
"echo 'hola'"
"echo ''"
"echo ' '"
"echo ' '"
'echo '\''$USER'\'''
"echo '|'"
"echo '<'"
"echo '>'"

)

RED="\\033[31m"
GREEN="\\033[32m"
YELLOW="\\033[33m"
NC="\\033[0m"

run_test() {
    local cmd="$1"
    echo "===> Test: $cmd"

    # Ejecutar en bash
    bash_stdout=$(mktemp)
    bash_stderr=$(mktemp)
    echo "$cmd" | bash > $bash_stdout 2> $bash_stderr
    bash_exit=$?

    # Ejecutar en minishell
    mini_stdout=$(mktemp)
    mini_stderr=$(mktemp)
    echo "$cmd" | $MINISHELL > $mini_stdout 2> $mini_stderr
    mini_exit=$?

    # Normalizar errores: sustituir prefix de bash por minishell
    bash_stderr_normalized=$(mktemp)
    cp "$bash_stderr" "$bash_stderr_normalized"
    sed -i 's|^bash:|minishell:|' "$bash_stderr_normalized"

    # Comparar
    if cmp -s "$bash_stdout" "$mini_stdout" && cmp -s "$bash_stderr_normalized" "$mini_stderr" && [ $bash_exit -eq $mini_exit ]; then
        echo -e "${GREEN}OK${NC}"
    else
        echo -e "${RED}FAIL${NC}"
        echo "--- bash stdout ---"
        cat "$bash_stdout"
        echo "--- minishell stdout ---"
        cat "$mini_stdout"
        echo "--- bash stderr ---"
        cat "$bash_stderr"
        echo "--- minishell stderr ---"
        cat "$mini_stderr"
        echo "--- bash exit: $bash_exit, minishell exit: $mini_exit ---"
    fi

    rm -f "$bash_stdout" "$bash_stderr" "$mini_stdout" "$mini_stderr"
    echo
}

for t in "${tests[@]}"; do
    run_test "$t"
done