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
#line 38 "src/parser.yy" // lalr1.cc:413

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
      case 55: // exp
      case 56: // exp_app
      case 58: // exp_ops
      case 59: // exp_base
        value.move< Shared_Exp > (that.value);
        break;

      case 46: // "tbool"
        value.move< Shared_TBool > (that.value);
        break;

      case 45: // "tint"
        value.move< Shared_TInt > (that.value);
        break;

      case 47: // "tunit"
        value.move< Shared_TUnit > (that.value);
        break;

      case 60: // typ
        value.move< Shared_Typ > (that.value);
        break;

      case 51: // formal
        value.move< arg_t > (that.value);
        break;

      case 52: // formallist
        value.move< arglist_t > (that.value);
        break;

      case 43: // "int"
        value.move< int > (that.value);
        break;

      case 44: // "var"
        value.move< std::string > (that.value);
        break;

      case 57: // expslist
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
      case 55: // exp
      case 56: // exp_app
      case 58: // exp_ops
      case 59: // exp_base
        value.copy< Shared_Exp > (that.value);
        break;

      case 46: // "tbool"
        value.copy< Shared_TBool > (that.value);
        break;

      case 45: // "tint"
        value.copy< Shared_TInt > (that.value);
        break;

      case 47: // "tunit"
        value.copy< Shared_TUnit > (that.value);
        break;

      case 60: // typ
        value.copy< Shared_Typ > (that.value);
        break;

      case 51: // formal
        value.copy< arg_t > (that.value);
        break;

      case 52: // formallist
        value.copy< arglist_t > (that.value);
        break;

      case 43: // "int"
        value.copy< int > (that.value);
        break;

      case 44: // "var"
        value.copy< std::string > (that.value);
        break;

      case 57: // expslist
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
            case 55: // exp

#line 116 "src/parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< Shared_Exp > ()->string_of_exp(); }
#line 400 "src/parser.yy.cpp" // lalr1.cc:636
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
    #line 29 "src/parser.yy" // lalr1.cc:745
{
  // Initialize the initial location.
  // NOTE: For some reasons unknown, I cannot access the filename when try to print error
  yyla.location.begin.filename = yyla.location.end.filename = &driver.file;
}

#line 520 "src/parser.yy.cpp" // lalr1.cc:745

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
      case 55: // exp
      case 56: // exp_app
      case 58: // exp_ops
      case 59: // exp_base
        yylhs.value.build< Shared_Exp > ();
        break;

      case 46: // "tbool"
        yylhs.value.build< Shared_TBool > ();
        break;

      case 45: // "tint"
        yylhs.value.build< Shared_TInt > ();
        break;

      case 47: // "tunit"
        yylhs.value.build< Shared_TUnit > ();
        break;

      case 60: // typ
        yylhs.value.build< Shared_Typ > ();
        break;

      case 51: // formal
        yylhs.value.build< arg_t > ();
        break;

      case 52: // formallist
        yylhs.value.build< arglist_t > ();
        break;

      case 43: // "int"
        yylhs.value.build< int > ();
        break;

      case 44: // "var"
        yylhs.value.build< std::string > ();
        break;

      case 57: // expslist
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
#line 123 "src/parser.yy" // lalr1.cc:859
    {
                                    std::vector<Shared_Exp> v;
                                    v.push_back(std::make_shared<ELit>(1));
                                    *ret = std::make_shared<EApp>("main", v);
                                  }
#line 677 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 3:
#line 131 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< arg_t > () = arg_t(yystack_[2].value.as< std::string > (), yystack_[0].value.as< Shared_Typ > ()); }
#line 683 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 4:
#line 135 "src/parser.yy" // lalr1.cc:859
    {
                                    arglist_t v;
                                    v.push_back(yystack_[0].value.as< arg_t > ());
                                    yylhs.value.as< arglist_t > () = v;
                                  }
#line 693 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 5:
#line 140 "src/parser.yy" // lalr1.cc:859
    {
                                    arglist_t v = yystack_[2].value.as< arglist_t > ();
                                    v.push_back(yystack_[0].value.as< arg_t > ());
                                    yylhs.value.as< arglist_t > () = v;
                                  }
