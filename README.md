# minishell
Tan bonito como shell

# Nombre del Programa: minishell

## Funciones autorizadas

- [readline](https://tiswww.case.edu/php/chet/readline/readline.html)
- [rl_clear_history](https://tiswww.case.edu/php/chet/readline/readline.html#IDX179)
- [rl_on_new_line](https://tiswww.case.edu/php/chet/readline/readline.html#IDX193)
- [rl_replace_line](https://tiswww.case.edu/php/chet/readline/readline.html#IDX194)
- [rl_redisplay](https://tiswww.case.edu/php/chet/readline/readline.html#IDX196)
- [add_history](https://tiswww.case.edu/php/chet/readline/readline.html#IDX175)
- [printf](https://man7.org/linux/man-pages/man3/printf.3.html)
- [malloc](https://man7.org/linux/man-pages/man3/malloc.3.html)
- [free](https://man7.org/linux/man-pages/man3/free.3.html)
- [write](https://man7.org/linux/man-pages/man2/write.2.html)
- [access](https://man7.org/linux/man-pages/man2/access.2.html)
- [open](https://man7.org/linux/man-pages/man2/open.2.html)
- [read](https://man7.org/linux/man-pages/man2/read.2.html)
- [close](https://man7.org/linux/man-pages/man2/close.2.html)
- [fork](https://man7.org/linux/man-pages/man2/fork.2.html)
- [wait](https://man7.org/linux/man-pages/man2/wait.2.html)
- [waitpid](https://man7.org/linux/man-pages/man2/waitpid.2.html)
- [wait3](https://man7.org/linux/man-pages/man2/wait3.2.html)
- [wait4](https://man7.org/linux/man-pages/man2/wait4.2.html)
- [signal](https://man7.org/linux/man-pages/man2/signal.2.html)
- [sigaction](https://man7.org/linux/man-pages/man2/sigaction.2.html)
- [kill](https://man7.org/linux/man-pages/man2/kill.2.html)
- [exit](https://man7.org/linux/man-pages/man3/exit.3.html)
- [getcwd](https://man7.org/linux/man-pages/man3/getcwd.3.html)
- [chdir](https://man7.org/linux/man-pages/man2/chdir.2.html)
- [stat](https://man7.org/linux/man-pages/man2/stat.2.html)
- [lstat](https://man7.org/linux/man-pages/man2/lstat.2.html)
- [fstat](https://man7.org/linux/man-pages/man2/fstat.2.html)
- [unlink](https://man7.org/linux/man-pages/man2/unlink.2.html)
- [execve](https://man7.org/linux/man-pages/man2/execve.2.html)
- [dup](https://man7.org/linux/man-pages/man2/dup.2.html)
- [dup2](https://man7.org/linux/man-pages/man2/dup2.2.html)
- [pipe](https://man7.org/linux/man-pages/man2/pipe.2.html)
- [opendir](https://man7.org/linux/man-pages/man3/opendir.3.html)
- [readdir](https://man7.org/linux/man-pages/man3/readdir.3.html)
- [closedir](https://man7.org/linux/man-pages/man3/closedir.3.html)
- [strerror](https://man7.org/linux/man-pages/man3/strerror.3.html)
- [perror](https://man7.org/linux/man-pages/man3/perror.3.html)
- [isatty](https://man7.org/linux/man-pages/man3/isatty.3.html)
- [ttyname](https://man7.org/linux/man-pages/man3/ttyname.3.html)
- [ttyslot](https://man7.org/linux/man-pages/man3/ttyslot.3.html)
- [ioctl](https://man7.org/linux/man-pages/man2/ioctl.2.html)
- [getenv](https://man7.org/linux/man-pages/man3/getenv.3.html)
- [tcsetattr](https://man7.org/linux/man-pages/man3/tcsetattr.3.html)
- [tcgetattr](https://man7.org/linux/man-pages/man3/tcgetattr.3.html)
- [tgetent](https://linux.die.net/man/3/tgetent)
- [tgetflag](https://linux.die.net/man/3/tgetent)
- [tgetnum](https://linux.die.net/man/3/tgetent)
- [tgetstr](https://linux.die.net/man/3/tgetent)
- [tgoto](https://linux.die.net/man/3/tgetent)
- [tputs](https://linux.die.net/man/3/tgetent)

## Descripción del proyecto

### Entrada y ejecución

- Mostrar una entrada mientras espera un comando nuevo.
- Tener un historial funcional.
- Buscar y ejecutar el ejecutable correcto (basado en la variable PATH o mediante rutas relativas o absolutas).

### Manejo de señales

- Evita utilizar más de una variable global para indicar la recepción de una señal.

⚠️ Esta variable no puede proporcionar ninguna otra información que el número de la señal recibida.  
Está prohibido usar estructuras globales de tipo “norm”.

### Reglas de sintaxis

- No interpretar comillas sin cerrar.
- No interpretar caracteres especiales no especificados como:
  - `\` (barra invertida)
  - `;` (punto y coma)

### Manejo de comillas

- `'` (comilla simple) evita que se interpreten los metacaracteres entrecomillados.
- `"` (comilla doble) evita que se interpreten los metacaracteres excepto `$`.

### Redirecciones

- `<` redirige la entrada estándar.
- `>` redirige la salida estándar.
- `<<` [heredoc](https://linuxize.com/post/bash-heredoc) recibe un delimitador, luego lee desde la entrada hasta que se ingrese una línea que contenga solo dicho delimitador.
  - No es necesario actualizar el historial en este caso.
- `>>` redirige la salida en modo append.

### Pipes

- Implementar `|`, conectando el output de un comando al input del siguiente en la pipeline.

### Expansión de variables

- `$VAR`: expandir a su valor en el entorno.
- `$?`: expandir al estado de salida del último comando ejecutado.

### Atajos de teclado (comportamiento interactivo)

- Ctrl-C : imprime una nueva línea con el prompt.
- Ctrl-D : termina el shell.
- Ctrl-\ : no hace nada.

## Built-ins requeridos

- [`echo`](https://www.geeksforgeeks.org/bash-scripting-bash-echo-command) (con la opción `-n`)
- [`cd`](https://www.geeksforgeeks.org/cd-command-in-linux-with-examples) (solo con una ruta relativa o absoluta)
- [`pwd`](https://www.geeksforgeeks.org/pwd-command-in-linux-with-examples)
- [`export`](https://www.geeksforgeeks.org/export-command-in-linux-with-examples)
- [`unset`](https://man7.org/linux/man-pages/man1/unset.1p.html)
- [`env`](https://www.geeksforgeeks.org/env-command-in-linux-with-examples)
- [`exit`](https://linuxize.com/post/bash-exit)

## BONUS
- `&&`, `||` con paréntesis para prioridades.
- Los wildcards `*` deben funcionar para el directorio actual.


## ✅ Orden de Programación (Etapas)

### 🥇 Fase 1 – Infraestructura Básica

- Bucle principal y entrada con readline
- Manejo de señales básico (Ctrl-C, Ctrl-D, Ctrl-\)
- Ejecutar comandos simples sin pipes ni redirecciones
- Manejo de built-ins sin opciones complejas

### 🥈 Fase 2 – Parser Completo

- [`Lexing`](https://www.geeksforgeeks.org/c/c-lexical-analyser-lexer/)
- Tokenización con soporte de comillas `'` y `"`
- Expansión de variables (`$VAR`, `$?`)
- Manejo de errores de sintaxis

### 🥉 Fase 3 – Ejecutor Completo

- Pipes
- Redirecciones (`<`, `>`, `>>`, `<<`)
- Lógica de duplicación de fds

### 🏁 Fase 4 – Pulido y Estabilidad

- Pruebas intensivas
- Manejo de errores y estados de retorno
- Pruebas con valgrind para fugas de memoria
- Comprobación del comportamiento frente a casos extremos
- [Hoja de Correción](https://github.com/zafraedu/minishell/blob/main/assets/es.eval.pdf)

## 🧩 Coordinación

- La mayoría de grupos dividen el trabajo en `Front-end:`Lexing/Parsing, comandos y señales y `Back-end:` Ejecución del programa.
- Definir estructuras compartidas: t_command, t_token, t_shell
- Usar makefile con módulos separados (parser.o, executor.o, etc.)
- Uso de Git con ramas por feature (parser/heredoc, executor/pipes, etc.) [Feature branch workflow](https://www.atlassian.com/git/tutorials/comparing-workflows/feature-branch-workflow#:~:text=How%20it%20works,work%20on%20a%20new%20feature.)
- Reuniones para revisión de integración

##  📖 Guías y ayudas:
- [42-cursus.gitbook](https://42-cursus.gitbook.io/guide/3-rank-03/minishell/functions)
- [Guia](https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218)
