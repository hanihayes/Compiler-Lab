/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
    NUM = 258,
    PLUS = 259,
    MINUS = 260,
    MUL = 261,
    DIV = 262,
    BEG = 263,
    READ = 264,
    WRITE = 265,
    END = 266,
    ID = 267,
    CONN = 268,
    ASSGN = 269,
    EX = 270,
    IF = 271,
    THEN = 272,
    ELSE = 273,
    ENDIF = 274,
    GT = 275,
    GE = 276,
    LE = 277,
    LT = 278,
    EQ = 279,
    NE = 280,
    WHILE = 281,
    ENDWHILE = 282,
    DO = 283,
    BREAK = 284,
    CONTINUE = 285,
    INTTYPE = 286,
    BOOLTYPE = 287
  };
#endif
/* Tokens.  */
#define NUM 258
#define PLUS 259
#define MINUS 260
#define MUL 261
#define DIV 262
#define BEG 263
#define READ 264
#define WRITE 265
#define END 266
#define ID 267
#define CONN 268
#define ASSGN 269
#define EX 270
#define IF 271
#define THEN 272
#define ELSE 273
#define ENDIF 274
#define GT 275
#define GE 276
#define LE 277
#define LT 278
#define EQ 279
#define NE 280
#define WHILE 281
#define ENDWHILE 282
#define DO 283
#define BREAK 284
#define CONTINUE 285
#define INTTYPE 286
#define BOOLTYPE 287

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
