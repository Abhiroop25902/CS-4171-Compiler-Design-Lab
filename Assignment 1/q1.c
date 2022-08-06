#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "uthash.h" // for hashmap
// source: https://troydhanson.github.io/uthash/userguide.html

/* Single caharacter lexemes */
#define LPAREN_TOK '('
#define GT_TOK '>'
#define LT_TOK '<'
#define RPAREN_TOK ')'
#define EQ_TOK '='
#define MINUS_TOK '-'
#define SEMICOLON_TOK ';'
#define HASH_TOK '#'
#define CURLY_BRACKET_START_TOK '{'
#define CURLY_BRACKET_END_TOK '}'
#define SQUARE_BRACKET_START_TOK '['
#define SQUARE_BRACKET_END_TOK ']'
#define EQUAL_TOK '='
#define SEMICOLON_TOK ';'
#define ADD_TOK '+'
#define MINUS_TOK '-'
#define DOUBLE_QUOTE_TOK '"'
#define COMMA_TOK ','
#define DIVIDE_TOK '/'
#define MULTIPLY_TOK '*'
#define MODULO_TOK '%'
#define NOT_TOK '!'
#define AND_TOK '&'
#define OR_TOK '|'
#define XOR_TOK '^'
#define COMPLEMENT_TOK '~'
/*....................
.......................*/
/* Reserved words */
#define WHILE_TOK 256
#define INCLUDE_TOK 257
#define VOID_TOK 258
#define FOR_TOK 259
#define INT_TOK 260
#define FLOAT_TOK 261
#define LONG_TOK 262
#define CHAR_TOK 263
#define ELSE_TOK 264

/*....................
.......................*/
/* Identifier, constants..*/
#define INTCONST 350
#define HEADER 351
int nextIdTok = 352; // will be the idtok for next variables
/*....................
.......................*/

// yyin is the file pointer which will be used for input from the file (argv[1])
FILE *yyin;
// output file
FILE *yyout;

// Variable yytext is a pointer to the matched string (NULL-terminated)
char *yytext;
const int YYTEXT_MAX_SIZE = 100;

// length of matched string
int yyleng;

// TODO: found out what yylval means
// yylval -> value associated with token

// token_struct for the map
struct map_struct
{
    const char *name; /* key */
    int tok;
    UT_hash_handle hh; /* makes this structure hashable */
};
struct map_struct *tokens = NULL; // The array of the map

void fixMultipleToken()
{
    for (int i = 0; i < yyleng; i++)
    {
        if (yytext[i] == '<' ||
            yytext[i] == '>' ||
            yytext[i] == '{' ||
            yytext[i] == '}' ||
            yytext[i] == '(' ||
            yytext[i] == ')' ||
            yytext[i] == '[' ||
            yytext[i] == ']' ||
            yytext[i] == ';' ||
            yytext[i] == '+' ||
            yytext[i] == '-' ||
            yytext[i] == ',' ||
            yytext[i] == '"')
        {
            if (fseek(yyin, -(yyleng - i), SEEK_CUR))
                perror("fseek error");
            yyleng = i;
            yytext[yyleng] = '\0';
            break;
        }
    }
}

bool isSingleChar(char c)
{
    if (yytext[0] == c)
    {
        if (fseek(yyin, -(yyleng - 1), SEEK_CUR) == -1)
            perror("fseek error");
        yytext[1] = '\0';

        return true;
    }

    return false;
}

bool isWord(char *word)
{
    return strcmp(yytext, word) == 0;
}

bool isHeader()
{
    if (yyleng < 2)
        return false;
    char extension[2];

    memcpy(extension, &yytext[yyleng - 2], 2);

    return strcmp(extension, ".h") == 0;
}

bool isDigit(char c)
{
    return (
        ((c - '0') >= 0) &&
        ((c - '0') <= 9));
}

bool isConstant()
{
    for (int i = 0; i < yyleng; i++)
        if (!isDigit(yytext[i]))
            return false;

    return true;
}

