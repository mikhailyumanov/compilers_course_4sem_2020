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
#line 25 "parser.y"

    #include "driver.hh"
    #include "location.hh"

    // include nodes
    #include "utils/elements.hpp"


    static yy::parser::symbol_type yylex(Scanner &scanner, Driver& driver) {
        return scanner.ScanToken();
    }

#line 58 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"


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
#line 149 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"


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
      case 50: // type
        value.YY_MOVE_OR_COPY< Type > (YY_MOVE (that.value));
        break;

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
      case 46: // "number"
      case 48: // integer_literal
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case 67: // formals
        value.YY_MOVE_OR_COPY< std::pair<Type, std::string> > (YY_MOVE (that.value));
        break;

      case 68: // comma_formals_list
      case 69: // args_list
        value.YY_MOVE_OR_COPY< std::pair<std::vector<Type>, std::vector<std::string>> > (YY_MOVE (that.value));
        break;

      case 57: // class_declaration
        value.YY_MOVE_OR_COPY< std::shared_ptr<ClassDecl> > (YY_MOVE (that.value));
        break;

      case 55: // class_declaration_list
        value.YY_MOVE_OR_COPY< std::shared_ptr<ClassDeclList> > (YY_MOVE (that.value));
        break;

      case 66: // comma_expr_list
        value.YY_MOVE_OR_COPY< std::shared_ptr<CommaExprList> > (YY_MOVE (that.value));
        break;

      case 60: // declaration
        value.YY_MOVE_OR_COPY< std::shared_ptr<Decl> > (YY_MOVE (that.value));
        break;

      case 59: // declaration_list
        value.YY_MOVE_OR_COPY< std::shared_ptr<DeclList> > (YY_MOVE (that.value));
        break;

      case 64: // expr
        value.YY_MOVE_OR_COPY< std::shared_ptr<Expression> > (YY_MOVE (that.value));
        break;

      case 49: // lvalue
        value.YY_MOVE_OR_COPY< std::shared_ptr<Lvalue> > (YY_MOVE (that.value));
        break;

      case 56: // main_class
        value.YY_MOVE_OR_COPY< std::shared_ptr<MainClass> > (YY_MOVE (that.value));
        break;

      case 70: // method_declaration
        value.YY_MOVE_OR_COPY< std::shared_ptr<MethodDecl> > (YY_MOVE (that.value));
        break;

      case 65: // method_invocation
        value.YY_MOVE_OR_COPY< std::shared_ptr<MethodInvocation> > (YY_MOVE (that.value));
        break;

      case 54: // program
        value.YY_MOVE_OR_COPY< std::shared_ptr<Program> > (YY_MOVE (that.value));
        break;

      case 62: // statement
        value.YY_MOVE_OR_COPY< std::shared_ptr<Statement> > (YY_MOVE (that.value));
        break;

      case 58: // statement_list
        value.YY_MOVE_OR_COPY< std::shared_ptr<StmtList> > (YY_MOVE (that.value));
        break;

      case 61: // variable_declaration
      case 63: // local_variable_declaration
        value.YY_MOVE_OR_COPY< std::shared_ptr<VarDecl> > (YY_MOVE (that.value));
        break;

      case 45: // "identifier"
      case 51: // type_identifier
      case 52: // simple_type
      case 53: // array_type
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
      case 50: // type
        value.move< Type > (YY_MOVE (that.value));
        break;

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
      case 46: // "number"
      case 48: // integer_literal
        value.move< int > (YY_MOVE (that.value));
        break;

      case 67: // formals
        value.move< std::pair<Type, std::string> > (YY_MOVE (that.value));
        break;

      case 68: // comma_formals_list
      case 69: // args_list
        value.move< std::pair<std::vector<Type>, std::vector<std::string>> > (YY_MOVE (that.value));
        break;

      case 57: // class_declaration
        value.move< std::shared_ptr<ClassDecl> > (YY_MOVE (that.value));
        break;

      case 55: // class_declaration_list
        value.move< std::shared_ptr<ClassDeclList> > (YY_MOVE (that.value));
        break;

      case 66: // comma_expr_list
        value.move< std::shared_ptr<CommaExprList> > (YY_MOVE (that.value));
        break;

      case 60: // declaration
        value.move< std::shared_ptr<Decl> > (YY_MOVE (that.value));
        break;

      case 59: // declaration_list
        value.move< std::shared_ptr<DeclList> > (YY_MOVE (that.value));
        break;

      case 64: // expr
        value.move< std::shared_ptr<Expression> > (YY_MOVE (that.value));
        break;

      case 49: // lvalue
        value.move< std::shared_ptr<Lvalue> > (YY_MOVE (that.value));
        break;

      case 56: // main_class
        value.move< std::shared_ptr<MainClass> > (YY_MOVE (that.value));
        break;

      case 70: // method_declaration
        value.move< std::shared_ptr<MethodDecl> > (YY_MOVE (that.value));
        break;

      case 65: // method_invocation
        value.move< std::shared_ptr<MethodInvocation> > (YY_MOVE (that.value));
        break;

      case 54: // program
        value.move< std::shared_ptr<Program> > (YY_MOVE (that.value));
        break;

      case 62: // statement
        value.move< std::shared_ptr<Statement> > (YY_MOVE (that.value));
        break;

      case 58: // statement_list
        value.move< std::shared_ptr<StmtList> > (YY_MOVE (that.value));
        break;

      case 61: // variable_declaration
      case 63: // local_variable_declaration
        value.move< std::shared_ptr<VarDecl> > (YY_MOVE (that.value));
        break;

      case 45: // "identifier"
      case 51: // type_identifier
      case 52: // simple_type
      case 53: // array_type
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
      case 50: // type
        value.copy< Type > (that.value);
        break;

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
      case 46: // "number"
      case 48: // integer_literal
        value.copy< int > (that.value);
        break;

      case 67: // formals
        value.copy< std::pair<Type, std::string> > (that.value);
        break;

      case 68: // comma_formals_list
      case 69: // args_list
        value.copy< std::pair<std::vector<Type>, std::vector<std::string>> > (that.value);
        break;

      case 57: // class_declaration
        value.copy< std::shared_ptr<ClassDecl> > (that.value);
        break;

      case 55: // class_declaration_list
        value.copy< std::shared_ptr<ClassDeclList> > (that.value);
        break;

      case 66: // comma_expr_list
        value.copy< std::shared_ptr<CommaExprList> > (that.value);
        break;

      case 60: // declaration
        value.copy< std::shared_ptr<Decl> > (that.value);
        break;

      case 59: // declaration_list
        value.copy< std::shared_ptr<DeclList> > (that.value);
        break;

      case 64: // expr
        value.copy< std::shared_ptr<Expression> > (that.value);
        break;

      case 49: // lvalue
        value.copy< std::shared_ptr<Lvalue> > (that.value);
        break;

      case 56: // main_class
        value.copy< std::shared_ptr<MainClass> > (that.value);
        break;

      case 70: // method_declaration
        value.copy< std::shared_ptr<MethodDecl> > (that.value);
        break;

      case 65: // method_invocation
        value.copy< std::shared_ptr<MethodInvocation> > (that.value);
        break;

      case 54: // program
        value.copy< std::shared_ptr<Program> > (that.value);
        break;

      case 62: // statement
        value.copy< std::shared_ptr<Statement> > (that.value);
        break;

      case 58: // statement_list
        value.copy< std::shared_ptr<StmtList> > (that.value);
        break;

      case 61: // variable_declaration
      case 63: // local_variable_declaration
        value.copy< std::shared_ptr<VarDecl> > (that.value);
        break;

      case 45: // "identifier"
      case 51: // type_identifier
      case 52: // simple_type
      case 53: // array_type
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
      case 50: // type
        value.move< Type > (that.value);
        break;

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
      case 46: // "number"
      case 48: // integer_literal
        value.move< int > (that.value);
        break;

      case 67: // formals
        value.move< std::pair<Type, std::string> > (that.value);
        break;

      case 68: // comma_formals_list
      case 69: // args_list
        value.move< std::pair<std::vector<Type>, std::vector<std::string>> > (that.value);
        break;

      case 57: // class_declaration
        value.move< std::shared_ptr<ClassDecl> > (that.value);
        break;

      case 55: // class_declaration_list
        value.move< std::shared_ptr<ClassDeclList> > (that.value);
        break;

      case 66: // comma_expr_list
        value.move< std::shared_ptr<CommaExprList> > (that.value);
        break;

      case 60: // declaration
        value.move< std::shared_ptr<Decl> > (that.value);
        break;

      case 59: // declaration_list
        value.move< std::shared_ptr<DeclList> > (that.value);
        break;

      case 64: // expr
        value.move< std::shared_ptr<Expression> > (that.value);
        break;

      case 49: // lvalue
        value.move< std::shared_ptr<Lvalue> > (that.value);
        break;

      case 56: // main_class
        value.move< std::shared_ptr<MainClass> > (that.value);
        break;

      case 70: // method_declaration
        value.move< std::shared_ptr<MethodDecl> > (that.value);
        break;

      case 65: // method_invocation
        value.move< std::shared_ptr<MethodInvocation> > (that.value);
        break;

      case 54: // program
        value.move< std::shared_ptr<Program> > (that.value);
        break;

      case 62: // statement
        value.move< std::shared_ptr<Statement> > (that.value);
        break;

      case 58: // statement_list
        value.move< std::shared_ptr<StmtList> > (that.value);
        break;

      case 61: // variable_declaration
      case 63: // local_variable_declaration
        value.move< std::shared_ptr<VarDecl> > (that.value);
        break;

      case 45: // "identifier"
      case 51: // type_identifier
      case 52: // simple_type
      case 53: // array_type
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
      case 50: // type
        yylhs.value.emplace< Type > ();
        break;

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
      case 46: // "number"
      case 48: // integer_literal
        yylhs.value.emplace< int > ();
        break;

      case 67: // formals
        yylhs.value.emplace< std::pair<Type, std::string> > ();
        break;

      case 68: // comma_formals_list
      case 69: // args_list
        yylhs.value.emplace< std::pair<std::vector<Type>, std::vector<std::string>> > ();
        break;

      case 57: // class_declaration
        yylhs.value.emplace< std::shared_ptr<ClassDecl> > ();
        break;

      case 55: // class_declaration_list
        yylhs.value.emplace< std::shared_ptr<ClassDeclList> > ();
        break;

      case 66: // comma_expr_list
        yylhs.value.emplace< std::shared_ptr<CommaExprList> > ();
        break;

      case 60: // declaration
        yylhs.value.emplace< std::shared_ptr<Decl> > ();
        break;

      case 59: // declaration_list
        yylhs.value.emplace< std::shared_ptr<DeclList> > ();
        break;

      case 64: // expr
        yylhs.value.emplace< std::shared_ptr<Expression> > ();
        break;

      case 49: // lvalue
        yylhs.value.emplace< std::shared_ptr<Lvalue> > ();
        break;

      case 56: // main_class
        yylhs.value.emplace< std::shared_ptr<MainClass> > ();
        break;

      case 70: // method_declaration
        yylhs.value.emplace< std::shared_ptr<MethodDecl> > ();
        break;

      case 65: // method_invocation
        yylhs.value.emplace< std::shared_ptr<MethodInvocation> > ();
        break;

      case 54: // program
        yylhs.value.emplace< std::shared_ptr<Program> > ();
        break;

      case 62: // statement
        yylhs.value.emplace< std::shared_ptr<Statement> > ();
        break;

      case 58: // statement_list
        yylhs.value.emplace< std::shared_ptr<StmtList> > ();
        break;

      case 61: // variable_declaration
      case 63: // local_variable_declaration
        yylhs.value.emplace< std::shared_ptr<VarDecl> > ();
        break;

      case 45: // "identifier"
      case 51: // type_identifier
      case 52: // simple_type
      case 53: // array_type
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
  case 2:
