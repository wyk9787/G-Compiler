// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

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


// First part of user declarations.

#line 37 "src/parser.yy.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "parser.yy.hpp"

// User implementation prologue.

#line 51 "src/parser.yy.cpp" // lalr1.cc:412
// Unqualified %code blocks.
#line 37 "src/parser.yy" // lalr1.cc:413

#include "parser_driver.h"
#include "token.hpp"
#include "type.hpp"
#include "interpreter.hpp"

#line 60 "src/parser.yy.cpp" // lalr1.cc:413


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
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

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
      *yycdebug_ << std::endl;                  \
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
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 146 "src/parser.yy.cpp" // lalr1.cc:479

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
        std::string yyr = "";
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
              // Fall through.
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
  parser::parser (parser_driver &driver_yyarg, Shared_Exp *ret_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg),
      ret (ret_yyarg)
  {}

  parser::~parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  parser::symbol_number_type
  parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 59: // exp
      case 60: // exp_app
      case 62: // exp_ops
      case 63: // exp_base
        value.move< Shared_Exp > (that.value);
        break;

      case 50: // "tbool"
        value.move< Shared_TBool > (that.value);
        break;

      case 49: // "tfloat"
        value.move< Shared_TFloat > (that.value);
        break;

      case 48: // "tint"
        value.move< Shared_TInt > (that.value);
        break;

      case 51: // "tunit"
        value.move< Shared_TUnit > (that.value);
        break;

      case 64: // typ
        value.move< Shared_Typ > (that.value);
        break;

      case 55: // formal
        value.move< arg_t > (that.value);
        break;

      case 56: // formallist
        value.move< arglist_t > (that.value);
        break;

      case 46: // "double"
        value.move< double > (that.value);
        break;

      case 45: // "int"
        value.move< int > (that.value);
        break;

      case 47: // "var"
        value.move< std::string > (that.value);
        break;

      case 61: // expslist
        value.move< std::vector<Shared_Exp> > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 59: // exp
      case 60: // exp_app
      case 62: // exp_ops
      case 63: // exp_base
        value.copy< Shared_Exp > (that.value);
        break;

      case 50: // "tbool"
        value.copy< Shared_TBool > (that.value);
        break;

      case 49: // "tfloat"
        value.copy< Shared_TFloat > (that.value);
        break;

      case 48: // "tint"
        value.copy< Shared_TInt > (that.value);
        break;

      case 51: // "tunit"
        value.copy< Shared_TUnit > (that.value);
        break;

      case 64: // typ
        value.copy< Shared_Typ > (that.value);
        break;

      case 55: // formal
        value.copy< arg_t > (that.value);
        break;

      case 56: // formallist
        value.copy< arglist_t > (that.value);
        break;

      case 46: // "double"
        value.copy< double > (that.value);
        break;

      case 45: // "int"
        value.copy< int > (that.value);
        break;

      case 47: // "var"
        value.copy< std::string > (that.value);
        break;

      case 61: // expslist
        value.copy< std::vector<Shared_Exp> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
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
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    switch (yytype)
    {
            case 59: // exp

#line 119 "src/parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< Shared_Exp > ()->string_of_exp(); }
#line 416 "src/parser.yy.cpp" // lalr1.cc:636
        break;


      default:
        break;
    }
    yyo << ')';
  }