#line 703 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 6:
#line 149 "src/parser.yy" // lalr1.cc:859
    {
                                    std::reverse(yystack_[6].value.as< arglist_t > ().begin(), yystack_[6].value.as< arglist_t > ().end());
                                    function_t func = {
                                      .name = yystack_[8].value.as< std::string > (),
                                      .arglist = yystack_[6].value.as< arglist_t > (),
                                      .return_type = yystack_[3].value.as< Shared_Typ > (),
                                      .e = yystack_[1].value.as< Shared_Exp > ()
                                    };
                                    global_functions.insert({yystack_[8].value.as< std::string > (), func});
                                  }
#line 718 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 9:
#line 167 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = yystack_[0].value.as< Shared_Exp > (); }
#line 724 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 10:
#line 171 "src/parser.yy" // lalr1.cc:859
    {
                                    std::reverse(yystack_[0].value.as< std::vector<Shared_Exp> > ().begin(), yystack_[0].value.as< std::vector<Shared_Exp> > ().end());
                                    yylhs.value.as< Shared_Exp > () = std::make_shared<EApp>(yystack_[1].value.as< std::string > (), yystack_[0].value.as< std::vector<Shared_Exp> > ());
                                  }
#line 733 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 11:
#line 175 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = yystack_[0].value.as< Shared_Exp > (); }
#line 739 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 12:
#line 179 "src/parser.yy" // lalr1.cc:859
    {
                                    std::vector<Shared_Exp> v;
                                    v.push_back(yystack_[0].value.as< Shared_Exp > ());
                                    yylhs.value.as< std::vector<Shared_Exp> > () = v;
                                  }
#line 749 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 13:
#line 184 "src/parser.yy" // lalr1.cc:859
    {
                                    yystack_[1].value.as< std::vector<Shared_Exp> > ().push_back(yystack_[0].value.as< Shared_Exp > ());
                                    yylhs.value.as< std::vector<Shared_Exp> > () = yystack_[1].value.as< std::vector<Shared_Exp> > ();
                                  }
#line 758 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 14:
#line 190 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EOperator>(TokenKind::Plus, yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 764 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 15:
#line 191 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EOperator>(TokenKind::Subtract, yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 770 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 16:
#line 192 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EOperator>(TokenKind::Multiply, yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 776 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 17:
#line 193 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EOperator>(TokenKind::Divide, yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 782 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 18:
#line 194 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EComp>(TokenKind::Leq, yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 788 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 19:
#line 195 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EComp>(TokenKind::Less, yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 794 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 20:
#line 196 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EComp>(TokenKind::Equal, yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 800 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 21:
#line 197 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EComp>(TokenKind::Greater, yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 806 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 22:
#line 198 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EComp>(TokenKind::Geq, yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 812 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 23:
#line 199 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EPair>(yystack_[3].value.as< Shared_Exp > (), yystack_[1].value.as< Shared_Exp > ()); }
#line 818 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 24:
#line 200 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EFst>(yystack_[1].value.as< Shared_Exp > ()); }
#line 824 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 25:
#line 201 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<ESnd>(yystack_[1].value.as< Shared_Exp > ()); }
#line 830 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 26:
#line 202 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<ECar>(yystack_[1].value.as< Shared_Exp > ()); }
#line 836 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 27:
#line 203 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<ECdr>(yystack_[1].value.as< Shared_Exp > ()); }
#line 842 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 28:
#line 204 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EEmpty>(yystack_[1].value.as< Shared_Exp > ()); }
#line 848 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 29:
#line 205 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<ECons>(yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 854 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 30:
#line 206 "src/parser.yy" // lalr1.cc:859
    {
                                    std::vector<Shared_Exp> v;
                                    yylhs.value.as< Shared_Exp > () = std::make_shared<EList>(v, yystack_[0].value.as< Shared_Typ > ());
                                  }