#line 142 "parser.y"
         { yylhs.value.as < std::shared_ptr<Program> > () = std::make_shared<Program>(yystack_[0].value.as < std::shared_ptr<MainClass> > ()); driver.program = yylhs.value.as < std::shared_ptr<Program> > (); }
#line 1037 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 3:
#line 144 "parser.y"
         { yylhs.value.as < std::shared_ptr<Program> > () = std::make_shared<Program>(yystack_[1].value.as < std::shared_ptr<MainClass> > (), yystack_[0].value.as < std::shared_ptr<ClassDeclList> > ()); driver.program = yylhs.value.as < std::shared_ptr<Program> > (); }
#line 1043 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 4:
#line 148 "parser.y"
                        { yylhs.value.as < std::shared_ptr<ClassDeclList> > () = std::make_shared<ClassDeclList>();
                          yylhs.value.as < std::shared_ptr<ClassDeclList> > ()->AddItem(yystack_[0].value.as < std::shared_ptr<ClassDecl> > ()); }
#line 1050 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 5:
#line 151 "parser.y"
                        { yylhs.value.as < std::shared_ptr<ClassDeclList> > () = yystack_[1].value.as < std::shared_ptr<ClassDeclList> > (); yylhs.value.as < std::shared_ptr<ClassDeclList> > ()->AddItem(yystack_[0].value.as < std::shared_ptr<ClassDecl> > ()); }
