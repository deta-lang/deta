grammar Deta;

//////////////////////////// Miscellaneous

main: rule* EOF;
rule: annotation+? moduleStmt;
annotation: '@' IDENTIFIER property* | '@' fnCall;

forLoopCondition: (CONST | VAR)? (IDENTIFIER | objectAlias | arrayAlias)

//////////////////////////// Statement Types

moduleStmt: importStmt
    | exportStmt
    | varDefStmt
    | fnDefStmt
    | typeDefStmt
    | enumDefStmt
    ;

blockStmt: ifStmt
    | doWhileStmt
    | forStmt
    | varStmt
    | newStmt
    | matchStmt
    | constStmt
    | whileStmt
    ;

loopBodyStmt: blockStmt
    | breakStmt
    | continueStmt
    ;

typeBodyStmt: varStmt
    | constStmt
    | fnDefStmt
    | initStmt
    ;

stmtAsExpr: fnDefStmt
    | newStmt
    | matchStmt
    | varAssignStmt
    ;

//////////////////////////// Statements

ifStmt:
    IF tupleSingleExpr body
    (ELSE IF tupleSingleExpr body)*
    (ELSE body)?
    ;

// inStmt:
//     value IN value;

doWhileStmt:
    DO body WHILE tupleSingleExpr;

fnDefStmt:
    FN IDENTIFIER? fnParams (MINUSARROW type)? body;

forStmt:
    FOR forLoopCondition body;

varStmt:
    VAR varDefStmt;

newStmt:
    NEW fnCall;

typeDefStmt: typeAliasStmt
    | TYPE IDENTIFIER? (EXTENDS IDENTIFIER property*)? LCURLY typeBodyStmt* RCURLY;

enumDefStmt:
    ENUM IDENTIFIER LCURLY (IDENTIFIER (COMMA IDENTIFIER)*)? RCURLY;

matchStmt:
    MATCH tupleSingleExpr LCURLY (matchKey (COMMA matchKey)* MINUSARROW ((LCURLY value* RCURLY) | value))* RCURLY;

constStmt:
    CONST varDefStmt;

whileStmt:
    WHILE tupleSingleExpr body;

breakStmt:
    BREAK (IDENTIFIER property*)?;

returnStmt:
    RETURN value?;

deleteStmt:
    DELETE IDENTIFIER property*;

importStmt:
      IMPORT LT WHOLEPATH GT (AS importAlias)?
    | IMPORT DQUOTE WHOLEPATH DQUOTE (AS importAlias)?
    | IMPORT IDENTFIIER (AS importAlias)?
    ;

exportStmt:
      EXPORT varStmt
    | EXPORT constStmt
    | EXPORT fnDefStmt
    | EXPORT typeDefStmt
    | EXPORT enumDefStmt
    | EXPORT IDENTIFIER property*
      (AS commonAlias)
    ;

continueStmt:
    CONTINUE (IDENTIFIER property*)?;

// instanceofStmt:
//    value INSTANCEOF IDENTIFIER property*;

varDefStmt: IDENTIFIER QMARK? ((COLON type) | (ASSIGN value) | (COLON type ASSIGN value));

varAssignStmt: (IDENTIFIER | object | array | fnCall) property* COMPOUND_OPERATOR value;

initStmt: INIT fnParams body

//////////////////////////// Expressions

property: DOT IDENTIFIER
    | LBRACK value RBRACK
    ;

range: rangeUnit (INCLRANGE | EXCLRANGE) rangeUnit
    | rangeUnit (INCLRANGE | EXCLRANGE)
    | (INCLRANGE | EXCLRANGE) rangeUnit
    ;

typeUnit: IDENTIFIER
    | FN LPAREN (IDENTIFIER property* (COMMA IDENTIFIER property*)*)? RPAREN (MINUSARROW type)?
    ;

rangeUnit: (IDENTIFIER
    | INT
    | fnCall
    | newStmt
    | object
    | array) property*
    ;

arrayRange: rangeUnit COLON rangeUnit
    | COLON rangeUnit
    | rangeUnit COLON
    | rangeUnit
    | COLON
    ;
    
type: typeUnit (DOT typeUnit)* (BWOR typeUnit (DOT typeUnit)*)*;

array: type LBRACK arrayRange? RBRACK LCURLY (value (COMMA value)*)? RCURLY;

