%{
#include <string.h>
#include "parser.h"
enum { word, less, gt, pipesym, ret, amp };
%}
%%
\n      return ret;
"<"     return less;
">"     return gt;
"|"     return pipesym;
"&"     return amp;
[ \t]+      ;
[^<>|& \t\n]+   return word;
%%
char *argv[1024];

struct command read_command_line() {
    int ind;
    struct command cmd;
    cmd.argv = argv;

again:
    printf("ti2sh$ ");
    fflush(stdout);
    cmd.background = 0;
    ind = 0;

    for (;;) {
    switch (yylex()) {
    case word:
        argv[ind++] = strdup(yytext);
        break;
    case less:
    case gt:
    case pipesym:
        fprintf(stderr, "ti2sh: Ein-/Ausgabe-Umlenkung nicht implementiert!\n");
        goto junk;
    case amp:
        cmd.background = 1;
        if (yylex() != ret) {
        fprintf(stderr, "ti2sh: Mehrere Kommandos nicht implementiert!\n");
        goto junk;
        }
        /* fall through */
    case ret:
        if (ind == 0)
        goto again;
        argv[ind] = 0;
        return cmd;
    }
    }
 junk:
    while (yylex() != ret)
    ;
    goto again;
}

int yywrap() {
    printf("(bye)\n");
    exit(0);
}