#line 1056 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 6:
#line 156 "parser.y"
            { yylhs.value.as < std::shared_ptr<MainClass> > () = std::make_shared<MainClass>(yystack_[2].value.as < std::shared_ptr<StmtList> > ()); }
#line 1062 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 7:
#line 160 "parser.y"
                   { yylhs.value.as < std::shared_ptr<ClassDecl> > () = std::make_shared<ClassDecl>(yystack_[3].value.as < std::string > (), yystack_[1].value.as < std::shared_ptr<DeclList> > ()); }
#line 1068 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 8:
#line 163 "parser.y"
                   { yylhs.value.as < std::shared_ptr<ClassDecl> > () = std::make_shared<ClassDecl>(yystack_[5].value.as < std::string > (), yystack_[1].value.as < std::shared_ptr<DeclList> > ()); }
#line 1074 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 9:
#line 167 "parser.y"
                { yylhs.value.as < std::shared_ptr<StmtList> > () = std::make_shared<StmtList>(); yylhs.value.as < std::shared_ptr<StmtList> > ()->AddItem(yystack_[0].value.as < std::shared_ptr<Statement> > ()); }
#line 1080 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 10:
#line 169 "parser.y"
                { yylhs.value.as < std::shared_ptr<StmtList> > () = yystack_[1].value.as < std::shared_ptr<StmtList> > (); yylhs.value.as < std::shared_ptr<StmtList> > ()->AddItem(yystack_[0].value.as < std::shared_ptr<Statement> > ()); }
#line 1086 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 11:
#line 173 "parser.y"
                   { yylhs.value.as < std::shared_ptr<DeclList> > () = std::make_shared<DeclList>(); yylhs.value.as < std::shared_ptr<DeclList> > ()->AddItem(yystack_[0].value.as < std::shared_ptr<Decl> > ()); }
#line 1092 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 12:
#line 175 "parser.y"
                   { yylhs.value.as < std::shared_ptr<DeclList> > () = yystack_[1].value.as < std::shared_ptr<DeclList> > (); yylhs.value.as < std::shared_ptr<DeclList> > ()->AddItem(yystack_[0].value.as < std::shared_ptr<Decl> > ()); }
#line 1098 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 13:
#line 179 "parser.y"
             { yylhs.value.as < std::shared_ptr<Decl> > () = yystack_[0].value.as < std::shared_ptr<VarDecl> > (); }
#line 1104 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 14:
#line 181 "parser.y"
             { yylhs.value.as < std::shared_ptr<Decl> > () = yystack_[0].value.as < std::shared_ptr<MethodDecl> > (); }
#line 1110 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 15:
#line 185 "parser.y"
                    { yylhs.value.as < std::shared_ptr<MethodDecl> > () = std::make_shared<MethodDecl>(
                          FunctionType(yystack_[5].value.as < Type > (), yystack_[3].value.as < std::pair<std::vector<Type>, std::vector<std::string>> > ().first,yystack_[3].value.as < std::pair<std::vector<Type>, std::vector<std::string>> > ().second), yystack_[4].value.as < std::string > (), yystack_[1].value.as < std::shared_ptr<StmtList> > ()); }
#line 1117 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 16:
#line 189 "parser.y"
                   { yylhs.value.as < std::pair<std::vector<Type>, std::vector<std::string>> > () = std::pair<std::vector<Type>,
                                    std::vector<std::string>>(); }
