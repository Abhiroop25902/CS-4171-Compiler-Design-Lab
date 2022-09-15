// TODO: clean output in console
%{
#include"lex.yy.c"
#include "hash_table.c"
void yyerror(char *);
int scope=0;
char data_type[10];
hash_table* h = NULL;
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
%token ADD_TOK
%token SUB_TOK
%token MUL_TOK
%token DIV_TOK




%start S



// TODO: test.y: warning: 14 shift/reduce conflicts [-Wconflicts-sr]
%%
S                 :  FUNC S
                  |  stmt S                        
                  |  FUNC
                  |  stmt
                  ;

FUNC              :  datatype  MAIN_TOK LPAREN_TOK {scope++;} PARAMETERS {scope--;} RPAREN_TOK BLOCK 
                  |  datatype  ID_TOK LPAREN_TOK {scope++;} PARAMETERS {scope--;} RPAREN_TOK BLOCK    
                  ;

BLOCK             :  LCRLY_TOK  {scope++;} STATEMENTS  BLOCKS  {hash_table_end_scope(h, scope); scope--; } RCRLY_TOK  
                  |  SEMICOLON_TOK
                  ;       

BLOCKS            :  BLOCK STATEMENTS BLOCKS                                
                  |
                  ;

STATEMENTS        :  STATEMENTS stmt 
                  |  STATEMENTS conditional
                  |  STATEMENTS iterative
                  |  STATEMENTS func_call
                  |       
                  ; 

func_call         :  ID_TOK LPAREN_TOK PARAMETERS RPAREN_TOK SEMICOLON_TOK
                  |  ID_TOK LPAREN_TOK PARAMETERS RPAREN_TOK
                  ;

PARAMETERS        :  PARAMETER PARAMETERS
                  |  COMMA_TOK PARAMETERS
                  |  DECLARATION  
                  |
                  ;

PARAMETER         :  ID_TOK
                  |  const
                  |  func_call
                  ;

iterative         :  FOR_TOK LPAREN_TOK DECLARATION SEMICOLON_TOK comparision SEMICOLON_TOK DECLARATION RPAREN_TOK BLOCK
                  |  WHILE_TOK LPAREN_TOK comparision RPAREN_TOK BLOCK
                  ;

conditional       :  IF_TOK LPAREN_TOK cond_expression RPAREN_TOK BLOCK
                  |  IF_TOK LPAREN_TOK cond_expression RPAREN_TOK BLOCK ELSE_TOK BLOCK
                  |  IF_TOK LPAREN_TOK cond_expression RPAREN_TOK BLOCK ELSE_TOK conditional
                  ;

cond_expression   :  cond_expression cond_op cond_expression
                  |  LPAREN_TOK cond_expression RPAREN_TOK 
                  |  NOT_TOK LPAREN_TOK cond_expression RPAREN_TOK 
                  |  comparision     
                  ;

cond_op           :  COND_AND_TOK
                  |  COND_OR_TOK
                  ;

comparision       :  data LT_TOK data 
                  |  data GT_TOK data
                  |  data COND_EQUAL_TOK data
                  |  const
                  ;

data              :  INT_CONST
                  |  FLOAT_CONST
                  |  ID_TOK
                  ;
     

stmt              :  DECLARATION SEMICOLON_TOK        
                  ;


DECLARATION       :  datatype id_token   {hash_table_insert(h, scope, data_type, var_name);}
                  |  id_token            {if(!hash_table_isPresent(h, var_name)){printf("Error: unknown name '%s' found\n", var_name); exit(1);}} 
                  |  RETURN_TOK ret_data
                  ;

ret_data          :  PARAMETER
                  |       
                  ;

datatype          :  INT_TOK        {strcpy(data_type, yytext);}
                  |  FLOAT_TOK      {strcpy(data_type, yytext);}
                  |  CHAR_TOK       {strcpy(data_type, yytext);}  
                  ;

id_token          :  id_token COMMA_TOK id_token   // TODO: comma parameters
                  |  ID_TOK                       
                  |  ID_TOK EQUAL_TOK expression 
                  |  ID_TOK INCREMENT_TOK
                  |  INCREMENT_TOK ID_TOK
                  ;

expression        :  expression expression_op expression
                  |  LPAREN_TOK expression RPAREN_TOK
                  |  const
                  ;

expression_op     :  ADD_TOK
                  |  SUB_TOK
                  |  MUL_TOK
                  |  DIV_TOK
                  ;

const             :  INT_CONST
                  |  FLOAT_CONST
                  |  CHAR_CONST
                  |  STRING_CONST
                  ;



%%

int main(int argc, char* argv[])
{
   if(argc != 2){
        fprintf(stderr, "Error: Need a File Name");
        exit(1);
   }     
   h = create_hash_table();
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
