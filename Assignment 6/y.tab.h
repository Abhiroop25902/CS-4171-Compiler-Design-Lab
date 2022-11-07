/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SEMICOLON_TOK = 258,
    LBRAC_TOK = 259,
    RBRAC_TOK = 260,
    LPAREN_TOK = 261,
    RPAREN_TOK = 262,
    LBRACK_TOK = 263,
    RBRACK_TOK = 264,
    INT_TOK = 265,
    CHAR_TOK = 266,
    FLOAT_TOK = 267,
    INT_CONST_TOK = 268,
    CHAR_CONST_TOK = 269,
    MAIN_TOK = 270,
    COMMA_TOK = 271,
    ID_TOK = 272,
    EQ_TOK = 273,
    IF_TOK = 274,
    ELSE_TOK = 275,
    GT_TOK = 276,
    EQ_EQ_TOK = 277,
    LT_TOK = 278,
    GEQU_TOK = 279,
    LEQU_TOK = 280,
    PLUS_TOK = 281,
    INCRMNT_TOK = 282,
    ASUM_TOK = 283,
    MINUS_TOK = 284,
    DCRMNT_TOK = 285,
    ADIFF_TOK = 286,
    ASTERISK_TOK = 287,
    APROD_TOK = 288,
    DIVIDE_TOK = 289,
    AQUOT_TOK = 290,
    BITWISE_AND_TOK = 291,
    ABIT_AND_TOK = 292,
    AND_TOK = 293,
    BITWISE_OR_TOK = 294,
    ABIT_OR_TOK = 295,
    OR_TOK = 296,
    FOR_TOK = 297,
    WHILE_TOK = 298,
    DO_TOK = 299,
    RETURN_TOK = 300,
    BREAK_TOK = 301
  };
#endif
/* Tokens.  */
#define SEMICOLON_TOK 258
#define LBRAC_TOK 259
#define RBRAC_TOK 260
#define LPAREN_TOK 261
#define RPAREN_TOK 262
#define LBRACK_TOK 263
#define RBRACK_TOK 264
#define INT_TOK 265
#define CHAR_TOK 266
#define FLOAT_TOK 267
#define INT_CONST_TOK 268
#define CHAR_CONST_TOK 269
#define MAIN_TOK 270
#define COMMA_TOK 271
#define ID_TOK 272
#define EQ_TOK 273
#define IF_TOK 274
#define ELSE_TOK 275
#define GT_TOK 276
#define EQ_EQ_TOK 277
#define LT_TOK 278
#define GEQU_TOK 279
#define LEQU_TOK 280
#define PLUS_TOK 281
#define INCRMNT_TOK 282
#define ASUM_TOK 283
#define MINUS_TOK 284
#define DCRMNT_TOK 285
#define ADIFF_TOK 286
#define ASTERISK_TOK 287
#define APROD_TOK 288
#define DIVIDE_TOK 289
#define AQUOT_TOK 290
#define BITWISE_AND_TOK 291
#define ABIT_AND_TOK 292
#define AND_TOK 293
#define BITWISE_OR_TOK 294
#define ABIT_OR_TOK 295
#define OR_TOK 296
#define FOR_TOK 297
#define WHILE_TOK 298
#define DO_TOK 299
#define RETURN_TOK 300
#define BREAK_TOK 301

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 21 "test.y"

        double dval;
        int val;
        char *name;
        node *sNode;

#line 156 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