#line 1124 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 17:
#line 191 "parser.y"
                                      { yylhs.value.as < std::pair<std::vector<Type>, std::vector<std::string>> > () = yystack_[1].value.as < std::pair<std::vector<Type>, std::vector<std::string>> > (); }
#line 1130 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 18:
#line 195 "parser.y"
                    { yylhs.value.as < std::pair<std::vector<Type>, std::vector<std::string>> > () = std::pair<std::vector<Type>,
                                     std::vector<std::string>>();
                      yylhs.value.as < std::pair<std::vector<Type>, std::vector<std::string>> > ().first.push_back(yystack_[0].value.as < std::pair<Type, std::string> > ().first);
                      yylhs.value.as < std::pair<std::vector<Type>, std::vector<std::string>> > ().second.push_back(yystack_[0].value.as < std::pair<Type, std::string> > ().second); }
#line 1139 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 19:
#line 200 "parser.y"
                    { yylhs.value.as < std::pair<std::vector<Type>, std::vector<std::string>> > () = yystack_[2].value.as < std::pair<std::vector<Type>, std::vector<std::string>> > (); yylhs.value.as < std::pair<std::vector<Type>, std::vector<std::string>> > ().first.push_back(yystack_[0].value.as < std::pair<Type, std::string> > ().first);
                      yylhs.value.as < std::pair<std::vector<Type>, std::vector<std::string>> > ().second.push_back(yystack_[0].value.as < std::pair<Type, std::string> > ().second); }
#line 1146 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 20:
#line 204 "parser.y"
                           { yylhs.value.as < std::pair<Type, std::string> > () = std::make_pair(yystack_[1].value.as < Type > (), yystack_[0].value.as < std::string > ()); }
#line 1152 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 21:
#line 208 "parser.y"
                      { yylhs.value.as < std::shared_ptr<VarDecl> > () = std::make_shared<VarDecl>(yystack_[2].value.as < Type > (), yystack_[1].value.as < std::string > ()); }
#line 1158 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 22:
#line 211 "parser.y"
                  { yylhs.value.as < Type > () = Type{yystack_[0].value.as < std::string > (), false}; }
#line 1164 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 23:
#line 212 "parser.y"
                  { yylhs.value.as < Type > () = Type{yystack_[0].value.as < std::string > (), true};  }
#line 1170 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 24:
#line 215 "parser.y"
                                { yylhs.value.as < std::string > () = yystack_[2].value.as < std::string > (); }
#line 1176 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 25:
#line 218 "parser.y"
                   { yylhs.value.as < std::string > () = "int"; }
#line 1182 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 26:
#line 219 "parser.y"
                       {yylhs.value.as < std::string > () = "boolean"; }
#line 1188 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 27:
#line 220 "parser.y"
                    { yylhs.value.as < std::string > () = "void"; }
#line 1194 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 28:
#line 221 "parser.y"
                             { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); }
#line 1200 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 29:
#line 224 "parser.y"
                              { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); }
#line 1206 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 30:
#line 228 "parser.y"
           { yylhs.value.as < std::shared_ptr<Statement> > () = std::static_pointer_cast<Statement>(
              std::make_shared<AssertStmt>(yystack_[2].value.as < std::shared_ptr<Expression> > ())); }
#line 1213 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 31:
#line 231 "parser.y"
           { yylhs.value.as < std::shared_ptr<Statement> > () = std::make_shared<StmtListStmt>(yystack_[1].value.as < std::shared_ptr<StmtList> > ()); }
#line 1219 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 32:
#line 233 "parser.y"
           { yylhs.value.as < std::shared_ptr<Statement> > () = std::make_shared<IfStmt>(yystack_[2].value.as < std::shared_ptr<Expression> > (), yystack_[0].value.as < std::shared_ptr<Statement> > ()); }
#line 1225 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 33:
#line 235 "parser.y"
           { yylhs.value.as < std::shared_ptr<Statement> > () = std::make_shared<IfElseStmt>(yystack_[4].value.as < std::shared_ptr<Expression> > (), yystack_[2].value.as < std::shared_ptr<Statement> > (), yystack_[0].value.as < std::shared_ptr<Statement> > ()); }
#line 1231 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 34:
#line 237 "parser.y"
           { yylhs.value.as < std::shared_ptr<Statement> > () = std::make_shared<WhileStmt>(yystack_[2].value.as < std::shared_ptr<Expression> > (), yystack_[0].value.as < std::shared_ptr<Statement> > ()); }
#line 1237 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 35:
#line 239 "parser.y"
           { yylhs.value.as < std::shared_ptr<Statement> > () = std::make_shared<PrintStmt>(yystack_[2].value.as < std::shared_ptr<Expression> > ()); }
#line 1243 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 36:
#line 241 "parser.y"
           { yylhs.value.as < std::shared_ptr<Statement> > () = std::make_shared<AssignmentStmt>(yystack_[3].value.as < std::shared_ptr<Lvalue> > (), yystack_[1].value.as < std::shared_ptr<Expression> > ()); }
#line 1249 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 37:
#line 243 "parser.y"
           { yylhs.value.as < std::shared_ptr<Statement> > () = std::make_shared<LocalVarDeclStmt>(yystack_[0].value.as < std::shared_ptr<VarDecl> > ()); }
#line 1255 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 38:
#line 248 "parser.y"
           { yylhs.value.as < std::shared_ptr<Statement> > () = std::make_shared<LocalVarDeclStmt>(
                 std::make_shared<VarDecl>(Type{yystack_[4].value.as < std::string > (), true}, yystack_[1].value.as < std::string > ())); }
