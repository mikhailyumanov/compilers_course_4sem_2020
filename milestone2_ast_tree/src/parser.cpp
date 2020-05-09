// A Bison parser, made by GNU Bison 3.5.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.





#include "parser.hh"


// Unqualified %code blocks.
#line 22 "parser.y"

    #include "driver.hh"
    #include "location.hh"

    // include nodes
    // program
    #include "program/Program.hpp"
    #include "program/MainClass.hpp"
    #include "program/ClassDeclList.hpp"
    // statements
    #include "statements/Statement.hpp"
    #include "statements/PrintStmt.hpp"
    #include "statements/StmtList.hpp"
    // expressions
    #include "expressions/Expression.hpp"
    #include "expressions/BoolConstExpression.hpp"
    // declarations

    static yy::parser::symbol_type yylex(Scanner &scanner, Driver& driver) {
        return scanner.ScanToken();
    }

#line 68 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 159 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"


  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  parser::parser (Scanner &scanner_yyarg, Driver &driver_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg),
      driver (driver_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_number_type
  parser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[+state];
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 4: // "-"
      case 5: // "+"
      case 6: // "*"
      case 7: // "/"
      case 8: // "&&"
      case 9: // "||"
      case 10: // "<"
      case 11: // ">"
      case 12: // "=="
      case 13: // "%"
      case 45: // "number"
      case 50: // integer_literal
      case 51: // binary_operator
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case 53: // type
        value.YY_MOVE_OR_COPY< std::pair<std::string, bool> > (YY_MOVE (that.value));
        break;

      case 52: // lvalue
        value.YY_MOVE_OR_COPY< std::pair<std::string, int> > (YY_MOVE (that.value));
        break;

      case 49: // expr
        value.YY_MOVE_OR_COPY< std::pair<std::vector<int>, bool> > (YY_MOVE (that.value));
        break;

      case 44: // "identifier"
      case 54: // simple_type
      case 55: // array_type
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 4: // "-"
      case 5: // "+"
      case 6: // "*"
      case 7: // "/"
      case 8: // "&&"
      case 9: // "||"
      case 10: // "<"
      case 11: // ">"
      case 12: // "=="
      case 13: // "%"
      case 45: // "number"
      case 50: // integer_literal
      case 51: // binary_operator
        value.move< int > (YY_MOVE (that.value));
        break;

      case 53: // type
        value.move< std::pair<std::string, bool> > (YY_MOVE (that.value));
        break;

      case 52: // lvalue
        value.move< std::pair<std::string, int> > (YY_MOVE (that.value));
        break;

      case 49: // expr
        value.move< std::pair<std::vector<int>, bool> > (YY_MOVE (that.value));
        break;

      case 44: // "identifier"
      case 54: // simple_type
      case 55: // array_type
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 4: // "-"
      case 5: // "+"
      case 6: // "*"
      case 7: // "/"
      case 8: // "&&"
      case 9: // "||"
      case 10: // "<"
      case 11: // ">"
      case 12: // "=="
      case 13: // "%"
      case 45: // "number"
      case 50: // integer_literal
      case 51: // binary_operator
        value.copy< int > (that.value);
        break;

      case 53: // type
        value.copy< std::pair<std::string, bool> > (that.value);
        break;

      case 52: // lvalue
        value.copy< std::pair<std::string, int> > (that.value);
        break;

      case 49: // expr
        value.copy< std::pair<std::vector<int>, bool> > (that.value);
        break;

      case 44: // "identifier"
      case 54: // simple_type
      case 55: // array_type
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 4: // "-"
      case 5: // "+"
      case 6: // "*"
      case 7: // "/"
      case 8: // "&&"
      case 9: // "||"
      case 10: // "<"
      case 11: // ">"
      case 12: // "=="
      case 13: // "%"
      case 45: // "number"
      case 50: // integer_literal
      case 51: // binary_operator
        value.move< int > (that.value);
        break;

      case 53: // type
        value.move< std::pair<std::string, bool> > (that.value);
        break;

      case 52: // lvalue
        value.move< std::pair<std::string, int> > (that.value);
        break;

      case 49: // expr
        value.move< std::pair<std::vector<int>, bool> > (that.value);
        break;

      case 44: // "identifier"
      case 54: // simple_type
      case 55: // array_type
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (scanner, driver));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 4: // "-"
      case 5: // "+"
      case 6: // "*"
      case 7: // "/"
      case 8: // "&&"
      case 9: // "||"
      case 10: // "<"
      case 11: // ">"
      case 12: // "=="
      case 13: // "%"
      case 45: // "number"
      case 50: // integer_literal
      case 51: // binary_operator
        yylhs.value.emplace< int > ();
        break;

      case 53: // type
        yylhs.value.emplace< std::pair<std::string, bool> > ();
        break;

      case 52: // lvalue
        yylhs.value.emplace< std::pair<std::string, int> > ();
        break;

      case 49: // expr
        yylhs.value.emplace< std::pair<std::vector<int>, bool> > ();
        break;

      case 44: // "identifier"
      case 54: // simple_type
      case 55: // array_type
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 21:
#line 163 "parser.y"
                    { driver.variables[yystack_[1].value.as < std::string > ()] = 
                          std::make_pair(std::vector<int>(), yystack_[2].value.as < std::pair<std::string, bool> > ().second); }
