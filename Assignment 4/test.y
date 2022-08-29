// TODO: clean output in console
%{
#include"lex.yy.c"
void yyerror(char *);
int scope=0;
%}

%token SEMICOLON_TOK
%token LCRLY_TOK
%token RCRLY_TOK
%token LPAREN_TOK
%token RPAREN_TOK
%token INT_TOK
%token MAIN_TOK
%token COMMA_TOK
%token ID_TOK
%token EQUAL_TOK
%token INT_CONST
%token FLOAT_TOK
%token FLOAT_CONST
%token CHAR_TOK
%token CHAR_CONST
%token IF_TOK
%token COND_OR_TOK
%token COND_AND_TOK
%token LT_TOK
%token GT_TOK
%token COND_EQUAL_TOK
%token NOT_TOK
%token ELSE_TOK
%token FOR_TOK
%token INCREMENT_TOK
%token WHILE_TOK
%token STRING_CONST
%token RETURN_TOK




%start S




%%
S               :       S FUNC 
                |       S stmt                         
                |       FUNC
                |       stmt
                ;

FUNC            :       datatype  MAIN_TOK LPAREN_TOK RPAREN_TOK BLOCK    {printf("Syntax for Main Function is Ok....\n");}
                |       datatype  ID_TOK LPAREN_TOK RPAREN_TOK BLOCK
                ;

BLOCK           :       LCRLY_TOK  STATEMENTS  BLOCKS  RCRLY_TOK
                ;       

BLOCKS          :       BLOCK STATEMENTS BLOCKS                                {}
                |
                ;

STATEMENTS      :       STATEMENTS stmt
                |       STATEMENTS conditional
                |       STATEMENTS iterative
                |       STATEMENTS func_call
                |       
                ; 

// TODO: 2 shift error from here
func_call       :       ID_TOK LPAREN_TOK PARAMETERS RPAREN_TOK func_end
                ;

func_end        :       SEMICOLON_TOK
                |       
                ;

PARAMETERS      :       PARAMETER PARAMETERS
                |       COMMA_TOK PARAMETERS
                |
                ;

PARAMETER       :       ID_TOK
                |       const
                |       func_call
                ;

iterative       :       FOR_TOK LPAREN_TOK DECLARATION SEMICOLON_TOK comparision SEMICOLON_TOK DECLARATION RPAREN_TOK BLOCK
                |       WHILE_TOK LPAREN_TOK comparision RPAREN_TOK BLOCK
                ;

conditional     :       IF_TOK LPAREN_TOK cond_expression RPAREN_TOK BLOCK
                |       IF_TOK LPAREN_TOK cond_expression RPAREN_TOK BLOCK ELSE_TOK BLOCK
                ;

// TODO: This is givong 4 warnings
cond_expression :       cond_expression COND_OR_TOK cond_expression
                |       cond_expression COND_AND_TOK cond_expression
                |       LPAREN_TOK cond_expression RPAREN_TOK 
                |       NOT_TOK LPAREN_TOK cond_expression RPAREN_TOK 
                |       comparision

comparision     :       data LT_TOK data 
                |       data GT_TOK data
                |       data COND_EQUAL_TOK data
                |       const
                ;

data            :       INT_CONST
                |       FLOAT_CONST
                |       ID_TOK
                ;
     

stmt            :       DECLARATION SEMICOLON_TOK       {}
                ;


DECLARATION     :       datatype id_token       {printf("Syntax of The Declaration Statement is Correct.....\n");}
                |       RETURN_TOK ret_data
                ;

// TODO: one shift reduce warning
ret_data        :       PARAMETER
                |       
                ;

datatype        :       INT_TOK
                |       FLOAT_TOK
                |       CHAR_TOK
                |
                ;

id_token        :       id_token COMMA_TOK ID_TOK          {}
                |       ID_TOK                             {}
                |       ID_TOK EQUAL_TOK const
                |       ID_TOK INCREMENT_TOK
                |       INCREMENT_TOK ID_TOK
                ;

const           :       INT_CONST
                |       FLOAT_CONST
                |       CHAR_CONST
                |       STRING_CONST
                ;



%%




int main(int argc, char* argv[])
{
   if(argc != 2){
        fprintf(stderr, "Error: Need a File Name");
        exit(1);
   }     

   yyin = fopen(argv[1], "r");
   if (yyin == NULL)
      perror("fopen() error");

   if (yyparse()==0) printf("Parsed Successfully\n");
   else printf("\nParsing Error at Line No %d\n", yylineno);

   return(0);	

}

void yyerror(char *s)
{
	printf("yyerror: %s\n",s);
}