object: (LPAREN type RPAREN)? LCURLY
        (((objectKey QMARK? (COLON type)? ASSIGN value) | constStmt | varStmt | fnDefStmt) (COMMA (objectKey QMARK? (COLON type)? ASSIGN value) | constStmt | varStmt | fnDefStmt)*)?
    RCURLY
    ;

fnCall:
    IDENTIFIER property* LPAREN
        (value (COMMA value)*)?
    RPAREN
    ;



//////////////////////////// Expression Combinator

tupleSingleExpr:
    LPAREN value RPAREN | value;

tupleMultiExpr:
    LPAREN value (COMMA value)* RPAREN | value;

ternaryExpr:
    value QMARK value COLON value;

binaryExpr1:
    binaryExpr2 (OR binaryExpr2)*;

binaryExpr2:
    binaryExpr3 (AND binaryExpr3)*;

binaryExpr3:
    binaryExpr4 ((BWAND | BWOR | BWXOR) binaryExpr4)*;

binaryExpr4:
    binaryExpr5 ((EQ | NEQ) binaryExpr5)*;

binaryExpr5:
    binaryExpr6 ((IN | INSTANCEOF) binaryExpr6)*;

binaryExpr6:
    binaryExpr7 ((LT | GT | LTEQ | GTEQ) binaryExpr7)*;

binaryExpr7:
    binaryExpr8 ((ADD | SUB) binaryExpr8)*;

binaryExpr8:
    binaryExpr9 ((MUL | DIV | MOD) binaryExpr9)*;

binaryExpr9:
    value (EXP value)*;

value:
    tupleMultiExpr | binaryExpr1 | ternaryExpr | term;

term:
      unary? unaryableFactor property*
    | nonunaryableFactor property*
    | varAssignStmt
    ;

unaryableFactor:
      NUMBER | IDENTIFIER
    |  fnCall
    ;

nonunaryableFactor:
      STRING
    | array | object;

//////////////////////////// Utilities



//////////////////////////// Lexer Rules
//////////////////////////// Skip List

WS: [ \n\t\r] -> skip;
COMMENT_SINGLELINE: '//' ~[\n\r]* -> skip;
COMMENT_MULTILINE: '/*' .*? '*/' -> skip;

//////////////////////////// Keywords

AS: 'as';
IF: 'if';
IN: 'in';
DO: 'do';
FN: 'fn';

FOR: 'for';
VAR: 'var';
NEW: 'new';

TYPE: 'type';
ENUM: 'enum';
ELSE: 'else';

MATCH: 'match';
CONST: 'const';
WHILE: 'while';
BREAK: 'break';

RETURN: 'return';
DELETE: 'delete';
IMPORT: 'import';
EXPORT: 'export';

CONTINUE: 'continue';

INSTANCEOF: 'instanceof';

//////////////////////////// Brackeys

LPAREN: '(';
RPAREN: ')';
LBRACK: '[';
RBRACK: ']';
LCURLY: '{';
RCURLY: '}';

//////////////////////////// Operators

ADD: '+';
SUB: '-';
MUL: '*';
DIV: '/';
MOD: '%';
EXP: '**';

BWOR: '|';
BWAND: '&';
BWXOR: '^';
BWNOT: '~';
BWLSH: '<<';
BWRSH: '>>';

LT: '<';
GT: '>';
EQ: '==';
NEQ: '!=';
LTEQ: '<=';
GTEQ: '>=';

OR: '||';
AND: '&&';
NOT: '!';

SPREAD: '...';
EXCLRANGE: '..';
INCLRANGE: '..=';

SEMI: ';';
QMARK: '?';
COLON: ':';

COMPOUND_OPERATOR: '+=' | '-=' | '*=' | '/=' | '%=' | '**='
    | '&=' | '|='
    ;

//////////////////////////// Path

WHOLEPATH: './'? PATH ('/' PATH)*;
PATH: [a-zA-Z0-9_ \t$\(\)\[\]\<\>:\-.]+;

//////////////////////////// Basic

INT: [0-9][0-9_]+?[0-9];
CHAR: '\'' (ESC | ~[\']) '\'';
FLOAT: INT '.' INT | '.' INT;
STRING: '"' (ESC | ~[\\"])* '"';
RSTRING: 'r"' ~["] '"';
IDENTIFIER: [a-zA-Z_][a-zA-Z_0-9]*;

fragment ESC: [ \n\t\r];