#line 758 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"
    break;

  case 22:
#line 166 "parser.y"
                  { yylhs.value.as < std::pair<std::string, bool> > () = std::make_pair(yystack_[0].value.as < std::string > (), 0); }
#line 764 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"
    break;

  case 23:
#line 167 "parser.y"
                  { yylhs.value.as < std::pair<std::string, bool> > () = std::make_pair(yystack_[0].value.as < std::string > (), 1); }
#line 770 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"
    break;

  case 28:
#line 171 "parser.y"
                                { yylhs.value.as < std::string > () = yystack_[2].value.as < std::string > (); }
#line 776 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"
    break;

  case 36:
#line 182 "parser.y"
           { std::cout << yystack_[2].value.as < std::pair<std::vector<int>, bool> > ().first[0] << std::endl; }
#line 782 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"
    break;

  case 37:
#line 184 "parser.y"
           { if (yystack_[3].value.as < std::pair<std::string, int> > ().second == -1) driver.variables[yystack_[3].value.as < std::pair<std::string, int> > ().first] = yystack_[1].value.as < std::pair<std::vector<int>, bool> > ();
             else driver.variables[yystack_[3].value.as < std::pair<std::string, int> > ().first].first[yystack_[3].value.as < std::pair<std::string, int> > ().second] = yystack_[1].value.as < std::pair<std::vector<int>, bool> > ().first[0]; }
#line 789 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"
    break;

  case 42:
#line 193 "parser.y"
                                  { yylhs.value.as < std::pair<std::string, int> > () = std::make_pair(yystack_[0].value.as < std::string > (), -1); }
#line 795 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"
    break;

  case 43:
#line 194 "parser.y"
                                  { yylhs.value.as < std::pair<std::string, int> > () = std::make_pair(yystack_[3].value.as < std::string > (), yystack_[1].value.as < std::pair<std::vector<int>, bool> > ().first[0]); }
#line 801 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"
    break;

  case 46:
#line 199 "parser.y"
                                { /*$$ = new BinOpExpression($1, $2, $3);*/ 
    int tmp = 0;
/*  switch($2) {
    case token::TOK_AND:     tmp = $1.first[0] && $3.first[0]; break;
    case token::TOK_OR:      tmp = $1.first[0] || $3.first[0]; break;
    case token::TOK_LESS:    tmp = $1.first[0] <  $3.first[0]; break;
    case token::TOK_GREATER: tmp = $1.first[0] >  $3.first[0]; break;
    case token::TOK_EQUAL:   tmp = $1.first[0] == $3.first[0]; break;
    case token::TOK_PLUS:    tmp = $1.first[0] +  $3.first[0]; break;
    case token::TOK_MINUS:   tmp = $1.first[0] -  $3.first[0]; break;
    case token::TOK_STAR:    tmp = $1.first[0] *  $3.first[0]; break;
    case token::TOK_SLASH:   tmp = $1.first[0] /  $3.first[0]; break;
    case token::TOK_RMNDR:   tmp = $1.first[0] %  $3.first[0]; break;
    default: break;
  }*/
  yylhs.value.as < std::pair<std::vector<int>, bool> > () = std::make_pair(std::vector<int>{tmp}, 0);
}
#line 823 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"
    break;

  case 47:
