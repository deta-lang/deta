
// Generated from Deta.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"




class  DetaParser : public antlr4::Parser {
public:
  enum {
    Expr = 1, ExprGroup = 2, ExprUnary = 3, ExprBinary = 4, ExprTernary = 5, 
    ValueExpr = 6, UnaryOp = 7, ExprOr = 8, ExprAnd = 9, ExprBitwise = 10, 
    ExprEquality = 11, ExprRelational = 12, ExprShift = 13, ExprAdditive = 14, 
    ExprMultiplicative = 15, ExprExponent = 16, CompoundOperator = 17, MatchCase = 18, 
    MatchCaseKey = 19, GroupStmt = 20, BaseStmt = 21, BodyStmt = 22, BodyStmtContent = 23, 
    ExprStmt = 24, VarAssign = 25, VarDeclStmt = 26, BaseVarDecl = 27, TypeAlias = 28, 
    TypeBase = 29, EnumBase = 30, TypeBody = 31, IfStmt = 32, DoWhileStmt = 33, 
    FnDefStmt = 34, ForStmt = 35, VarStmt = 36, NewStmt = 37, TypeStmt = 38, 
    EnumStmt = 39, MatchStmt = 40, ConstStmt = 41, WhileStmt = 42, BreakStmt = 43, 
    ReturnStmt = 44, DeleteStmt = 45, ImportStmt = 46, ImportName = 47, 
    ImportAlias = 48, ExportStmt = 49, ContinueStmt = 50, AnyAlias = 51, 
    ArrayAlias = 52, ObjectAlias = 53, BaseAlias = 54, Array = 55, Object = 56, 
    ObjectKey = 57, Type = 58, TypeProperty = 59, PersistentProperty = 60, 
    Property = 61, PropertyAccess = 62, DotPropertyAccess = 63, IndexAccess = 64, 
    ForCondition = 65, ForConditionInternal = 66, Annotations = 67, Annotation = 68, 
    FnCall = 69, FnArg = 70, FnParams = 71, FnParam = 72, Range = 73, InclusiveRange = 74, 
    ExclusiveRange = 75, Term = 76, WHOLEPATH = 77, PATH = 78, PATH_CHAR = 79, 
    STRING = 80, CHAR = 81, FLOAT = 82, INT = 83, IDENTIFIER = 84, WS = 85
  };

  enum {
    RuleMain = 0
  };

  DetaParser(antlr4::TokenStream *input);
  ~DetaParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class MainContext; 

  class  MainContext : public antlr4::ParserRuleContext {
  public:
    MainContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    antlr4::tree::TerminalNode *Annotations();
    std::vector<antlr4::tree::TerminalNode *> Expr();
    antlr4::tree::TerminalNode* Expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> BaseStmt();
    antlr4::tree::TerminalNode* BaseStmt(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MainContext* main();


private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