#line 863 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 31:
#line 210 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<ERef>(yystack_[1].value.as< Shared_Exp > ()); }
#line 869 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 32:
#line 211 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EDeref>(yystack_[0].value.as< Shared_Exp > ()); }
#line 875 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 33:
#line 212 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EAssign>(yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 881 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 34:
#line 213 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<ESeq>(yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 887 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 35:
#line 214 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = yystack_[0].value.as< Shared_Exp > (); }
#line 893 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 36:
#line 218 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EUnit>(); }
#line 899 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 37:
#line 219 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<ELit>(yystack_[0].value.as< int > ()); }
#line 905 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 38:
#line 220 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EBool>(true); }
#line 911 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 39:
#line 221 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EBool>(false); }
#line 917 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 40:
#line 222 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EVar>(yystack_[0].value.as< std::string > ()); }
#line 923 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 41:
#line 224 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EIf>(yystack_[4].value.as< Shared_Exp > (), yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 929 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 42:
#line 226 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<ELet>(yystack_[6].value.as< std::string > (), yystack_[4].value.as< Shared_Typ > (), yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 935 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 43:
#line 228 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EWhile>(yystack_[3].value.as< Shared_Exp > (), yystack_[1].value.as< Shared_Exp > (), yystack_[3].value.as< Shared_Exp > ()); }
#line 941 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 44:
#line 229 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = yystack_[1].value.as< Shared_Exp > (); }
#line 947 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 45:
#line 232 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Typ > () = yystack_[0].value.as< Shared_TInt > (); }
#line 953 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 46:
#line 233 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Typ > () = yystack_[0].value.as< Shared_TBool > (); }
#line 959 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 47:
#line 234 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Typ > () = yystack_[0].value.as< Shared_TUnit > (); }
#line 965 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 48:
#line 235 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Typ > () = std::make_shared<TPair>(yystack_[2].value.as< Shared_Typ > (), yystack_[0].value.as< Shared_Typ > ()); }
#line 971 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 49:
#line 236 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Typ > () = std::make_shared<TList>(yystack_[1].value.as< Shared_Typ > ()); }
#line 977 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 50:
#line 237 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Typ > () = std::make_shared<TRef>(yystack_[1].value.as< Shared_Typ > ()); }
#line 983 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 51:
#line 238 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Typ > () = yystack_[1].value.as< Shared_Typ > (); }
#line 989 "src/parser.yy.cpp" // lalr1.cc:859
    break;