#line 217 "parser.y"
      { yylhs.value.as < std::pair<std::vector<int>, bool> > () = std::make_pair(std::vector<int>{yystack_[3].value.as < std::pair<std::vector<int>, bool> > ().first[yystack_[1].value.as < std::pair<std::vector<int>, bool> > ().first[0]]}, 0); }
#line 829 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"
    break;

  case 48:
#line 219 "parser.y"
                        { yylhs.value.as < std::pair<std::vector<int>, bool> > () = std::make_pair(std::vector<int>{(int)yystack_[2].value.as < std::pair<std::vector<int>, bool> > ().first.size()}, 0); }
#line 835 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"
    break;

  case 49:
#line 222 "parser.y"
      { yylhs.value.as < std::pair<std::vector<int>, bool> > () = std::make_pair(std::vector<int>(yystack_[1].value.as < std::pair<std::vector<int>, bool> > ().first[0]), 1); }
#line 841 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"
    break;

  case 50:
#line 225 "parser.y"
      { yylhs.value.as < std::pair<std::vector<int>, bool> > () = std::make_pair(std::vector<int>(1), 0); }
#line 847 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"
    break;

  case 51:
#line 228 "parser.y"
      { yylhs.value.as < std::pair<std::vector<int>, bool> > () = std::make_pair(std::vector<int>{!yystack_[0].value.as < std::pair<std::vector<int>, bool> > ().first[0]}, 0); }
#line 853 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"
    break;

  case 52:
#line 230 "parser.y"
                                     { yylhs.value.as < std::pair<std::vector<int>, bool> > () = yystack_[1].value.as < std::pair<std::vector<int>, bool> > (); }
#line 859 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"
    break;

  case 53:
#line 232 "parser.y"
                                     { yylhs.value.as < std::pair<std::vector<int>, bool> > () = driver.variables[yystack_[0].value.as < std::string > ()]; }
#line 865 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"
    break;

  case 54:
#line 235 "parser.y"
      { yylhs.value.as < std::pair<std::vector<int>, bool> > () = std::make_pair(std::vector<int>{yystack_[0].value.as < int > ()}, 0); }
#line 871 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"
    break;

  case 55:
#line 237 "parser.y"
                                     { /* TODO */ }
#line 877 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"
    break;

  case 56:
#line 240 "parser.y"
      { yylhs.value.as < std::pair<std::vector<int>, bool> > () = std::make_pair(std::vector<int>{1}, 0); }
#line 883 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"
    break;

  case 57:
#line 243 "parser.y"
      { yylhs.value.as < std::pair<std::vector<int>, bool> > () = std::make_pair(std::vector<int>{0}, 0); }
#line 889 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"
    break;

  case 58:
#line 245 "parser.y"
                                     { }
#line 895 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"
    break;

  case 59:
#line 247 "parser.y"
                          { yylhs.value.as < int > () = yystack_[0].value.as < int > (); }
#line 901 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"
    break;

  case 60:
#line 248 "parser.y"
                              { yylhs.value.as < int > () = -yystack_[0].value.as < int > (); }
#line 907 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"
    break;

  case 61:
#line 250 "parser.y"
                 { yylhs.value.as < int > () = yystack_[0].value.as < int > (); }
#line 913 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"
    break;

  case 62:
#line 250 "parser.y"
                        { yylhs.value.as < int > () = yystack_[0].value.as < int > (); }
#line 919 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"
    break;

  case 63:
#line 250 "parser.y"
                               { yylhs.value.as < int > () = yystack_[0].value.as < int > (); }
#line 925 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"
    break;

  case 64:
#line 250 "parser.y"
                                     { yylhs.value.as < int > () = yystack_[0].value.as < int > (); }
#line 931 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"
    break;

  case 65:
#line 250 "parser.y"
                                           { yylhs.value.as < int > () = yystack_[0].value.as < int > (); }
#line 937 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"
    break;

  case 66:
#line 251 "parser.y"
                 { yylhs.value.as < int > () = yystack_[0].value.as < int > (); }
#line 943 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"
    break;

  case 67:
#line 251 "parser.y"
                        { yylhs.value.as < int > () = yystack_[0].value.as < int > (); }
#line 949 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"
    break;

  case 68:
#line 251 "parser.y"
                               { yylhs.value.as < int > () = yystack_[0].value.as < int > (); }
#line 955 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"
    break;

  case 69:
#line 251 "parser.y"
                                     { yylhs.value.as < int > () = yystack_[0].value.as < int > (); }
#line 961 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"
    break;

  case 70:
#line 251 "parser.y"
                                           { yylhs.value.as < int > () = yystack_[0].value.as < int > (); }
#line 967 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"
    break;


#line 971 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[+yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yy_error_token_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yy_error_token_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    std::ptrdiff_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */
    if (!yyla.empty ())
      {
        symbol_number_type yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];

        int yyn = yypact_[+yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yy_error_token_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -71;

  const signed char parser::yytable_ninf_ = -43;

  const short
  parser::yypact_[] =
  {
     -19,   -25,    35,    33,     3,   -71,    27,    33,   -71,    44,
      -2,   -71,    46,    32,    40,    48,    37,   -71,   -71,   -71,
     -71,    43,    72,   -71,    21,   -71,   -71,   -71,    73,    51,
      59,    70,    89,   -71,   -71,    32,    93,    94,   -71,   -71,
     195,   101,    14,    91,   -71,    99,   -71,    74,    18,   -71,
     180,   180,   -71,   -71,    37,    78,     1,   180,   175,   -71,
     -71,   -71,   111,   112,   113,     1,   118,     6,   -71,     1,
     412,   -71,   127,    75,   -71,   -71,   -71,   109,   110,   -71,
     -71,   -71,   276,   -71,   145,   -71,   116,   128,     1,     1,
       1,   238,   100,     1,   412,   -71,   -71,   -71,   -71,   -71,
     -71,   -71,   -71,   -71,   -71,     1,   -33,     1,     1,   -71,
     -71,   -71,   124,   -71,   -71,     1,   129,   293,   310,   327,
     -71,   131,   344,   361,   -71,   138,   412,   257,   -71,   378,
     -71,   180,   180,   136,   119,   -71,   -71,     1,   -71,   -71,
     125,   -71,   -71,   146,   412,    28,   180,     1,   -71,     1,
     -71,   395,   412,   140,   -71
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,     0,     2,     0,     1,     0,     3,     4,     0,
       0,     5,     0,     0,     0,     0,     0,    24,    25,    26,
      27,     0,    22,    23,     0,    11,    14,    13,     0,     0,
       0,     0,     0,     7,    12,     0,     0,     0,    21,    28,
       0,     0,     0,     0,     8,     0,    16,     0,     0,    18,
       0,     0,    20,    17,     0,     0,     0,     0,     0,    55,
      56,    57,     0,     0,     0,     0,     0,    53,    59,     0,
       0,    54,     0,     0,    40,     9,    31,    58,     0,    19,
      60,    53,     0,    58,     0,    29,     0,     0,     0,     0,
       0,     0,     0,     0,    51,    67,    66,    68,    69,    61,
      62,    63,    64,    65,    70,     0,     0,     0,     0,    15,
      10,    39,     0,    52,    32,     0,     0,     0,     0,     0,
      38,     0,     0,     0,    48,     0,    46,     0,     6,     0,
      50,     0,     0,     0,     0,    43,    47,     0,    37,    49,
      33,    35,    30,     0,    44,     0,     0,     0,    41,     0,
      34,     0,    45,     0,    36
  };

  const short
  parser::yypgoto_[] =
  {
     -71,   -52,   -71,   -71,   -71,   -10,   107,   -71,   -71,   -71,
     -71,   159,    15,   132,   -22,   -71,   -71,   -71,   122,     7,
     -71,   -70,   -71,   -50,   -71
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,    70,    71,   107,    72,    21,    22,    23,     2,     7,
       3,     8,    73,    24,    25,    26,    43,    48,    49,    74,
      87,    75,    76,    83,   145
  };

  const short
  parser::yytable_[] =
  {
      77,    77,    34,   110,    82,    55,    30,    77,   110,   -42,
     124,   125,     1,    91,   110,    56,    13,    94,    34,     4,
      27,     9,    93,    77,    58,    59,    60,    61,    77,    46,
      14,    27,    47,    53,    77,     5,   117,   118,   119,    54,
      33,   122,    27,   148,    47,    81,    68,    27,    69,   149,
      17,    18,    19,   123,    16,   126,   127,    17,    18,    19,
      20,   140,   141,   129,     6,    16,    78,    20,    17,    18,
      19,    10,    84,    17,    18,    19,   150,    12,    20,    55,
      15,    77,    77,    20,    28,   144,    29,    31,    32,    56,
      36,    35,    38,    57,   109,   151,    77,   152,    58,    59,
      60,    61,    62,    37,    63,    64,    39,    41,    42,    50,
      65,    17,    18,    19,    55,    66,    45,    51,    52,    67,
      68,    20,    69,    80,    56,    88,    89,    90,    57,   112,
     108,   111,   115,    58,    59,    60,    61,    62,    92,    63,
      64,   121,   116,   128,   130,    65,    17,    18,    19,    55,
      66,   134,   137,   146,    67,    68,    20,    69,   142,    56,
     147,   143,   154,    57,   114,    86,    11,    40,    58,    59,
      60,    61,    62,     0,    63,    64,    79,     0,     0,     0,
      65,    17,    18,    19,    55,    66,     0,     0,     0,    67,
      68,    20,    69,     0,    56,     0,     0,     0,    57,     0,
       0,     0,     0,    58,    59,    60,    61,    62,     0,    63,
      64,    17,    18,    19,    44,    65,    17,    18,    19,    85,
      66,    20,     0,     0,    67,    68,    20,    69,    16,     0,
       0,    17,    18,    19,     0,     0,     0,     0,     0,     0,
       0,    20,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,     0,     0,   105,     0,     0,     0,   106,     0,
     120,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,     0,     0,   105,     0,     0,     0,   106,     0,   138,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
       0,   113,   105,     0,     0,     0,   106,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,     0,   131,   105,
       0,     0,     0,   106,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,     0,   132,   105,     0,     0,     0,
     106,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,     0,   133,   105,     0,     0,     0,   106,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,     0,     0,
     105,   135,     0,     0,   106,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,     0,     0,   105,   136,     0,
       0,   106,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,     0,     0,   105,   139,     0,     0,   106,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,     0,
     153,   105,     0,     0,     0,   106,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,     0,     0,   105,     0,
       0,     0,   106
  };

  const short
  parser::yycheck_[] =
  {
      50,    51,    24,    73,    56,     4,    16,    57,    78,     3,
      43,    44,    31,    65,    84,    14,    18,    69,    40,    44,
      13,    18,    16,    73,    23,    24,    25,    26,    78,    15,
      32,    24,    42,    15,    84,     0,    88,    89,    90,    21,
      19,    93,    35,    15,    54,    44,    45,    40,    47,    21,
      36,    37,    38,   105,    33,   107,   108,    36,    37,    38,
      46,   131,   132,   115,    31,    33,    51,    46,    36,    37,
      38,    44,    57,    36,    37,    38,   146,    33,    46,     4,
      34,   131,   132,    46,    44,   137,    38,    44,    16,    14,
      39,    18,    22,    18,    19,   147,   146,   149,    23,    24,
      25,    26,    27,    44,    29,    30,    17,    14,    14,    18,
      35,    36,    37,    38,     4,    40,    15,    18,    44,    44,
      45,    46,    47,    45,    14,    14,    14,    14,    18,    19,
       3,    22,    16,    23,    24,    25,    26,    27,    20,    29,
      30,    41,    14,    19,    15,    35,    36,    37,    38,     4,
      40,    20,    14,    28,    44,    45,    46,    47,    22,    14,
      14,    42,    22,    18,    19,    58,     7,    35,    23,    24,
      25,    26,    27,    -1,    29,    30,    54,    -1,    -1,    -1,
      35,    36,    37,    38,     4,    40,    -1,    -1,    -1,    44,
      45,    46,    47,    -1,    14,    -1,    -1,    -1,    18,    -1,
      -1,    -1,    -1,    23,    24,    25,    26,    27,    -1,    29,
      30,    36,    37,    38,    19,    35,    36,    37,    38,    44,
      40,    46,    -1,    -1,    44,    45,    46,    47,    33,    -1,
      -1,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    46,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    -1,    16,    -1,    -1,    -1,    20,    -1,
      22,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    -1,    16,    -1,    -1,    -1,    20,    -1,    22,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    15,    16,    -1,    -1,    -1,    20,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    -1,    15,    16,
      -1,    -1,    -1,    20,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    15,    16,    -1,    -1,    -1,
      20,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    15,    16,    -1,    -1,    -1,    20,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    -1,
      16,    17,    -1,    -1,    20,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    -1,    16,    17,    -1,
      -1,    20,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    -1,    16,    17,    -1,    -1,    20,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      15,    16,    -1,    -1,    -1,    20,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    -1,    16,    -1,
      -1,    -1,    20
  };

  const signed char
  parser::yystos_[] =
  {
       0,    31,    56,    58,    44,     0,    31,    57,    59,    18,
      44,    59,    33,    18,    32,    34,    33,    36,    37,    38,
      46,    53,    54,    55,    61,    62,    63,    67,    44,    38,
      53,    44,    16,    19,    62,    18,    39,    44,    22,    17,
      61,    14,    14,    64,    19,    15,    15,    53,    65,    66,
      18,    18,    44,    15,    21,     4,    14,    18,    23,    24,
      25,    26,    27,    29,    30,    35,    40,    44,    45,    47,
      49,    50,    52,    60,    67,    69,    70,    71,    60,    66,
      45,    44,    49,    71,    60,    44,    54,    68,    14,    14,
      14,    49,    20,    16,    49,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    16,    20,    51,     3,    19,
      69,    22,    19,    15,    19,    16,    14,    49,    49,    49,
      22,    41,    49,    49,    43,    44,    49,    49,    19,    49,
      15,    15,    15,    15,    20,    17,    17,    14,    22,    17,
      69,    69,    22,    42,    49,    72,    28,    14,    15,    21,
      69,    49,    49,    15,    22
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    48,    56,    56,    57,    57,    58,    59,    59,    60,
      60,    61,    61,    62,    62,    63,    64,    64,    65,    65,
      66,    67,    53,    53,    54,    54,    54,    54,    55,    68,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      70,    71,    52,    52,    72,    72,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    50,
      50,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     2,     1,     2,    13,     5,     7,     1,
       2,     1,     2,     1,     1,     7,     2,     3,     1,     3,
       2,     3,     1,     1,     1,     1,     1,     1,     3,     1,
       5,     1,     3,     5,     7,     5,     9,     4,     3,     2,
       1,     6,     1,     4,     1,     3,     3,     4,     3,     5,
       4,     2,     3,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"=\"", "\"-\"", "\"+\"",
  "\"*\"", "\"/\"", "\"&&\"", "\"||\"", "\"<\"", "\">\"", "\"==\"",
  "\"%\"", "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\".\"",
  "\",\"", "\";\"", "\"new\"", "\"this\"", "\"true\"", "\"false\"",
  "\"if\"", "\"else\"", "\"while\"", "\"assert\"", "\"class\"",
  "\"extends\"", "\"public\"", "\"static\"", "\"return\"", "\"int\"",
  "\"boolean\"", "\"void\"", "\"main\"", "\"System\"", "\"out\"",
  "\"println\"", "\"length\"", "\"identifier\"", "\"number\"",
  "\"type_identifier\"", "\"!\"", "$accept", "expr", "integer_literal",
  "binary_operator", "lvalue", "type", "simple_type", "array_type",
  "program", "class_declaration_list", "main_class", "class_declaration",
  "statement_list", "declaration_list", "declaration",
  "method_declaration", "args_list", "comma_formals_list", "formals",
  "variable_declaration", "type_identifier", "statement",
  "local_variable_declaration", "method_invocation", "comma_expr_list", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  parser::yyrline_[] =
  {
       0,   129,   129,   130,   132,   133,   135,   138,   139,   142,
     143,   145,   146,   148,   149,   151,   154,   155,   157,   158,
     160,   162,   166,   167,   169,   169,   169,   169,   171,   173,
     175,   176,   177,   178,   179,   180,   181,   183,   186,   187,
     189,   191,   193,   194,   196,   197,   199,   216,   219,   221,
     224,   227,   230,   232,   234,   237,   239,   242,   245,   247,
     248,   250,   250,   250,   250,   250,   251,   251,   251,   251,
     251
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 1518 "/compilers/compilers_course_4sem_2020/milestone2_ast_tree/src/parser.cpp"

#line 253 "parser.y"


void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