#line 1262 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 39:
#line 252 "parser.y"
           { yylhs.value.as < std::shared_ptr<Statement> > () = std::make_shared<ReturnStmt>(yystack_[1].value.as < std::shared_ptr<Expression> > ()); }
#line 1268 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 40:
#line 254 "parser.y"
           { yylhs.value.as < std::shared_ptr<Statement> > () = std::make_shared<MethodStmt>(yystack_[1].value.as < std::shared_ptr<MethodInvocation> > ()); }
#line 1274 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 41:
#line 258 "parser.y"
                            { yylhs.value.as < std::shared_ptr<VarDecl> > () = yystack_[0].value.as < std::shared_ptr<VarDecl> > (); }
#line 1280 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 42:
#line 262 "parser.y"
        { yylhs.value.as < std::shared_ptr<MethodInvocation> > () = std::make_shared<MethodInvocation>(yystack_[5].value.as < std::shared_ptr<Expression> > (), Symbol(yystack_[3].value.as < std::string > ()), yystack_[1].value.as < std::shared_ptr<CommaExprList> > ()); }
#line 1286 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 43:
#line 264 "parser.y"
        { yylhs.value.as < std::shared_ptr<MethodInvocation> > () = std::make_shared<MethodInvocation>(yystack_[4].value.as < std::shared_ptr<Expression> > (), Symbol(yystack_[2].value.as < std::string > ()), 
              std::make_shared<CommaExprList>()); }
#line 1293 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 44:
#line 269 "parser.y"
        { yylhs.value.as < std::shared_ptr<Lvalue> > () = std::make_shared<Lvalue>(yystack_[0].value.as < std::string > ()); }
#line 1299 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 45:
#line 271 "parser.y"
        { yylhs.value.as < std::shared_ptr<Lvalue> > () = std::make_shared<Lvalue>(yystack_[3].value.as < std::string > (), yystack_[1].value.as < std::shared_ptr<Expression> > ()); }
#line 1305 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 46:
#line 274 "parser.y"
                      { yylhs.value.as < std::shared_ptr<CommaExprList> > () = std::make_shared<CommaExprList>(); yylhs.value.as < std::shared_ptr<CommaExprList> > ()->AddItem(yystack_[0].value.as < std::shared_ptr<Expression> > ()); }
#line 1311 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 47:
#line 275 "parser.y"
                                          { yylhs.value.as < std::shared_ptr<CommaExprList> > () = yystack_[2].value.as < std::shared_ptr<CommaExprList> > (); yylhs.value.as < std::shared_ptr<CommaExprList> > ()->AddItem(yystack_[0].value.as < std::shared_ptr<Expression> > ()); }
#line 1317 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 48:
#line 286 "parser.y"
  {yylhs.value.as < std::shared_ptr<Expression> > () = std::make_shared<BinOpExpr>(yystack_[2].value.as < std::shared_ptr<Expression> > (), BinOpExpr::Operation::OP_AND     , yystack_[0].value.as < std::shared_ptr<Expression> > ());}
#line 1323 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 49:
#line 288 "parser.y"
  {yylhs.value.as < std::shared_ptr<Expression> > () = std::make_shared<BinOpExpr>(yystack_[2].value.as < std::shared_ptr<Expression> > (), BinOpExpr::Operation::OP_OR      , yystack_[0].value.as < std::shared_ptr<Expression> > ());}
#line 1329 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 50:
#line 290 "parser.y"
  {yylhs.value.as < std::shared_ptr<Expression> > () = std::make_shared<BinOpExpr>(yystack_[2].value.as < std::shared_ptr<Expression> > (), BinOpExpr::Operation::OP_LESS    , yystack_[0].value.as < std::shared_ptr<Expression> > ());}
#line 1335 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 51:
#line 292 "parser.y"
  {yylhs.value.as < std::shared_ptr<Expression> > () = std::make_shared<BinOpExpr>(yystack_[2].value.as < std::shared_ptr<Expression> > (), BinOpExpr::Operation::OP_GREATER , yystack_[0].value.as < std::shared_ptr<Expression> > ());}
#line 1341 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 52:
#line 294 "parser.y"
  {yylhs.value.as < std::shared_ptr<Expression> > () = std::make_shared<BinOpExpr>(yystack_[2].value.as < std::shared_ptr<Expression> > (), BinOpExpr::Operation::OP_EQUAL   , yystack_[0].value.as < std::shared_ptr<Expression> > ());}
#line 1347 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 53:
#line 296 "parser.y"
  {yylhs.value.as < std::shared_ptr<Expression> > () = std::make_shared<BinOpExpr>(yystack_[2].value.as < std::shared_ptr<Expression> > (), BinOpExpr::Operation::OP_PLUS    , yystack_[0].value.as < std::shared_ptr<Expression> > ());}
#line 1353 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 54:
#line 298 "parser.y"
  {yylhs.value.as < std::shared_ptr<Expression> > () = std::make_shared<BinOpExpr>(yystack_[2].value.as < std::shared_ptr<Expression> > (), BinOpExpr::Operation::OP_MINUS   , yystack_[0].value.as < std::shared_ptr<Expression> > ());}
#line 1359 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 55:
#line 300 "parser.y"
  {yylhs.value.as < std::shared_ptr<Expression> > () = std::make_shared<BinOpExpr>(yystack_[2].value.as < std::shared_ptr<Expression> > (), BinOpExpr::Operation::OP_STAR    , yystack_[0].value.as < std::shared_ptr<Expression> > ());}
#line 1365 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 56:
#line 302 "parser.y"
  {yylhs.value.as < std::shared_ptr<Expression> > () = std::make_shared<BinOpExpr>(yystack_[2].value.as < std::shared_ptr<Expression> > (), BinOpExpr::Operation::OP_SLASH   , yystack_[0].value.as < std::shared_ptr<Expression> > ());}
