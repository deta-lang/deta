
// Generated from Deta.g4 by ANTLR 4.8


#include "DetaListener.h"

#include "DetaParser.h"


using namespace antlrcpp;
using namespace antlr4;

DetaParser::DetaParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

DetaParser::~DetaParser() {
  delete _interpreter;
}

std::string DetaParser::getGrammarFileName() const {
  return "Deta.g4";
}

const std::vector<std::string>& DetaParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& DetaParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- MainContext ------------------------------------------------------------------

DetaParser::MainContext::MainContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DetaParser::MainContext::EOF() {
  return getToken(DetaParser::EOF, 0);
}

tree::TerminalNode* DetaParser::MainContext::Annotations() {
  return getToken(DetaParser::Annotations, 0);
}

std::vector<tree::TerminalNode *> DetaParser::MainContext::Expr() {
  return getTokens(DetaParser::Expr);
}

tree::TerminalNode* DetaParser::MainContext::Expr(size_t i) {
  return getToken(DetaParser::Expr, i);
}

std::vector<tree::TerminalNode *> DetaParser::MainContext::BaseStmt() {
  return getTokens(DetaParser::BaseStmt);
}

tree::TerminalNode* DetaParser::MainContext::BaseStmt(size_t i) {
  return getToken(DetaParser::BaseStmt, i);
}


size_t DetaParser::MainContext::getRuleIndex() const {
  return DetaParser::RuleMain;
}

void DetaParser::MainContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DetaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMain(this);
}

void DetaParser::MainContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DetaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMain(this);
}

DetaParser::MainContext* DetaParser::main() {
  MainContext *_localctx = _tracker.createInstance<MainContext>(_ctx, getState());
  enterRule(_localctx, 0, DetaParser::RuleMain);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(3);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == DetaParser::Annotations) {
      setState(2);
      match(DetaParser::Annotations);
    }
    setState(8);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == DetaParser::Expr

    || _la == DetaParser::BaseStmt) {
      setState(5);
      _la = _input->LA(1);
      if (!(_la == DetaParser::Expr

      || _la == DetaParser::BaseStmt)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(10);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(11);
    match(DetaParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> DetaParser::_decisionToDFA;
atn::PredictionContextCache DetaParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN DetaParser::_atn;
std::vector<uint16_t> DetaParser::_serializedATN;

std::vector<std::string> DetaParser::_ruleNames = {
  "main"
};

std::vector<std::string> DetaParser::_literalNames = {
};

std::vector<std::string> DetaParser::_symbolicNames = {
  "", "Expr", "ExprGroup", "ExprUnary", "ExprBinary", "ExprTernary", "ValueExpr", 
  "UnaryOp", "ExprOr", "ExprAnd", "ExprBitwise", "ExprEquality", "ExprRelational", 
  "ExprShift", "ExprAdditive", "ExprMultiplicative", "ExprExponent", "CompoundOperator", 
  "MatchCase", "MatchCaseKey", "GroupStmt", "BaseStmt", "BodyStmt", "BodyStmtContent", 
  "ExprStmt", "VarAssign", "VarDeclStmt", "BaseVarDecl", "TypeAlias", "TypeBase", 
  "EnumBase", "TypeBody", "IfStmt", "DoWhileStmt", "FnDefStmt", "ForStmt", 
  "VarStmt", "NewStmt", "TypeStmt", "EnumStmt", "MatchStmt", "ConstStmt", 
  "WhileStmt", "BreakStmt", "ReturnStmt", "DeleteStmt", "ImportStmt", "ImportName", 
  "ImportAlias", "ExportStmt", "ContinueStmt", "AnyAlias", "ArrayAlias", 
  "ObjectAlias", "BaseAlias", "Array", "Object", "ObjectKey", "Type", "TypeProperty", 
  "PersistentProperty", "Property", "PropertyAccess", "DotPropertyAccess", 
  "IndexAccess", "ForCondition", "ForConditionInternal", "Annotations", 
  "Annotation", "FnCall", "FnArg", "FnParams", "FnParam", "Range", "InclusiveRange", 
  "ExclusiveRange", "Term", "WHOLEPATH", "PATH", "PATH_CHAR", "STRING", 
  "CHAR", "FLOAT", "INT", "IDENTIFIER", "WS"
};

dfa::Vocabulary DetaParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> DetaParser::_tokenNames;

DetaParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x57, 0x10, 0x4, 0x2, 0x9, 0x2, 0x3, 0x2, 0x5, 0x2, 0x6, 0xa, 0x2, 
    0x3, 0x2, 0x7, 0x2, 0x9, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0xc, 0xb, 0x2, 
    0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x2, 0x2, 0x3, 0x2, 0x2, 0x3, 0x4, 0x2, 
    0x3, 0x3, 0x17, 0x17, 0x2, 0x10, 0x2, 0x5, 0x3, 0x2, 0x2, 0x2, 0x4, 
    0x6, 0x7, 0x45, 0x2, 0x2, 0x5, 0x4, 0x3, 0x2, 0x2, 0x2, 0x5, 0x6, 0x3, 
    0x2, 0x2, 0x2, 0x6, 0xa, 0x3, 0x2, 0x2, 0x2, 0x7, 0x9, 0x9, 0x2, 0x2, 
    0x2, 0x8, 0x7, 0x3, 0x2, 0x2, 0x2, 0x9, 0xc, 0x3, 0x2, 0x2, 0x2, 0xa, 
    0x8, 0x3, 0x2, 0x2, 0x2, 0xa, 0xb, 0x3, 0x2, 0x2, 0x2, 0xb, 0xd, 0x3, 
    0x2, 0x2, 0x2, 0xc, 0xa, 0x3, 0x2, 0x2, 0x2, 0xd, 0xe, 0x7, 0x2, 0x2, 
    0x3, 0xe, 0x3, 0x3, 0x2, 0x2, 0x2, 0x4, 0x5, 0xa, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

DetaParser::Initializer DetaParser::_init;