#endif

  inline
  void
  parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  parser::yypop_ (unsigned int n)
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

  inline parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::parse ()
  {
    // State.
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

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    // User initialization code.
    #line 28 "src/parser.yy" // lalr1.cc:745
{
  // Initialize the initial location.
  // NOTE: For some reasons unknown, I cannot access the filename when try to print error
  yyla.location.begin.filename = yyla.location.end.filename = &driver.file;
}

#line 536 "src/parser.yy.cpp" // lalr1.cc:745

    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex (driver));
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

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
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 59: // exp
      case 60: // exp_app
      case 62: // exp_ops
      case 63: // exp_base
        yylhs.value.build< Shared_Exp > ();
        break;

      case 50: // "tbool"
        yylhs.value.build< Shared_TBool > ();
        break;

      case 49: // "tfloat"
        yylhs.value.build< Shared_TFloat > ();
        break;

      case 48: // "tint"
        yylhs.value.build< Shared_TInt > ();
        break;

      case 51: // "tunit"
        yylhs.value.build< Shared_TUnit > ();
        break;

      case 64: // typ
        yylhs.value.build< Shared_Typ > ();
        break;

      case 55: // formal
        yylhs.value.build< arg_t > ();
        break;

      case 56: // formallist
        yylhs.value.build< arglist_t > ();
        break;

      case 46: // "double"
        yylhs.value.build< double > ();
        break;

      case 45: // "int"
        yylhs.value.build< int > ();
        break;

      case 47: // "var"
        yylhs.value.build< std::string > ();
        break;

      case 61: // expslist
        yylhs.value.build< std::vector<Shared_Exp> > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 126 "src/parser.yy" // lalr1.cc:859
    {
                                    std::vector<Shared_Exp> v;
                                    v.push_back(std::make_shared<ELit>(true, 1, 0, false));
                                    *ret = std::make_shared<EApp>("main", v);
                                  }
#line 701 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 3:
#line 134 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< arg_t > () = arg_t(yystack_[2].value.as< std::string > (), yystack_[0].value.as< Shared_Typ > ()); }
#line 707 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 4:
#line 138 "src/parser.yy" // lalr1.cc:859
    {
                                    arglist_t v;
                                    v.push_back(yystack_[0].value.as< arg_t > ());
                                    yylhs.value.as< arglist_t > () = v;
                                  }
#line 717 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 5:
#line 143 "src/parser.yy" // lalr1.cc:859
    {
                                    arglist_t v = yystack_[2].value.as< arglist_t > ();
                                    v.push_back(yystack_[0].value.as< arg_t > ());
                                    yylhs.value.as< arglist_t > () = v;
                                  }
#line 727 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 6:
#line 152 "src/parser.yy" // lalr1.cc:859
    {
                                    std::reverse(yystack_[6].value.as< arglist_t > ().begin(), yystack_[6].value.as< arglist_t > ().end());
                                    function_t func = {
                                      .arglist = yystack_[6].value.as< arglist_t > (),
                                      .return_type = yystack_[3].value.as< Shared_Typ > (),
                                      .e = yystack_[1].value.as< Shared_Exp > ()
                                    };
                                    global_functions.insert({yystack_[8].value.as< std::string > (), func});
                                  }
#line 741 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 9:
#line 169 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = yystack_[0].value.as< Shared_Exp > (); }
#line 747 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 10:
#line 173 "src/parser.yy" // lalr1.cc:859
    {
                                    std::reverse(yystack_[0].value.as< std::vector<Shared_Exp> > ().begin(), yystack_[0].value.as< std::vector<Shared_Exp> > ().end());
                                    yylhs.value.as< Shared_Exp > () = std::make_shared<EApp>(yystack_[1].value.as< std::string > (), yystack_[0].value.as< std::vector<Shared_Exp> > ());
                                  }
#line 756 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 11:
#line 177 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = yystack_[0].value.as< Shared_Exp > (); }
#line 762 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 12:
#line 181 "src/parser.yy" // lalr1.cc:859
    {
                                    std::vector<Shared_Exp> v;
                                    v.push_back(yystack_[0].value.as< Shared_Exp > ());
                                    yylhs.value.as< std::vector<Shared_Exp> > () = v;
                                  }
#line 772 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 13:
#line 186 "src/parser.yy" // lalr1.cc:859
    {
                                    yystack_[1].value.as< std::vector<Shared_Exp> > ().push_back(yystack_[0].value.as< Shared_Exp > ());
                                    yylhs.value.as< std::vector<Shared_Exp> > () = yystack_[1].value.as< std::vector<Shared_Exp> > ();
                                  }