#line 1371 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 57:
#line 304 "parser.y"
  {yylhs.value.as < std::shared_ptr<Expression> > () = std::make_shared<BinOpExpr>(yystack_[2].value.as < std::shared_ptr<Expression> > (), BinOpExpr::Operation::OP_RMNDR   , yystack_[0].value.as < std::shared_ptr<Expression> > ());}
#line 1377 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 58:
#line 307 "parser.y"
      { yylhs.value.as < std::shared_ptr<Expression> > () = std::make_shared<SubscriptExpr>(yystack_[3].value.as < std::shared_ptr<Expression> > (), yystack_[1].value.as < std::shared_ptr<Expression> > ()); }
#line 1383 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 59:
#line 310 "parser.y"
      { yylhs.value.as < std::shared_ptr<Expression> > () = std::make_shared<LengthExpr>(yystack_[2].value.as < std::shared_ptr<Expression> > ()); }
#line 1389 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 60:
#line 313 "parser.y"
      { yylhs.value.as < std::shared_ptr<Expression> > () = std::make_shared<NewArrayExpr>(yystack_[3].value.as < std::string > (), yystack_[1].value.as < std::shared_ptr<Expression> > ()); }
#line 1395 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 61:
#line 316 "parser.y"
      { yylhs.value.as < std::shared_ptr<Expression> > () = std::make_shared<NewExpr>(yystack_[2].value.as < std::string > ()); }
#line 1401 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 62:
#line 319 "parser.y"
      { yylhs.value.as < std::shared_ptr<Expression> > () = yystack_[1].value.as < std::shared_ptr<Expression> > (); }
#line 1407 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 63:
#line 322 "parser.y"
      { yylhs.value.as < std::shared_ptr<Expression> > () = std::make_shared<IdentExpr>(yystack_[0].value.as < std::string > ()); }
#line 1413 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 64:
#line 325 "parser.y"
      { yylhs.value.as < std::shared_ptr<Expression> > () = std::make_shared<IntExpr>(yystack_[0].value.as < int > ()); }
#line 1419 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 65:
#line 327 "parser.y"
                                     { /* TODO */ }
#line 1425 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 66:
#line 330 "parser.y"
      { yylhs.value.as < std::shared_ptr<Expression> > () = std::make_shared<TrueExpr>(); }
#line 1431 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 67:
#line 333 "parser.y"
      { yylhs.value.as < std::shared_ptr<Expression> > () = std::make_shared<FalseExpr>(); }
#line 1437 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 68:
#line 336 "parser.y"
      { yylhs.value.as < std::shared_ptr<Expression> > () = std::make_shared<MethodExpr>(yystack_[0].value.as < std::shared_ptr<MethodInvocation> > ()); }
#line 1443 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 69:
#line 339 "parser.y"
      { yylhs.value.as < std::shared_ptr<Expression> > () = std::make_shared<NotExpr>(yystack_[0].value.as < std::shared_ptr<Expression> > ()); }
#line 1449 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 70:
#line 342 "parser.y"
                          { yylhs.value.as < int > () = yystack_[0].value.as < int > (); }
#line 1455 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;

  case 71:
#line 343 "parser.y"
                              { yylhs.value.as < int > () = -yystack_[0].value.as < int > (); }
#line 1461 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"
    break;


