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
#line 36 "src/parser.yy" // lalr1.cc:413

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
        value.move< Shared_Exp > (that.value);
        break;

      case 55: // "tbool"
        value.move< Shared_TBool > (that.value);
        break;

      case 54: // "tfloat"
        value.move< Shared_TFloat > (that.value);
        break;

      case 53: // "tint"
        value.move< Shared_TInt > (that.value);
        break;

      case 56: // "tunit"
        value.move< Shared_TUnit > (that.value);
        break;

      case 60: // typ
        value.move< Shared_Typ > (that.value);
        break;

      case 50: // "double"
        value.move< double > (that.value);
        break;

      case 49: // "int"
        value.move< int > (that.value);
        break;

      case 51: // "var"
      case 52: // "filename"
        value.move< std::string > (that.value);
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
        value.copy< Shared_Exp > (that.value);
        break;

      case 55: // "tbool"
        value.copy< Shared_TBool > (that.value);
        break;

      case 54: // "tfloat"
        value.copy< Shared_TFloat > (that.value);
        break;

      case 53: // "tint"
        value.copy< Shared_TInt > (that.value);
        break;

      case 56: // "tunit"
        value.copy< Shared_TUnit > (that.value);
        break;

      case 60: // typ
        value.copy< Shared_Typ > (that.value);
        break;

      case 50: // "double"
        value.copy< double > (that.value);
        break;

      case 49: // "int"
        value.copy< int > (that.value);
        break;

      case 51: // "var"
      case 52: // "filename"
        value.copy< std::string > (that.value);
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

#line 118 "src/parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< Shared_Exp > ()->string_of_exp(); }
#line 388 "src/parser.yy.cpp" // lalr1.cc:636
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
    #line 27 "src/parser.yy" // lalr1.cc:745
{
  // Initialize the initial location.
  // NOTE: For some reasons unknown, I cannot access the filename when try to print error
  yyla.location.begin.filename = yyla.location.end.filename = &driver.file;
}

#line 508 "src/parser.yy.cpp" // lalr1.cc:745

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
        yylhs.value.build< Shared_Exp > ();
        break;

      case 55: // "tbool"
        yylhs.value.build< Shared_TBool > ();
        break;

      case 54: // "tfloat"
        yylhs.value.build< Shared_TFloat > ();
        break;

      case 53: // "tint"
        yylhs.value.build< Shared_TInt > ();
        break;

      case 56: // "tunit"
        yylhs.value.build< Shared_TUnit > ();
        break;

      case 60: // typ
        yylhs.value.build< Shared_Typ > ();
        break;

      case 50: // "double"
        yylhs.value.build< double > ();
        break;

      case 49: // "int"
        yylhs.value.build< int > ();
        break;

      case 51: // "var"
      case 52: // "filename"
        yylhs.value.build< std::string > ();
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
#line 125 "src/parser.yy" // lalr1.cc:859
    { *ret = yystack_[1].value.as< Shared_Exp > (); }