#line 781 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 14:
#line 192 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EOperator>(TokenKind::Plus, yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 787 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 15:
#line 193 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EOperator>(TokenKind::Subtract, yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 793 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 16:
#line 194 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EOperator>(TokenKind::Multiply, yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 799 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 17:
#line 195 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EOperator>(TokenKind::Divide, yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 805 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 18:
#line 196 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EComp>(TokenKind::Leq, yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 811 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 19:
#line 197 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EComp>(TokenKind::Less, yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 817 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 20:
#line 198 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EComp>(TokenKind::Equal, yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 823 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 21:
#line 199 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EComp>(TokenKind::Greater, yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 829 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 22:
#line 200 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EComp>(TokenKind::Geq, yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 835 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 23:
#line 201 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EPair>(yystack_[3].value.as< Shared_Exp > (), yystack_[1].value.as< Shared_Exp > ()); }
#line 841 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 24:
#line 202 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EFst>(yystack_[1].value.as< Shared_Exp > ()); }
#line 847 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 25:
#line 203 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<ESnd>(yystack_[1].value.as< Shared_Exp > ()); }
#line 853 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 26:
#line 204 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<ECar>(yystack_[1].value.as< Shared_Exp > ()); }
#line 859 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 27:
#line 205 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<ECdr>(yystack_[1].value.as< Shared_Exp > ()); }
#line 865 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 28:
#line 206 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EEmpty>(yystack_[1].value.as< Shared_Exp > ()); }
#line 871 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 29:
#line 207 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<ECons>(yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 877 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 30:
#line 208 "src/parser.yy" // lalr1.cc:859
    {
                                    std::vector<Shared_Exp> v;
                                    yylhs.value.as< Shared_Exp > () = std::make_shared<EList>(v, yystack_[0].value.as< Shared_Typ > ());
                                  }
#line 886 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 31:
#line 212 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<ERef>(yystack_[1].value.as< Shared_Exp > ()); }
#line 892 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 32:
#line 213 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EDeref>(yystack_[0].value.as< Shared_Exp > ()); }
#line 898 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 33:
#line 214 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EAssign>(yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 904 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 34:
#line 215 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<ESeq>(yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 910 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 35:
#line 216 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = yystack_[0].value.as< Shared_Exp > (); }
#line 916 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 36:
#line 220 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EUnit>(); }
#line 922 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 37:
#line 221 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<ELit>(true, yystack_[0].value.as< int > (), 0, false); }
#line 928 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 38:
#line 222 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<ELit>(false, 0, yystack_[0].value.as< double > (), false); }
#line 934 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 39:
#line 223 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EBool>(true); }
#line 940 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 40:
#line 224 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EBool>(false); }
#line 946 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 41:
#line 225 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<ELit>(false, 0, 0, true); }
#line 952 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 42:
#line 226 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EVar>(yystack_[0].value.as< std::string > ()); }
#line 958 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 43:
#line 228 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EIf>(yystack_[4].value.as< Shared_Exp > (), yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 964 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 44:
#line 230 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<ELet>(yystack_[6].value.as< std::string > (), yystack_[4].value.as< Shared_Typ > (), yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 970 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 45:
#line 232 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EWhile>(yystack_[3].value.as< Shared_Exp > (), yystack_[1].value.as< Shared_Exp > (), yystack_[3].value.as< Shared_Exp > ()); }
#line 976 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 46:
#line 233 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = yystack_[1].value.as< Shared_Exp > (); }
#line 982 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 47:
#line 236 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Typ > () = yystack_[0].value.as< Shared_TInt > (); }
#line 988 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 48:
#line 237 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Typ > () = yystack_[0].value.as< Shared_TFloat > (); }
#line 994 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 49:
#line 238 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Typ > () = yystack_[0].value.as< Shared_TBool > (); }
#line 1000 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 50:
#line 239 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Typ > () = yystack_[0].value.as< Shared_TUnit > (); }
#line 1006 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 51:
#line 240 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Typ > () = std::make_shared<TFunc>(yystack_[2].value.as< Shared_Typ > (), yystack_[0].value.as< Shared_Typ > ()); }
#line 1012 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 52:
#line 241 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Typ > () = std::make_shared<TPair>(yystack_[2].value.as< Shared_Typ > (), yystack_[0].value.as< Shared_Typ > ()); }
#line 1018 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 53:
#line 242 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Typ > () = std::make_shared<TList>(yystack_[1].value.as< Shared_Typ > ()); }
#line 1024 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 54:
#line 243 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Typ > () = std::make_shared<TRef>(yystack_[1].value.as< Shared_Typ > ()); }
#line 1030 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 55:
#line 244 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Typ > () = yystack_[1].value.as< Shared_Typ > (); }
#line 1036 "src/parser.yy.cpp" // lalr1.cc:859
    break;