#line 1465 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"

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

  const signed char parser::yytable_ninf_ = -45;

  const short
  parser::yypact_[] =
  {
     -11,   -38,    18,    -2,    13,   -71,    -5,    -2,   -71,     9,
     -13,   -71,    29,   431,    21,    28,   -26,   -71,   -71,   -71,
     -71,    31,   -71,    56,   -71,   212,   -71,   -71,   -71,    55,
      37,    38,    59,    66,   -71,   -71,   431,    70,    72,   -71,
     -71,   224,    76,   -14,    77,   -71,    79,   -71,    57,   -71,
      17,   174,   174,   -71,   -71,   -26,    65,   210,   210,   174,
     -26,   -71,   -71,   -71,    88,    97,    98,   210,   102,    12,
     -71,   -71,   116,    90,   -71,   -71,   -71,   450,   101,   118,
     -71,   -71,   -71,   486,   -71,   306,   146,   110,   113,   210,
     210,   210,   266,    92,    54,   210,   -71,   -71,   210,   210,
     210,   210,   210,   210,   210,   210,   210,   210,   210,    16,
     -71,   119,   -71,   -71,   124,   210,   324,   342,   360,   -71,
     120,   106,   378,   286,   173,   173,    80,    80,   468,   468,
     504,   504,   486,   450,   396,   -71,   132,   -71,   -71,   414,
     174,   174,   129,   115,   130,   -71,   -71,   -71,   202,   -71,
     133,   -71,   -71,   152,   -71,   -71,   450,    43,   174,   210,
     -71,   210,   -71,   432,   450,   145,   -71
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,     0,     2,     0,     1,     0,     3,     4,     0,
       0,     5,     0,     0,     0,     0,     0,    25,    26,    27,
      29,     0,    28,    22,    23,     0,    11,    13,    14,     0,
       0,     0,     0,     0,     7,    12,     0,     0,     0,    21,
      24,     0,     0,     0,     0,     8,     0,    16,     0,    18,
       0,     0,     0,    20,    17,     0,     0,     0,     0,     0,
       0,    65,    66,    67,     0,     0,     0,     0,     0,    63,
      70,    64,     0,     0,    41,     9,    37,     0,    68,     0,
      19,    71,    63,    69,    68,     0,     0,    28,     0,     0,
       0,     0,     0,     0,     0,     0,    15,    10,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      40,     0,    62,    31,     0,     0,     0,     0,     0,    39,
       0,     0,     0,     0,    54,    53,    55,    56,    48,    49,
      50,    51,    52,    57,     0,    59,     0,     6,    61,     0,
       0,     0,     0,     0,     0,    45,    36,    58,     0,    60,
      32,    34,    30,     0,    38,    43,    46,     0,     0,     0,
      42,     0,    33,     0,    47,     0,    35
  };

  const short
  parser::yypgoto_[] =
  {
     -71,   -71,   -71,     1,   109,   121,   -71,   -71,   -71,   -71,
     168,   -25,   159,   -15,    50,   -70,   -71,   -53,   -51,   -71,
     141,   -71,   -71,   -71
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,    71,    72,    21,    22,    23,    24,     2,     7,     3,
       8,    73,    25,    26,    74,    75,    76,    77,    84,   157,
      49,    50,    44,    28
  };

  const short
  parser::yytable_[] =
  {
      78,    78,    47,    97,    83,    85,    13,     4,    78,    97,
      35,    17,    18,    19,    92,   -44,    97,    31,     5,    20,
      14,     1,    78,    17,    18,    19,    35,    79,    78,    94,
       6,    20,     9,    54,    86,    78,   116,   117,   118,    55,
      10,   122,   123,    12,    48,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,    48,   -29,    56,   160,
     135,   136,   139,    27,    15,   161,    29,    30,    57,    58,
     150,   151,   121,    33,    36,    27,    32,    37,    60,    61,
      62,    63,    39,    38,    40,    42,    27,    43,   162,    78,
      78,    27,    46,   107,    56,   156,    51,   108,    52,    82,
      70,   109,    53,    89,    57,    58,   163,    78,   164,    59,
      96,    81,    90,    91,    60,    61,    62,    63,    64,    95,
      65,    66,    56,    93,   110,   114,    67,    17,    18,    19,
     115,    68,    57,    58,   120,    69,    70,    59,   111,   137,
     138,   143,    60,    61,    62,    63,    64,   148,    65,    66,
      56,   144,   152,   154,    67,    17,    18,    19,   153,    68,
      57,    58,   158,    69,    70,    59,   113,   159,   166,    87,
      60,    61,    62,    63,    64,    11,    65,    66,    56,   100,
     101,    88,    67,    17,    18,    19,   107,    68,    57,    58,
     108,    69,    70,    59,   109,    41,    80,     0,    60,    61,
      62,    63,    64,     0,    65,    66,    56,     0,     0,     0,
      67,    17,    18,    19,    56,    68,    57,    58,   155,    69,
      70,     0,     0,     0,    57,    58,    60,    61,    62,    63,
       0,     0,    34,     0,    60,    61,    62,    63,     0,     0,
       0,     0,     0,     0,    45,     0,    16,    82,    70,    17,
      18,    19,     0,     0,     0,    82,    70,    20,    16,     0,
       0,    17,    18,    19,     0,     0,     0,     0,     0,    20,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
       0,     0,     0,   108,     0,     0,     0,   109,     0,   119,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
       0,     0,     0,   108,     0,     0,     0,   109,     0,   146,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
       0,     0,   112,   108,     0,     0,     0,   109,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,     0,     0,
     140,   108,     0,     0,     0,   109,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,     0,     0,   141,   108,
       0,     0,     0,   109,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,     0,     0,   142,   108,     0,     0,
       0,   109,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,     0,     0,     0,   108,   145,     0,     0,   109,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
       0,     0,     0,   108,   147,     0,     0,   109,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,     0,     0,
       0,   108,   149,     0,     0,   109,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,     0,     0,   165,   108,
       0,     0,     0,   109,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,     0,    16,     0,   108,    17,    18,
      19,   109,    98,    99,   100,   101,    20,     0,   104,   105,
     106,   107,     0,     0,     0,   108,     0,     0,     0,   109,
      98,    99,   100,   101,     0,     0,   104,   105,     0,   107,
       0,     0,     0,   108,     0,     0,     0,   109,    98,    99,
     100,   101,     0,     0,     0,     0,     0,   107,     0,     0,
       0,   108,     0,     0,     0,   109
  };

  const short
  parser::yycheck_[] =
  {
      51,    52,    16,    73,    57,    58,    19,    45,    59,    79,
      25,    37,    38,    39,    67,     3,    86,    16,     0,    45,
      33,    32,    73,    37,    38,    39,    41,    52,    79,    17,
      32,    45,    19,    16,    59,    86,    89,    90,    91,    22,
      45,    94,    95,    34,    43,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,    55,    45,     4,    16,
      44,    45,   115,    13,    35,    22,    45,    39,    14,    15,
     140,   141,    18,    17,    19,    25,    45,    40,    24,    25,
      26,    27,    23,    45,    18,    15,    36,    15,   158,   140,
     141,    41,    16,    13,     4,   148,    19,    17,    19,    45,
      46,    21,    45,    15,    14,    15,   159,   158,   161,    19,
      20,    46,    15,    15,    24,    25,    26,    27,    28,     3,
      30,    31,     4,    21,    23,    15,    36,    37,    38,    39,
      17,    41,    14,    15,    42,    45,    46,    19,    20,    20,
      16,    21,    24,    25,    26,    27,    28,    15,    30,    31,
       4,    45,    23,    23,    36,    37,    38,    39,    43,    41,
      14,    15,    29,    45,    46,    19,    20,    15,    23,    60,
      24,    25,    26,    27,    28,     7,    30,    31,     4,     6,
       7,    60,    36,    37,    38,    39,    13,    41,    14,    15,
      17,    45,    46,    19,    21,    36,    55,    -1,    24,    25,
      26,    27,    28,    -1,    30,    31,     4,    -1,    -1,    -1,
      36,    37,    38,    39,     4,    41,    14,    15,    16,    45,
      46,    -1,    -1,    -1,    14,    15,    24,    25,    26,    27,
      -1,    -1,    20,    -1,    24,    25,    26,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    20,    -1,    34,    45,    46,    37,
      38,    39,    -1,    -1,    -1,    45,    46,    45,    34,    -1,
      -1,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,    45,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    -1,    -1,    17,    -1,    -1,    -1,    21,    -1,    23,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    -1,    -1,    17,    -1,    -1,    -1,    21,    -1,    23,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    -1,    16,    17,    -1,    -1,    -1,    21,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    -1,
      16,    17,    -1,    -1,    -1,    21,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    -1,    16,    17,
      -1,    -1,    -1,    21,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    -1,    16,    17,    -1,    -1,
      -1,    21,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    -1,    -1,    17,    18,    -1,    -1,    21,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    -1,    -1,    17,    18,    -1,    -1,    21,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    -1,
      -1,    17,    18,    -1,    -1,    21,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    -1,    16,    17,
      -1,    -1,    -1,    21,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    34,    -1,    17,    37,    38,
      39,    21,     4,     5,     6,     7,    45,    -1,    10,    11,
      12,    13,    -1,    -1,    -1,    17,    -1,    -1,    -1,    21,
       4,     5,     6,     7,    -1,    -1,    10,    11,    -1,    13,
      -1,    -1,    -1,    17,    -1,    -1,    -1,    21,     4,     5,
       6,     7,    -1,    -1,    -1,    -1,    -1,    13,    -1,    -1,
      -1,    17,    -1,    -1,    -1,    21
  };

  const signed char
  parser::yystos_[] =
  {
       0,    32,    54,    56,    45,     0,    32,    55,    57,    19,
      45,    57,    34,    19,    33,    35,    34,    37,    38,    39,
      45,    50,    51,    52,    53,    59,    60,    61,    70,    45,
      39,    50,    45,    17,    20,    60,    19,    40,    45,    23,
      18,    59,    15,    15,    69,    20,    16,    16,    50,    67,
      68,    19,    19,    45,    16,    22,     4,    14,    15,    19,
      24,    25,    26,    27,    28,    30,    31,    36,    41,    45,
      46,    48,    49,    58,    61,    62,    63,    64,    65,    58,
      67,    46,    45,    64,    65,    64,    58,    51,    52,    15,
      15,    15,    64,    21,    17,     3,    20,    62,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    17,    21,
      23,    20,    16,    20,    15,    17,    64,    64,    64,    23,
      42,    18,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    44,    45,    20,    16,    64,
      16,    16,    16,    21,    45,    18,    23,    18,    15,    18,
      62,    62,    23,    43,    23,    16,    64,    66,    29,    15,
      16,    22,    62,    64,    64,    16,    23
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    47,    54,    54,    55,    55,    56,    57,    57,    58,
      58,    59,    59,    60,    60,    70,    69,    69,    68,    68,
      67,    61,    50,    50,    53,    52,    52,    52,    52,    51,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    63,    65,    65,    49,    49,    66,    66,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      48,    48
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     2,     1,     2,    13,     5,     7,     1,
       2,     1,     2,     1,     1,     7,     2,     3,     1,     3,
       2,     3,     1,     1,     3,     1,     1,     1,     1,     1,
       5,     3,     5,     7,     5,     9,     4,     1,     5,     3,
       2,     1,     6,     5,     1,     4,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     4,     3,
       5,     4,     3,     1,     1,     1,     1,     1,     1,     2,
       1,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"=\"", "\"-\"", "\"+\"",
  "\"*\"", "\"/\"", "\"&&\"", "\"||\"", "\"<\"", "\">\"", "\"==\"",
  "\"%\"", "\"!\"", "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"",
  "\".\"", "\",\"", "\";\"", "\"new\"", "\"this\"", "\"true\"",
  "\"false\"", "\"if\"", "\"else\"", "\"while\"", "\"assert\"",
  "\"class\"", "\"extends\"", "\"public\"", "\"static\"", "\"return\"",
  "\"int\"", "\"boolean\"", "\"void\"", "\"main\"", "\"System\"",
  "\"out\"", "\"println\"", "\"length\"", "\"identifier\"", "\"number\"",
  "$accept", "integer_literal", "lvalue", "type", "type_identifier",
  "simple_type", "array_type", "program", "class_declaration_list",
  "main_class", "class_declaration", "statement_list", "declaration_list",
  "declaration", "variable_declaration", "statement",
  "local_variable_declaration", "expr", "method_invocation",
  "comma_expr_list", "formals", "comma_formals_list", "args_list",
  "method_declaration", YY_NULLPTR
  };

#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   141,   141,   143,   147,   150,   154,   159,   161,   166,
     168,   172,   174,   178,   180,   184,   189,   191,   194,   199,
     204,   207,   211,   212,   215,   218,   219,   220,   221,   224,
     227,   230,   232,   234,   236,   238,   240,   242,   247,   251,
     253,   257,   261,   263,   268,   270,   274,   275,   285,   287,
     289,   291,   293,   295,   297,   299,   301,   303,   306,   309,
     312,   315,   318,   321,   324,   327,   329,   332,   335,   338,
     342,   343
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
#line 2033 "/compilers/compilers_course_4sem_2020/milestone5_functions/parser.cpp"

#line 348 "parser.y"


void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
