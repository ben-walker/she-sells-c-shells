%option noyywrap
%option nounput
%option noinput

    enum { NUM_ARGS = 100 };
    char *args[NUM_ARGS];
    int argCount;

WORD    [a-zA-Z0-9\/\.-]+
SPECIAL [12]?[()><|&;*]+
QUOTED  \"[^\"]*\"
%%
    argCount = 0;
    args[0] = NULL;

{WORD}|{SPECIAL}|{QUOTED} {
    if (argCount < NUM_ARGS - 1) {
        args[argCount++] = strdup(yytext);
        args[argCount] = NULL;
    }
}
\n      return (int)args;
[ \t]+  |
.       ;
%%
char **getln() {
	yylex();
    return args;
}
