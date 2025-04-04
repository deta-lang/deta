
// Generated from Deta.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"
#include "DetaListener.h"


/**
 * This class provides an empty implementation of DetaListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  DetaBaseListener : public DetaListener {
public:

  virtual void enterMain(DetaParser::MainContext * /*ctx*/) override { }
  virtual void exitMain(DetaParser::MainContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

