#include "WhileLangTest.h"
#include "Bin.h"
#include "Value.h"
#include "Expr.h"
#include "Statement.h"
#include "Compound.h"
#include "Assign.h"
#include "While.h"
#include "Output.h"
#include "If.h"

#include <QDebug>

#include <QTextStream>

WhileLanguageTest::WhileLanguageTest(QObject *parent) : QObject(parent)
{

}

void WhileLanguageTest::TestPrint(){
    QString expected("begin\n  n := 5\n  r := 1\n  while ( n>0 ) do\n    begin\n      r := r*n\n      n := n-1\n    end\n  output r\nend\n");
    QString result;
    QTextStream qout(&result);

    Statement* factorial = new Compound(QList<Statement*>()
                               << new Assign(new Var("n"), new Value(5))
                               << new Assign(new Var("r"), new Value(1))
                               << new While(new Bin('>',new Var("n"), new Value(0)),
                                     new Compound(QList<Statement*>()
                                        << new Assign( new Var("r"), new Bin('*', new Var("r"), new Var("n")))
                                        << new Assign( new Var("n"), new Bin('-', new Var("n"), new Value(1)))
                                   )
                               )
                               << new Output( new Var("r"))
                            );
    factorial->pp(qout);

    QCOMPARE(result, expected);
}

void WhileLanguageTest::TestExecValue(){
    Value* result = new Value(5);
    qint64 expected = 5;
    QCOMPARE(result->exec(),expected);
}

void WhileLanguageTest::TestExecVar(){
    qint64 expected = 4;
    Assign* var = new Assign( new Var("n"), new Value(expected) );
    var->exec();
    qint64 result = Expr::getSymbolValue("n");
    QCOMPARE(result, expected );
}

void WhileLanguageTest::TestExecIfIf(){
    Statement *expected = new Output( new Var("r"));
    Statement *ifelse = new Output( new Var("n"));
    Statement *statement = new If(new Value(1),
                                  expected,
                                  ifelse);
    Statement *result = statement->exec();
    QCOMPARE(result, expected);
}

void WhileLanguageTest::TestExecIfElse(){
    Statement *ifif = new Output( new Var("r"));
    Statement *expected = new Output( new Var("n"));
    Statement *statement = new If(new Value(0),
                                  ifif,
                                  expected);
    Statement *result = statement->exec();
    QCOMPARE(result, expected);
}

void WhileLanguageTest::TestExecAssign(){
    qint64 expected = 533;
    Statement* assign = new Assign(new Var("x"), new Value(expected));
    assign->exec();
    QCOMPARE(Expr::getSymbolValue("x"),expected);
}

void WhileLanguageTest::TestExecCompound(){
    qint64 nExpected = 5;
    qint64 xExpected = 6;
    Statement* compound = new Compound(QList<Statement*>()
                               << new Assign( new Var("n"), new Value(nExpected))
                               << new Assign( new Var("x"), new Value(xExpected))
                               );
    compound->exec();
    qint64 nResult = Expr::getSymbolValue("n");
    qint64 xResult = Expr::getSymbolValue("x");

    QCOMPARE(nResult,nExpected);
    QCOMPARE(xResult,xExpected);
}

void WhileLanguageTest::TestExecBin(){
    qint64 gtTExpected = 1;
    qint64 gtFExpected = 0;
    qint64 mulExpected = 10;
    qint64 subExpected = -3;
    qint64 mulVarExpected = -30;

    Statement* compound = new Compound(QList<Statement*>()
                                << new Assign( new Var("gtT"), new Bin( '>', new Value(5), new Value(4)))
                                << new Assign( new Var("gtF"), new Bin( '>', new Value(4), new Value(5)))
                                << new Assign( new Var("mul"), new Bin( '*', new Value(2), new Value(5)))
                                << new Assign( new Var("sub"), new Bin( '-', new Value(2), new Value(5)))
                                << new Assign( new Var("mulVar"), new Bin( '*', new Var("mul"), new Var("sub")))
                              );
    compound->exec();
    QCOMPARE(Expr::getSymbolValue("gtT"),gtTExpected);
    QCOMPARE(Expr::getSymbolValue("gtF"),gtFExpected);
    QCOMPARE(Expr::getSymbolValue("mul"),mulExpected);
    QCOMPARE(Expr::getSymbolValue("sub"),subExpected);
    QCOMPARE(Expr::getSymbolValue("mulVar"),mulVarExpected);
}

void WhileLanguageTest::TestExecWhile(){
    qint64 rStart = 2;
    qint64 rExpected = 64;
    Statement* compound = new Compound(QList<Statement*>()
                                   << new Assign( new Var("r"), new Value(rStart))
                                   << new Assign( new Var("i"), new Value(0))
                                   << new While( new Bin('>', new Value(5), new Var("i")),
                                          new Compound(QList<Statement*>()
                                                << new Assign( new Var("i"), new Bin( '+', new Var("i"), new Value(1)))
                                                << new Assign( new Var("r"), new Bin('*', new Var("r"), new Value(2)))
                                              )
                                          )
                                   );
    compound->exec();
    QCOMPARE(Expr::getSymbolValue("r"),rExpected);
}

void WhileLanguageTest::TestExecOutput(){
    QString result;
    Output *output = new Output(new Var("r"));
    output->setOutputDevice(&result);
    Statement* statement = new Compound( QList<Statement *>()
                            << new Assign(new Var("r"), new Value(4))
                            << output
                        );
    statement->exec();
    QString expected = "r = 4\n";
    QCOMPARE(result,expected);
}

void WhileLanguageTest::TestFactorial(){
    QString result;
    Output *output = new Output(new Var("r"));
    output->setOutputDevice(&result);

    Statement* factorial = new Compound(QList<Statement*>()
                               << new Assign(new Var("n"), new Value(5))
                               << new Assign(new Var("r"), new Value(1))
                               << new While(new Bin('>',new Var("n"), new Value(0)),
                                     new Compound(QList<Statement*>()
                                        << new Assign( new Var("r"), new Bin('*', new Var("r"), new Var("n")))
                                        << new Assign( new Var("n"), new Bin('-', new Var("n"), new Value(1)))
                                   )
                               )
                               << output
                            );
    factorial->exec();
    QString expected = "r = 120\n";
    QCOMPARE(result, expected);
}


QTEST_GUILESS_MAIN(WhileLanguageTest)
