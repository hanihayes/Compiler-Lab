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
    BEG = 259,
    READ = 260,
    WRITE = 261,
    END = 262,
    ASGN = 263,
    ID = 264,
    IF = 265,
    THEN = 266,
    WHILE = 267,
    ENDWHILE = 268,
    ENDIF = 269,
    DO = 270,
    ELSE = 271,
    BREAK = 272,
    CONTINUE = 273,
    DECL = 274,
    ENDDECL = 275,
    INT = 276,
    STR = 277,
    CONN = 278,
    INTTYPE = 279,
    STRTYPE = 280,
    BOOLTYPE = 281,
    VARIABLE = 282,
    STRING = 283,
    ASSGN = 284,
    PLUS = 285,
    MINUS = 286,
    MUL = 287,
    DIV = 288,
    MOD = 289,
    LT = 290,
    GT = 291,
    LE = 292,
    GE = 293,
    EQ = 294,
    NE = 295
  };
#endif
/* Tokens.  */
#define NUM 258
#define BEG 259
#define READ 260
#define WRITE 261
#define END 262
#define ASGN 263
#define ID 264
#define IF 265
#define THEN 266
#define WHILE 267
#define ENDWHILE 268
#define ENDIF 269
#define DO 270
#define ELSE 271
#define BREAK 272
#define CONTINUE 273
#define DECL 274
#define ENDDECL 275
#define INT 276
#define STR 277
#define CONN 278
#define INTTYPE 279
#define STRTYPE 280
#define BOOLTYPE 281
#define VARIABLE 282
#define STRING 283
#define ASSGN 284
#define PLUS 285
#define MINUS 286
#define MUL 287
#define DIV 288
#define MOD 289
#define LT 290
#define GT 291
#define LE 292
#define GE 293
#define EQ 294
#define NE 295

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
