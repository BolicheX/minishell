#!/usr/bin/env bash

MINISHELL=./minishell

tests=(
# ---- Comandos simples ----
"echo hola"
"echo -n hola"
"echo -nnnnnn hola"
"ls nofile"
"pwd"
"env"

# ---- Pipes ----
"echo hola | cat"
"echo hola | grep h"
"ls | wc -l"
"cat noexiste | wc -l"
"echo hola | cat | wc -c"
"ls | grep minishell | cat -e"
"echo hola | tr a-z A-Z | tr A-Z a-z | wc -c"
"echo | echo | echo"
"echo hola |"

# ---- Redirecciones salida ----
"echo hola > out.txt"
"echo hola >> out.txt"
"ls > out.txt"
"ls nofile > out.txt"
"echo hola > out1.txt > out2.txt"
"echo hola > /dev/null"
"echo hola > /"

# ---- Redirecciones entrada ----
"cat < out.txt"
"wc -l < out.txt"
"< out.txt cat"
"< noexiste.txt cat"
"cat < /dev/null"
"cat < out.txt | wc -c"

# ---- Heredoc ----
"cat << EOF
hola
mundo
EOF"
"cat << FIN | wc -l
uno
dos
FIN"
"cat << A << pues B
linea1
A
linea2
B"
"cat << EOF | grep hola
hola
EOF"
"cat <<''EOF
no expand \$HOME
EOF"
"cat <<\"EOF\"
literal \$PATH
EOF"
"cat <<EOF
expand \$PATH
EOF"

# ---- Comillas ----
"echo 'hola mundo'"
"echo \"hola mundo\""
"echo \"hola   mundo\""
"echo 'hola   mundo'"
"echo hola\"mundo\""
"echo 'hola'\"mundo\""
"echo ''"
"echo \"\""
"echo '   '"
"echo \"\$PATH\""
"echo '\$PATH'"

# ---- Variables ----
"echo \$PATH"
"echo \$HOME"
"echo \$USER"
"echo \$NOEXISTE"
"echo \$?"
"echo text\$VARend"

# ---- Combinaciones ----
"ls | grep minishell | wc -l"
"echo hola > out.txt | cat < out.txt"
"echo hola | cat > out.txt | wc -c"
"cat <<EOF | grep hola | wc -l
hola
EOF"
"echo 'unquoted > redir' > out.txt"
"echo \"a | b | c\""
"echo hola | > out.txt cat"
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