#line 655 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 3:
#line 129 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<ELit>(true, yystack_[0].value.as< int > (), 0, false); }
#line 661 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 4:
#line 130 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<ELit>(false, 0, yystack_[0].value.as< double > (), false); }
#line 667 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 5:
#line 131 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EBool>(true); }
#line 673 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 6:
#line 132 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EBool>(false); }
#line 679 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 7:
#line 133 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<ELit>(false, 0, 0, true); }
#line 685 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 8:
#line 134 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EVar>(yystack_[0].value.as< std::string > ()); }
#line 691 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 9:
#line 135 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EUnit>(); }
#line 697 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 10:
#line 137 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EFunc>(yystack_[7].value.as< std::string > (), yystack_[5].value.as< Shared_Typ > (), yystack_[2].value.as< Shared_Typ > (), yystack_[0].value.as< Shared_Exp > (), true, yystack_[9].value.as< std::string > ()); }
#line 703 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 11:
#line 139 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EFunc>(yystack_[7].value.as< std::string > (), yystack_[5].value.as< Shared_Typ > (), yystack_[2].value.as< Shared_Typ > (), yystack_[0].value.as< Shared_Exp > (), false, ""); }
#line 709 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 12:
#line 140 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EOperator>(TokenKind::Plus, yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 715 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 13:
#line 141 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EOperator>(TokenKind::Subtract, yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 721 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 14:
#line 142 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EOperator>(TokenKind::Multiply, yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 727 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 15:
#line 143 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EOperator>(TokenKind::Divide, yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 733 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 16:
#line 144 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EComp>(TokenKind::Leq, yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 739 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 17:
#line 145 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EComp>(TokenKind::Less, yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 745 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 18:
#line 146 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EComp>(TokenKind::Equal, yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 751 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 19:
#line 147 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EComp>(TokenKind::Greater, yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 757 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 20:
#line 148 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EComp>(TokenKind::Geq, yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 763 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 21:
#line 149 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EApp>(yystack_[3].value.as< Shared_Exp > (), yystack_[1].value.as< Shared_Exp > ()); }
#line 769 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 22:
#line 150 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EPair>(yystack_[3].value.as< Shared_Exp > (), yystack_[1].value.as< Shared_Exp > ()); }
#line 775 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 23:
#line 151 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EFst>(yystack_[1].value.as< Shared_Exp > ()); }
#line 781 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 24:
#line 152 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<ESnd>(yystack_[1].value.as< Shared_Exp > ()); }
#line 787 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 25:
#line 153 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<ECar>(yystack_[1].value.as< Shared_Exp > ()); }
#line 793 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 26:
#line 154 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<ECdr>(yystack_[1].value.as< Shared_Exp > ()); }
#line 799 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 27:
#line 155 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EEmpty>(yystack_[1].value.as< Shared_Exp > ()); }
#line 805 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 28:
#line 156 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<ECons>(yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 811 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 29:
#line 157 "src/parser.yy" // lalr1.cc:859
    { std::vector<Shared_Exp> v;
                                    yylhs.value.as< Shared_Exp > () = std::make_shared<EList>(v, yystack_[0].value.as< Shared_Typ > ()); }
#line 818 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 30:
#line 159 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<ERef>(yystack_[1].value.as< Shared_Exp > ()); }
#line 824 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 31:
#line 160 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EDeref>(yystack_[1].value.as< Shared_Exp > ()); }
#line 830 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 32:
#line 161 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EAssign>(yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 836 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 33:
#line 162 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<ESeq>(yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 842 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 34:
#line 164 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<ELet>(yystack_[7].value.as< std::string > (), yystack_[5].value.as< Shared_Typ > (), yystack_[2].value.as< Shared_Exp > (), yystack_[0].value.as< Shared_Exp > ()); }
#line 848 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 35:
#line 166 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EIf>(yystack_[8].value.as< Shared_Exp > (), yystack_[5].value.as< Shared_Exp > (), yystack_[1].value.as< Shared_Exp > ()); }
#line 854 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 36:
#line 167 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EWhile>(yystack_[4].value.as< Shared_Exp > (), yystack_[1].value.as< Shared_Exp > (), yystack_[4].value.as< Shared_Exp > ()); }
#line 860 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 37:
#line 168 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = yystack_[1].value.as< Shared_Exp > (); }
#line 866 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 38:
#line 169 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Exp > () = std::make_shared<EDef>(yystack_[4].value.as< std::string > (), yystack_[1].value.as< Shared_Exp > (), yystack_[5].value.as< Shared_Typ > ()); }
#line 872 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 39:
#line 173 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Typ > () = yystack_[0].value.as< Shared_TInt > (); }
#line 878 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 40:
#line 174 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Typ > () = yystack_[0].value.as< Shared_TFloat > (); }
#line 884 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 41:
#line 175 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Typ > () = yystack_[0].value.as< Shared_TBool > (); }
#line 890 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 42:
#line 176 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Typ > () = yystack_[0].value.as< Shared_TUnit > (); }
#line 896 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 43:
#line 177 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Typ > () = std::make_shared<TFunc>(yystack_[2].value.as< Shared_Typ > (), yystack_[0].value.as< Shared_Typ > ()); }
#line 902 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 44:
#line 178 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Typ > () = std::make_shared<TPair>(yystack_[2].value.as< Shared_Typ > (), yystack_[0].value.as< Shared_Typ > ()); }
#line 908 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 45:
#line 179 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Typ > () = std::make_shared<TList>(yystack_[1].value.as< Shared_Typ > ()); }
#line 914 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 46:
#line 180 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Typ > () = std::make_shared<TRef>(yystack_[1].value.as< Shared_Typ > ()); }
#line 920 "src/parser.yy.cpp" // lalr1.cc:859
    break;

  case 47:
#line 181 "src/parser.yy" // lalr1.cc:859
    { yylhs.value.as< Shared_Typ > () = yystack_[1].value.as< Shared_Typ > (); }
#line 926 "src/parser.yy.cpp" // lalr1.cc:859
    break;


#line 930 "src/parser.yy.cpp" // lalr1.cc:859
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


  const signed char parser::yypact_ninf_ = -45;

  const signed char parser::yytable_ninf_ = -1;

  const short int
  parser::yypact_[] =
  {
      -4,   107,    -4,   -45,   -11,   -45,   -45,   -25,   -23,   -44,
     107,   -45,     5,     7,    98,     8,    25,    32,    42,    43,
      44,   -45,   -45,   -45,   -45,   -45,   -45,   -45,    31,   171,
      17,   107,    38,   182,    -4,    10,    11,    40,    70,    -4,
      -4,    71,    19,    -4,    -4,    -4,    -4,    -4,    -4,   -45,
     -45,    -4,    -4,    -4,    -4,    -4,    -4,    -4,    -4,    -4,
      -4,    -4,    -4,    -4,   107,   107,    73,   -45,   -45,    -4,
     222,    74,    75,    48,   -45,   233,   273,   107,   -45,   284,
     324,   335,   375,   386,   426,     0,     0,    92,    92,   123,
     123,   123,   123,   123,   437,   649,   649,   610,    36,    36,
      78,   477,    79,   107,   107,    81,   -45,   -45,    36,   -45,
     -45,   -45,   -45,   -45,    84,   -45,    -4,   -45,    -4,    85,
      87,   107,    -4,   488,   498,    93,    95,    88,   538,   -45,
     105,   107,    -4,    96,   -45,    90,    37,   550,   107,    -4,
      -4,    -4,    89,   590,   649,    17,   600,    -4,   -45,   649
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     0,     0,     7,     0,     5,     6,     0,     0,     0,
       0,     9,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     3,     4,     8,    39,    40,    41,    42,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     1,
       2,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    46,    37,     0,
       0,     0,     0,     0,    47,     0,     0,     0,    45,     0,
       0,     0,     0,     0,     0,    12,    13,    14,    15,    17,
      16,    18,    19,    20,     0,    28,    32,    33,    44,    43,
       0,     0,     0,     0,     0,     0,    23,    24,    29,    25,
      26,    27,    31,    30,     0,    21,     0,    22,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    38,
       0,     0,     0,     0,    36,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    11,     0,    34,     0,    35,    10
  };

  const signed char
  parser::yypgoto_[] =
  {
     -45,   -45,    26,    -1
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,    28,    29,    30
  };

  const unsigned char
  parser::yytable_[] =
  {
      32,    34,    35,     1,    36,    53,    54,    37,     2,    38,
       3,     4,    60,    42,     5,     6,     7,    39,     8,    40,
      43,     9,    64,    10,    64,    11,    12,    13,    33,    14,
      42,    49,    15,    16,    17,    18,    19,    44,    65,    20,
      65,    64,    64,    64,    45,    21,    22,    23,    67,    24,
      25,    26,    27,    78,    46,    47,    48,    65,   140,    65,
      70,    71,    72,    98,    99,    75,    76,    73,    66,    79,
      80,    81,    82,    83,    84,    64,   108,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      64,    65,    64,    64,    64,   101,   100,    77,    74,   105,
     103,   104,   119,   120,    60,     1,    65,   121,    65,    65,
     147,   116,   118,   125,     1,   126,   133,   122,   132,   131,
     127,   135,   138,   139,     0,    10,    51,    52,    53,    54,
     136,    31,    41,     0,    10,    60,     0,   142,     0,   145,
      31,     0,   123,     0,   124,     0,   145,     0,   128,     0,
       0,    24,    25,    26,    27,     0,     0,     0,   137,     0,
      24,    25,    26,    27,     0,   143,   144,   146,     0,     0,
       0,    50,     0,   149,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,     0,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    68,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    61,     0,     0,     0,
       0,     0,    62,    63,    69,     0,     0,    61,     0,     0,
       0,     0,     0,    62,    63,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,   102,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,   106,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    61,     0,     0,
       0,     0,     0,    62,    63,     0,     0,     0,    61,     0,
       0,     0,     0,     0,    62,    63,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,   107,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,   109,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    61,     0,
       0,     0,     0,     0,    62,    63,     0,     0,     0,    61,
       0,     0,     0,     0,     0,    62,    63,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,   110,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    61,
       0,     0,     0,     0,     0,    62,    63,     0,     0,     0,
      61,     0,     0,     0,     0,     0,    62,    63,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,   112,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,   113,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      61,     0,     0,     0,     0,     0,    62,    63,     0,     0,
       0,    61,     0,     0,     0,     0,     0,    62,    63,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,   114,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
     115,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    61,     0,     0,     0,     0,     0,    62,    63,     0,
       0,     0,    61,     0,     0,     0,     0,     0,    62,    63,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
     117,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,     0,    61,     0,     0,     0,     0,     0,    62,    63,
       0,     0,   129,    61,     0,     0,     0,     0,     0,    62,
      63,     0,   130,    61,     0,     0,     0,     0,     0,    62,
      63,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,     0,     0,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   134,    61,   141,     0,     0,     0,     0,    62,
      63,     0,     0,     0,     0,    61,     0,     0,     0,     0,
       0,    62,    63,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,     0,   148,    61,     0,     0,     0,     0,
       0,    62,    63,     0,     0,    61,     0,     0,     0,     0,
       0,    62,    63,     0,     0,    61,     0,     0,     0,     0,
       0,    62,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61
  };

  const short int
  parser::yycheck_[] =
  {
       1,    12,    27,     7,    27,     5,     6,    51,    12,    10,
      14,    15,    12,    14,    18,    19,    20,    12,    22,    12,
      12,    25,     5,    27,     5,    29,    30,    31,     2,    33,
      31,     0,    36,    37,    38,    39,    40,    12,    21,    43,
      21,     5,     5,     5,    12,    49,    50,    51,    10,    53,
      54,    55,    56,    34,    12,    12,    12,    21,    21,    21,
      34,    51,    51,    64,    65,    39,    40,    27,    51,    43,
      44,    45,    46,    47,    48,     5,    77,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
       5,    21,     5,     5,     5,    69,    23,    26,    28,    51,
      26,    26,   103,   104,    12,     7,    21,    26,    21,    21,
      21,    33,    33,    28,     7,    28,    28,    33,    23,    26,
     121,    16,    26,    33,    -1,    27,     3,     4,     5,     6,
     131,    33,    34,    -1,    27,    12,    -1,   138,    -1,   140,
      33,    -1,   116,    -1,   118,    -1,   147,    -1,   122,    -1,
      -1,    53,    54,    55,    56,    -1,    -1,    -1,   132,    -1,
      53,    54,    55,    56,    -1,   139,   140,   141,    -1,    -1,
      -1,     0,    -1,   147,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,    -1,    -1,
      -1,    -1,    41,    42,    32,    -1,    -1,    35,    -1,    -1,
      -1,    -1,    -1,    41,    42,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,    -1,
      -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    35,    -1,
      -1,    -1,    -1,    -1,    41,    42,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,
      -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    35,
      -1,    -1,    -1,    -1,    -1,    41,    42,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,
      35,    -1,    -1,    -1,    -1,    -1,    41,    42,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,
      -1,    35,    -1,    -1,    -1,    -1,    -1,    41,    42,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    -1,    -1,    -1,    -1,    -1,    41,    42,    -1,
      -1,    -1,    35,    -1,    -1,    -1,    -1,    -1,    41,    42,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    -1,    35,    -1,    -1,    -1,    -1,    -1,    41,    42,
      -1,    -1,    34,    35,    -1,    -1,    -1,    -1,    -1,    41,
      42,    -1,    34,    35,    -1,    -1,    -1,    -1,    -1,    41,
      42,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    34,    35,    24,    -1,    -1,    -1,    -1,    41,
      42,    -1,    -1,    -1,    -1,    35,    -1,    -1,    -1,    -1,
      -1,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    -1,    34,    35,    -1,    -1,    -1,    -1,
      -1,    41,    42,    -1,    -1,    35,    -1,    -1,    -1,    -1,
      -1,    41,    42,    -1,    -1,    35,    -1,    -1,    -1,    -1,
      -1,    41,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    35
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     7,    12,    14,    15,    18,    19,    20,    22,    25,
      27,    29,    30,    31,    33,    36,    37,    38,    39,    40,
      43,    49,    50,    51,    53,    54,    55,    56,    58,    59,
      60,    33,    60,    59,    12,    27,    27,    51,    60,    12,
      12,    34,    60,    12,    12,    12,    12,    12,    12,     0,
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    35,    41,    42,     5,    21,    51,    10,    13,    32,
      59,    51,    51,    27,    28,    59,    59,    26,    34,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    60,    60,
      23,    59,    13,    26,    26,    51,    13,    13,    60,    13,
      13,    13,    13,    13,    13,    13,    33,    13,    33,    60,
      60,    26,    33,    59,    59,    28,    28,    60,    59,    34,
      34,    26,    23,    28,    34,    16,    60,    59,    26,    33,
      21,    24,    60,    59,    59,    60,    59,    21,    34,    59
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    57,    58,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    60,
      60,    60,    60,    60,    60,    60,    60,    60
  };

  const unsigned char
  parser::yyr2_[] =
  {
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
      11,    10,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     4,     5,     4,     4,     4,     4,     4,     3,     4,
       4,     4,     3,     3,    10,    11,     7,     3,     6,     1,
       1,     1,     1,     3,     3,     3,     3,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"eof\"", "error", "$undefined", "\"+\"", "\"-\"", "\"*\"", "\"/\"",
  "\"<\"", "\"<=\"", "\"==\"", "\">\"", "\">=\"", "\"(\"", "\")\"",
  "\"NaN\"", "\"if\"", "\"else\"", "\"then\"", "\"true\"", "\"false\"",
  "\"func\"", "\"->\"", "\"let\"", "\"=\"", "\"in\"", "\"rec\"", "\":\"",
  "\"[\"", "\"]\"", "\"()\"", "\"fst\"", "\"snd\"", "\",\"", "\"{\"",
  "\"}\"", "\"::\"", "\"car\"", "\"cdr\"", "\"empty\"", "\"!\"", "\"ref\"",
  "\":=\"", "\";\"", "\"while\"", "\"do\"", "\"end\"", "\"include\"",
  "\"#\"", "\"def\"", "\"int\"", "\"double\"", "\"var\"", "\"filename\"",
  "\"tint\"", "\"tfloat\"", "\"tbool\"", "\"tunit\"", "$accept", "prog",
  "exp", "typ", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  parser::yyrline_[] =
  {
       0,   125,   125,   129,   130,   131,   132,   133,   134,   135,
     136,   138,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     159,   160,   161,   162,   163,   165,   167,   168,   169,   173,
     174,   175,   176,   177,   178,   179,   180,   181
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
#line 1491 "src/parser.yy.cpp" // lalr1.cc:1167
#line 183 "src/parser.yy" // lalr1.cc:1168


// NOTE: Bison's error reporting simply forwards to the driver
void yy::parser::error(const yy::parser::location_type& l, const std::string &m) { driver.error(l, m); }