// call to invoke lexer, returns token
int yylex()
{
    int res = -1;
    if (fscanf(yyin, "%s", yytext) == EOF)
        return res;

    yyleng = strlen(yytext);

    // check for all one char tokens
    if (isSingleChar(HASH_TOK))
        res = HASH_TOK;
    else if (isSingleChar(LT_TOK))
        res = LT_TOK;
    else if (isSingleChar(GT_TOK))
        res = LT_TOK;
    else if (isSingleChar(CURLY_BRACKET_START_TOK))
        res = CURLY_BRACKET_START_TOK;
    else if (isSingleChar(CURLY_BRACKET_END_TOK))
        res = CURLY_BRACKET_END_TOK;
    else if (isSingleChar(LPAREN_TOK))
        res = LPAREN_TOK;
    else if (isSingleChar(RPAREN_TOK))
        res = RPAREN_TOK;
    else if (isSingleChar(SQUARE_BRACKET_START_TOK))
        res = SQUARE_BRACKET_START_TOK;
    else if (isSingleChar(SQUARE_BRACKET_END_TOK))
        res = SQUARE_BRACKET_END_TOK;
    else if (isSingleChar(EQUAL_TOK))
        res = EQUAL_TOK;
    else if (isSingleChar(SEMICOLON_TOK))
        res = SEMICOLON_TOK;
    else if (isSingleChar(ADD_TOK))
        res = ADD_TOK;
    else if (isSingleChar(MINUS_TOK))
        res = MINUS_TOK;
    else if (isSingleChar(DOUBLE_QUOTE_TOK))
        res = DOUBLE_QUOTE_TOK;
    else if (isSingleChar(COMMA_TOK))
        res = COMMA_TOK;
    else if (isSingleChar(DIVIDE_TOK))
        res = DIVIDE_TOK;
    else if (isSingleChar(MULTIPLY_TOK))
        res = MULTIPLY_TOK;
    else if (isSingleChar(MODULO_TOK))
        res = MODULO_TOK;
    else if (isSingleChar(NOT_TOK))
        res = NOT_TOK;
    else if (isSingleChar(AND_TOK))
        res = AND_TOK;
    else if (isSingleChar(OR_TOK))
        res = OR_TOK;
    else if (isSingleChar(XOR_TOK))
        res = XOR_TOK;
    else if (isSingleChar(COMPLEMENT_TOK))
        res = COMPLEMENT_TOK;

    if (res != -1)
    {
        printf("%s\t", yytext);
        return res;
    }

    // now the string can have multiple tokens in it so we need to take only one on yytext
    // Eg: 10; need to be changed to 10 and ;
    fixMultipleToken();

    if (isConstant())
        res = INTCONST;
    else if (isHeader())
        res = HEADER;
    else if (isWord("include"))
        res = INCLUDE_TOK;
    else if (isWord("void"))
        res = HEADER;
    else if (isWord("for"))
        res = FOR_TOK;
    else if (isWord("int"))
        res = FOR_TOK;
    else if (isWord("float"))
        res = FLOAT_TOK;
    else if (isWord("long"))
        res = LONG_TOK;
    else if (isWord("while"))
        res = WHILE_TOK;
    else if (isWord("char"))
        res = CHAR_TOK;
    else if (isWord("else"))
        res = ELSE_TOK;

    printf("%s\t", yytext);

    if (res == -1) // i.e the token is a variable name
    {
        // idea: we have a map which has key as string, and value as token number
        //  we first check if key is already present or not
        //  if present we return it's token
        //  else we make a new entry in map with the string as key and new token as value
        struct map_struct *s;
        HASH_FIND_STR(tokens, yytext, s);

        if (s) // i.e data is found
            return s->tok;

        // else data is not present hence we add it and return token
        s = (struct map_struct *)malloc(sizeof *s);
        s->name = yytext;
        s->tok = nextIdTok;
        nextIdTok++;
        HASH_ADD_KEYPTR(hh, tokens, s->name, strlen(s->name), s);
        return s->tok;
    }

    return res;
}

// wrapup, return 1 if done, 0 if not done
int yywrap(void)
{
    fclose(yyin);
    free(yytext);

    struct map_struct *s, *tmp;

    HASH_ITER(hh, tokens, s, tmp){
        HASH_DEL(tokens, s);
        free(s);
    }
}

void main(int argc, char *argv[])
{
    int token;
    if (argc != 2)
    {
        printf("Error: add only a filename\n");
        exit(-1);
    }

    yyin = fopen(argv[1], "r");
    if(yyin == NULL)
        perror("fopen() error");

    yytext = (char *)malloc(sizeof(char) * YYTEXT_MAX_SIZE);
    while (!feof(yyin))
    {
        token = yylex();
        printf("%d\n", token);
    }
    yywrap();
}