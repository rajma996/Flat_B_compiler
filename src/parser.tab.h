/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
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
    int_datatype = 258,
    array_num_index = 259,
    array_identi_index = 260,
    label = 261,
    if_token = 262,
    else_token = 263,
    for_token = 264,
    print = 265,
    comma = 266,
    read_token = 267,
    codeblock = 268,
    declblock = 269,
    println = 270,
    goto_token = 271,
    colon = 272,
    lcb = 273,
    rcb = 274,
    lrb = 275,
    rrb = 276,
    pluss = 277,
    minuss = 278,
    mul = 279,
    lt = 280,
    lte = 281,
    gt = 282,
    gte = 283,
    eq = 284,
    eqeq = 285,
    neq = 286,
    andand = 287,
    oror = 288,
    mod = 289,
    divi = 290,
    rsb = 291,
    lsb = 292,
    exit_command = 293,
    number = 294,
    identifier = 295,
    strings = 296
  };
#endif

/* Value type.  */


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