#line 1040 "src/parser.yy.cpp" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
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

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
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
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
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
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

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
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
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
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
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
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
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
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
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


  const signed char parser::yypact_ninf_ = -39;

  const signed char parser::yytable_ninf_ = -1;

  const short int
  parser::yypact_[] =
  {
     -11,   -32,    26,   -39,     9,    38,   -39,   -39,   -39,     5,
      30,   -39,    34,    -6,    32,     5,    -6,    -6,    -6,   -39,
     -39,   -39,   -39,     3,    -6,   -39,    36,    46,     8,    -6,
      -6,     2,   -39,   -39,   -39,     3,     3,   363,   327,   -39,
     363,   -39,   -39,     6,    48,    50,    37,    58,    59,    60,
     399,    61,   363,   -39,   -39,   399,    31,   -39,   274,   -39,
     -39,    63,    28,    57,    53,   399,   399,    54,   399,   399,
     399,   -39,   283,   399,    39,   399,   274,   -39,   399,   399,
     399,   399,   399,   399,   399,   399,   399,   399,   399,   399,
     -39,   399,   363,    -6,   116,   127,    -6,   165,   176,   214,
     225,   363,   274,    43,    43,   -39,   -39,    15,    15,    15,
      15,    15,   274,   444,   321,   263,    68,     7,   -39,   -39,
       3,   -39,   -39,   -39,   -39,    42,   -39,   363,   363,   -39,
     -39,    64,   363,   -39
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     0,     0,     7,     0,     0,     1,     2,     8,     0,
       0,     4,     0,     0,     0,     0,     0,     0,     0,    47,
      48,    49,    50,     3,     0,     5,     0,     0,     0,     0,
       0,     0,    54,    55,    53,    52,    51,     0,     0,    41,
       0,    39,    40,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    37,    38,    42,     0,     9,    11,    35,
      36,     0,    11,     0,     0,     0,     0,     0,     0,     0,
       0,    42,    32,     0,     0,    10,    12,     6,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      46,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    13,    14,    15,    16,    17,    19,    18,    20,
      21,    22,    29,    33,    34,     0,     0,     0,    24,    25,
      30,    26,    27,    28,    31,     0,    23,     0,     0,    45,
      43,     0,     0,    44
  };

  const signed char
  parser::yypgoto_[] =
  {
     -39,   -39,    71,   -39,    84,   -39,   -38,   -39,   -39,    27,
     -39,   -13
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,     2,    11,    12,     3,     4,    56,    57,    75,    58,
      59,    23
  };

  const unsigned char
  parser::yytable_[] =
  {
      61,    16,    63,    26,    27,    28,    17,    29,    29,     7,
       1,    31,    29,    29,    74,     5,    35,    36,    78,    79,
      80,    81,    30,    30,    37,    18,     6,    30,    30,   128,
       1,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      34,    29,    19,    20,    21,    22,    32,    14,    80,    81,
       9,    29,    10,    64,   116,    13,    30,    24,    91,    33,
      65,    87,    66,   125,    15,    62,    30,    88,    89,    67,
      68,    69,    70,    73,    92,    77,    90,    72,    93,    96,
     117,   101,    76,   120,   127,   129,    25,   132,     8,   130,
     131,     0,    94,    95,   133,    97,    98,    99,     0,     0,
     100,     0,   102,     0,     0,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,     0,   115,    78,
      79,    80,    81,    82,    83,    84,    85,    86,     0,   118,
      78,    79,    80,    81,    82,    83,    84,    85,    86,     0,
     119,     0,     0,     0,     0,     0,     0,     0,     0,    87,
       0,     0,     0,     0,     0,    88,    89,     0,     0,     0,
      87,     0,     0,     0,     0,     0,    88,    89,    78,    79,
      80,    81,    82,    83,    84,    85,    86,     0,   121,    78,
      79,    80,    81,    82,    83,    84,    85,    86,     0,   122,
       0,     0,     0,     0,     0,     0,     0,     0,    87,     0,
       0,     0,     0,     0,    88,    89,     0,     0,     0,    87,
       0,     0,     0,     0,     0,    88,    89,    78,    79,    80,
      81,    82,    83,    84,    85,    86,     0,   123,    78,    79,
      80,    81,    82,    83,    84,    85,    86,     0,   124,     0,
       0,     0,     0,     0,     0,     0,     0,    87,     0,     0,
       0,     0,     0,    88,    89,     0,     0,     0,    87,     0,
       0,     0,     0,     0,    88,    89,    78,    79,    80,    81,
      82,    83,    84,    85,    86,     0,   126,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    78,    79,    80,    81,
      82,    83,    84,    85,    86,     0,    87,     0,     0,     0,
       0,     0,    88,    89,     0,     0,     0,    87,     0,     0,
       0,     0,     0,    88,    89,     0,     0,     0,     0,     0,
       0,     0,    88,    89,    78,    79,    80,    81,    82,    83,
      84,    85,    86,     0,     0,     0,     0,     0,     0,    38,
      60,    39,    40,     0,     0,    41,    42,     0,    43,     0,
       0,     0,     0,     0,     0,    44,    45,     0,    46,     0,
      88,    47,    48,    49,    50,    51,     0,     0,    52,     0,
       0,     0,    53,    54,    55,    38,     0,    39,    40,     0,
       0,    41,    42,     0,    43,     0,     0,     0,     0,     0,
       0,    44,    45,     0,    46,     0,     0,    47,    48,    49,
      50,    51,     0,     0,    52,     0,     0,     0,    53,    54,
      55,    38,     0,    39,    40,     0,     0,    41,    42,     0,
      43,     0,     0,     0,     0,     0,     0,    44,    45,     0,
      46,     0,     0,    47,    48,    49,    50,    51,     0,     0,
      52,     0,     0,     0,    53,    54,    71,    78,    79,    80,
      81,    82,    83,    84,    85,    86
  };

  const short int
  parser::yycheck_[] =
  {
      38,     7,    40,    16,    17,    18,    12,     5,     5,     0,
      21,    24,     5,     5,    52,    47,    29,    30,     3,     4,
       5,     6,    20,    20,    22,    31,     0,    20,    20,    22,
      21,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      32,     5,    48,    49,    50,    51,    10,    13,     5,     6,
      12,     5,    47,    47,    92,    25,    20,    25,    30,    13,
      12,    33,    12,   101,    30,    38,    20,    39,    40,    32,
      12,    12,    12,    12,    17,    44,    13,    50,    25,    25,
      93,    42,    55,    96,    16,    43,    15,    23,     4,   127,
     128,    -1,    65,    66,   132,    68,    69,    70,    -1,    -1,
      73,    -1,    75,    -1,    -1,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    -1,    91,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    -1,    13,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    -1,
      13,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,
      -1,    -1,    -1,    -1,    -1,    39,    40,    -1,    -1,    -1,
      33,    -1,    -1,    -1,    -1,    -1,    39,    40,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    -1,    13,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    -1,    13,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    -1,
      -1,    -1,    -1,    -1,    39,    40,    -1,    -1,    -1,    33,
      -1,    -1,    -1,    -1,    -1,    39,    40,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    -1,    13,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    -1,    13,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    -1,    -1,
      -1,    -1,    -1,    39,    40,    -1,    -1,    -1,    33,    -1,
      -1,    -1,    -1,    -1,    39,    40,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    -1,    13,     3,     4,     5,
       6,     7,     8,     9,    10,    11,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    -1,    33,    -1,    -1,    -1,
      -1,    -1,    39,    40,    -1,    -1,    -1,    33,    -1,    -1,
      -1,    -1,    -1,    39,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    40,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    12,
      13,    14,    15,    -1,    -1,    18,    19,    -1,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    29,    -1,    31,    -1,
      39,    34,    35,    36,    37,    38,    -1,    -1,    41,    -1,
      -1,    -1,    45,    46,    47,    12,    -1,    14,    15,    -1,
      -1,    18,    19,    -1,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    29,    -1,    31,    -1,    -1,    34,    35,    36,
      37,    38,    -1,    -1,    41,    -1,    -1,    -1,    45,    46,
      47,    12,    -1,    14,    15,    -1,    -1,    18,    19,    -1,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    -1,
      31,    -1,    -1,    34,    35,    36,    37,    38,    -1,    -1,
      41,    -1,    -1,    -1,    45,    46,    47,     3,     4,     5,
       6,     7,     8,     9,    10,    11
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    21,    54,    57,    58,    47,     0,     0,    57,    12,
      47,    55,    56,    25,    13,    30,     7,    12,    31,    48,
      49,    50,    51,    64,    25,    55,    64,    64,    64,     5,
      20,    64,    10,    13,    32,    64,    64,    22,    12,    14,
      15,    18,    19,    21,    28,    29,    31,    34,    35,    36,
      37,    38,    41,    45,    46,    47,    59,    60,    62,    63,
      13,    59,    62,    59,    47,    12,    12,    32,    12,    12,
      12,    47,    62,    12,    59,    61,    62,    44,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    33,    39,    40,
      13,    30,    17,    25,    62,    62,    25,    62,    62,    62,
      62,    42,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    59,    64,    13,    13,
      64,    13,    13,    13,    13,    59,    13,    16,    22,    43,
      59,    59,    23,    59
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    53,    54,    55,    56,    56,    57,    58,    58,    59,
      60,    60,    61,    61,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    64,    64,    64,
      64,    64,    64,    64,    64,    64
  };

  const unsigned char
  parser::yyr2_[] =
  {
       0,     2,     2,     3,     1,     3,    10,     1,     2,     1,
       2,     1,     1,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     5,     4,     4,     4,     4,     4,     3,
       4,     4,     2,     3,     3,     1,     2,     1,     1,     1,
       1,     1,     1,     6,     8,     5,     3,     1,     1,     1,
       1,     3,     3,     3,     3,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"eof\"", "error", "$undefined", "\"+\"", "\"-\"", "\"*\"", "\"/\"",
  "\"<\"", "\"<=\"", "\"==\"", "\">\"", "\">=\"", "\"(\"", "\")\"",
  "\"NaN\"", "\"if\"", "\"else\"", "\"then\"", "\"true\"", "\"false\"",
  "\"->\"", "\"let\"", "\"=\"", "\"in\"", "\"rec\"", "\":\"", "\"[\"",
  "\"]\"", "\"fst\"", "\"snd\"", "\",\"", "\"{\"", "\"}\"", "\"::\"",
  "\"car\"", "\"cdr\"", "\"empty\"", "\"!\"", "\"ref\"", "\":=\"", "\";\"",
  "\"while\"", "\"do\"", "\"end\"", "\";;\"", "\"int\"", "\"double\"",
  "\"var\"", "\"tint\"", "\"tfloat\"", "\"tbool\"", "\"tunit\"", "\".\"",
  "$accept", "prog", "formal", "formallist", "decl", "decllist", "exp",
  "exp_app", "expslist", "exp_ops", "exp_base", "typ", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  parser::yyrline_[] =
  {
       0,   126,   126,   134,   138,   143,   151,   164,   165,   169,
     173,   177,   181,   186,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   212,   213,   214,   215,   216,   220,   221,   222,   223,
     224,   225,   226,   227,   229,   231,   233,   236,   237,   238,
     239,   240,   241,   242,   243,   244
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
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG



} // yy
#line 1557 "src/parser.yy.cpp" // lalr1.cc:1167
#line 246 "src/parser.yy" // lalr1.cc:1168


// NOTE: Bison's error reporting simply forwards to the driver
void yy::parser::error(const yy::parser::location_type& l, const std::string &m) { driver.error(l, m); }
