%{
    int numArgs = 100;
    char *args[100];
    int argCount = 0;
%}
WORD [a-zA-Z0-9\/\.-]+
SPECIAL [()><|&;*]
%option noyywrap

%%

%{
argCount = 0;
args[0] = NULL;
%}
{WORD}|{SPECIAL} {
    if (argCount < numArgs - 1) {
        args[argCount++] = (char *)strdup(yytext);
        args[argCount] = NULL;
    }
}

\n return (int)args;

[ \t]+

.

%%

char **getln() {
    // return (char **)yylex();
	yylex();
    return args;
}
