
// Generated from Deta.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"
#include "DetaParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by DetaParser.
 */
class  DetaListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterMain(DetaParser::MainContext *ctx) = 0;
  virtual void exitMain(DetaParser::MainContext *ctx) = 0;


};

