#!/usr/bin/env bash

MINISHELL=./minishell

tests=(
"noexiste"
"/root/prohibido"
"./"
"echo hola > out.txt"
"cat out.txt"
"echo hola >> out.txt"
"cat out.txt"
"cat < out.txt"
"cat out.txt"
"cat < noexiste.txt"
"cat < noexiste.txt | ls"
"pwd < noexiste.txt"
"pwd < noexiste.txt | ls"
"noexiste < noexiste.txt"
"noexiste < noexiste.txt | ls"
"cat < /root/prohibido.txt"
"cat < /root/prohibido.txt | ls"
"pwd < /root/prohibido.txt"
"pwd < /root/prohibido.txt | ls"
"noexiste < /root/prohibido.txt"
"noexiste < /root/prohibido.txt | ls"
"ls > /root/prohibido.txt"
"ls | cat > /root/prohibido.txt"
"echo hola > /root/prohibido.txt"
"ls | echo hola > /root/prohibido.txt"
"echo hola | cat > /root/prohibido.txt"
"noexiste > /root/prohibido.txt"
"noexiste | cat > /root/prohibido.txt"
"cat | noexiste > /root/prohibido.txt"
"<< EOF"
"cd noexiste"
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
    sed -i 's|^/bin/bash:|minishell:|' "$bash_stderr"
    sed -i 's|^bash:|minishell:|' "$bash_stderr"

    # Comparar
    if cmp -s "$bash_stdout" "$mini_stdout" && cmp -s "$bash_stderr" "$mini_stderr" && [ $bash_exit -eq $mini_exit ]; then
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

rm out.txt