#line 993 "src/parser.yy.cpp" // lalr1.cc:859
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


  const signed char parser::yypact_ninf_ = -36;

  const signed char parser::yytable_ninf_ = -1;

  const short int
  parser::yypact_[] =
  {
     -11,   -33,    48,   -36,     6,    14,   -36,   -36,   -36,     7,
      37,   -36,    11,    -2,    43,     7,    -2,    -2,    -2,   -36,
     -36,   -36,    53,    -2,   -36,     2,    33,    23,    -2,    35,
     -36,   -36,   -36,    53,   327,   299,   327,   -36,   -36,    15,
      56,    57,    40,    60,    61,    63,   355,    64,   327,   -36,
     355,    38,   -36,   257,   -36,   -36,    52,    26,    62,    67,
     355,   355,    70,   355,   355,   355,   -36,    12,   355,    39,
     355,   257,   -36,   355,   355,   355,   355,   355,   355,   355,
     355,   355,   355,   355,   355,   -36,   355,   327,    -2,   105,
     116,    -2,   152,   163,   199,   210,   327,   257,    36,    36,
     -36,   -36,   127,   127,   127,   127,   127,   257,   397,   293,
     246,    68,    42,   -36,   -36,    53,   -36,   -36,   -36,   -36,
      65,   -36,   327,   327,   -36,   -36,    96,   327,   -36
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     0,     0,     7,     0,     0,     1,     2,     8,     0,
       0,     4,     0,     0,     0,     0,     0,     0,     0,    45,
      46,    47,     3,     0,     5,     0,     0,     0,     0,     0,
      50,    51,    49,    48,     0,     0,     0,    38,    39,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    37,
      40,     0,     9,    11,    35,    36,     0,    11,     0,     0,
       0,     0,     0,     0,     0,     0,    40,    32,     0,     0,
      10,    12,     6,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    44,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    13,    14,    15,
      16,    17,    19,    18,    20,    21,    22,    29,    33,    34,
       0,     0,     0,    24,    25,    30,    26,    27,    28,    31,
       0,    23,     0,     0,    43,    41,     0,     0,    42
  };

  const short int
  parser::yypgoto_[] =
  {
     -36,   -36,   113,   -36,   130,   -36,   -35,   -36,   -36,    21,
     -36,   -14
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,     2,    11,    12,     3,     4,    51,    52,    70,    53,
      54,    22
  };

  const unsigned char
  parser::yytable_[] =
  {
      56,    58,    25,    26,    27,    16,     7,    28,     1,    29,
      17,     5,    30,    69,    33,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    14,     1,     9,    18,    28,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    28,    15,
      28,    75,    76,    19,    20,    21,    31,    28,     6,    83,
      84,    10,   111,    32,    86,    34,    57,    82,    28,    59,
      13,   120,   123,    83,    84,    85,    23,    67,    60,    61,
      62,    71,    63,    64,   112,    65,    68,   115,    87,    96,
      72,    89,    90,   122,    92,    93,    94,   125,   126,    95,
      88,    97,   128,    91,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   124,   110,    73,    74,
      75,    76,    77,    78,    79,    80,    81,   127,   113,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    24,   114,
      73,    74,    75,    76,     8,     0,    82,     0,     0,     0,
       0,     0,    83,    84,     0,     0,     0,    82,     0,     0,
       0,     0,     0,    83,    84,    73,    74,    75,    76,    77,
      78,    79,    80,    81,     0,   116,    73,    74,    75,    76,
      77,    78,    79,    80,    81,     0,   117,     0,     0,     0,
       0,     0,     0,    82,     0,     0,     0,     0,     0,    83,
      84,     0,     0,     0,    82,     0,     0,     0,     0,     0,
      83,    84,    73,    74,    75,    76,    77,    78,    79,    80,
      81,     0,   118,    73,    74,    75,    76,    77,    78,    79,
      80,    81,     0,   119,     0,     0,     0,     0,     0,     0,
      82,     0,     0,     0,     0,     0,    83,    84,     0,     0,
       0,    82,     0,     0,     0,     0,     0,    83,    84,    73,
      74,    75,    76,    77,    78,    79,    80,    81,     0,   121,
      73,    74,    75,    76,    77,    78,    79,    80,    81,     0,
       0,     0,     0,     0,     0,     0,     0,    82,     0,     0,
       0,     0,     0,    83,    84,     0,     0,     0,    82,     0,
       0,     0,     0,     0,    83,    84,    73,    74,    75,    76,
      77,    78,    79,    80,    81,     0,     0,     0,     0,     0,
       0,    35,    55,    36,     0,     0,    37,    38,    39,     0,
       0,     0,     0,     0,     0,    40,    41,     0,    42,     0,
      83,    43,    44,    45,    46,    47,     0,     0,    48,    35,
       0,    36,    49,    50,    37,    38,    39,     0,     0,     0,
       0,     0,     0,    40,    41,     0,    42,     0,     0,    43,
      44,    45,    46,    47,     0,     0,    48,    35,     0,    36,
      49,    50,    37,    38,    39,     0,     0,     0,     0,     0,
       0,    40,    41,     0,    42,     0,     0,    43,    44,    45,
      46,    47,     0,     0,    48,     0,     0,     0,    49,    66,
      73,    74,    75,    76,    77,    78,    79,    80,    81
  };

  const signed char
  parser::yycheck_[] =
  {
      35,    36,    16,    17,    18,     7,     0,     5,    19,    23,
      12,    44,    10,    48,    28,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    13,    19,    12,    29,     5,     3,
       4,     5,     6,     7,     8,     9,    10,    11,     5,    28,
       5,     5,     6,    45,    46,    47,    13,     5,     0,    37,
      38,    44,    87,    30,    28,    20,    35,    31,     5,    44,
      23,    96,    20,    37,    38,    13,    23,    46,    12,    12,
      30,    50,    12,    12,    88,    12,    12,    91,    16,    40,
      42,    60,    61,    15,    63,    64,    65,   122,   123,    68,
      23,    70,   127,    23,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    41,    86,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    21,    13,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    15,    13,
       3,     4,     5,     6,     4,    -1,    31,    -1,    -1,    -1,
      -1,    -1,    37,    38,    -1,    -1,    -1,    31,    -1,    -1,
      -1,    -1,    -1,    37,    38,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    -1,    13,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    -1,    13,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    37,
      38,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,
      37,    38,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    -1,    13,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    -1,    13,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    -1,    -1,    -1,    -1,    -1,    37,    38,    -1,    -1,
      -1,    31,    -1,    -1,    -1,    -1,    -1,    37,    38,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    -1,    13,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,
      -1,    -1,    -1,    37,    38,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    -1,    -1,    37,    38,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    12,    13,    14,    -1,    -1,    17,    18,    19,    -1,
      -1,    -1,    -1,    -1,    -1,    26,    27,    -1,    29,    -1,
      37,    32,    33,    34,    35,    36,    -1,    -1,    39,    12,
      -1,    14,    43,    44,    17,    18,    19,    -1,    -1,    -1,
      -1,    -1,    -1,    26,    27,    -1,    29,    -1,    -1,    32,
      33,    34,    35,    36,    -1,    -1,    39,    12,    -1,    14,
      43,    44,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,
      -1,    26,    27,    -1,    29,    -1,    -1,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,    -1,    43,    44,
       3,     4,     5,     6,     7,     8,     9,    10,    11
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    19,    50,    53,    54,    44,     0,     0,    53,    12,
      44,    51,    52,    23,    13,    28,     7,    12,    29,    45,
      46,    47,    60,    23,    51,    60,    60,    60,     5,    60,
      10,    13,    30,    60,    20,    12,    14,    17,    18,    19,
      26,    27,    29,    32,    33,    34,    35,    36,    39,    43,
      44,    55,    56,    58,    59,    13,    55,    58,    55,    44,
      12,    12,    30,    12,    12,    12,    44,    58,    12,    55,
      57,    58,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    31,    37,    38,    13,    28,    16,    23,    58,
      58,    23,    58,    58,    58,    58,    40,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    55,    60,    13,    13,    60,    13,    13,    13,    13,
      55,    13,    15,    20,    41,    55,    55,    21,    55
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    49,    50,    51,    52,    52,    53,    54,    54,    55,
      56,    56,    57,    57,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    60,    60,    60,    60,    60,
      60,    60
  };

  const unsigned char
  parser::yyr2_[] =
  {
       0,     2,     2,     3,     1,     3,    10,     1,     2,     1,
       2,     1,     1,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     5,     4,     4,     4,     4,     4,     3,
       4,     4,     2,     3,     3,     1,     2,     1,     1,     1,
       1,     6,     8,     5,     3,     1,     1,     1,     3,     3,
       3,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"eof\"", "error", "$undefined", "\"+\"", "\"-\"", "\"*\"", "\"/\"",
  "\"<\"", "\"<=\"", "\"==\"", "\">\"", "\">=\"", "\"(\"", "\")\"",
  "\"if\"", "\"else\"", "\"then\"", "\"true\"", "\"false\"", "\"let\"",
  "\"=\"", "\"in\"", "\"rec\"", "\":\"", "\"[\"", "\"]\"", "\"fst\"",
  "\"snd\"", "\",\"", "\"{\"", "\"}\"", "\"::\"", "\"car\"", "\"cdr\"",
  "\"empty\"", "\"!\"", "\"ref\"", "\":=\"", "\";\"", "\"while\"",
  "\"do\"", "\"end\"", "\";;\"", "\"int\"", "\"var\"", "\"tint\"",
  "\"tbool\"", "\"tunit\"", "\".\"", "$accept", "prog", "formal",
  "formallist", "decl", "decllist", "exp", "exp_app", "expslist",
  "exp_ops", "exp_base", "typ", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  parser::yyrline_[] =
  {
       0,   123,   123,   131,   135,   140,   148,   162,   163,   167,
     171,   175,   179,   184,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   210,   211,   212,   213,   214,   218,   219,   220,   221,
     222,   223,   225,   227,   229,   232,   233,   234,   235,   236,
     237,   238
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
#line 1497 "src/parser.yy.cpp" // lalr1.cc:1167
#line 240 "src/parser.yy" // lalr1.cc:1168


// NOTE: Bison's error reporting simply forwards to the driver
void yy::parser::error(const yy::parser::location_type& l, const std::string &m) { driver.error(l, m); }
