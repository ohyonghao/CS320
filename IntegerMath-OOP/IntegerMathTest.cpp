#include "IntegerMathTest.h"
#include "ExprBinaryOperator.h"
#include "ExprValue.h"
#include "Expr.h"
#include "OfInterest.h"
#include <QDebug>

IntegerMathTest::IntegerMathTest(QObject *parent) : QObject(parent)
{

}

void IntegerMathTest::checkResult( Expr* expr, const QString& formula, int value, bool isNumber  ){
    QString stringOut;
    QTextStream sout(&stringOut);

    bool ok{true};
    sout  << *expr;
    int rValue = expr->eval(&ok);
    qInfo() << "Testing: " << formula << "=" << value;
    QCOMPARE(stringOut, formula );
    QCOMPARE(rValue, value);
    QCOMPARE( ok, isNumber );

}

void IntegerMathTest::TestAdd(){

    TestOperator<Add>( 1,  2, "1+2",      1 +   2,  true);
    TestOperator<Add>(-1,  2, "-1+2",    -1 +   2,  true);
    TestOperator<Add>( 1, -2, "1+(-2)",   1 + (-2), true);
    TestOperator<Add>(-1, -2, "-1+(-2)", -1 + (-2), true);

}

void IntegerMathTest::TestSub(){

    TestOperator<Sub>( 1,  2, "1-2",      1 -   2, true);
    TestOperator<Sub>(-1,  2, "-1-2",    -1 -   2, true);
    TestOperator<Sub>( 1, -2, "1-(-2)",   1 - (-2), true);
    TestOperator<Sub>(-1, -2, "-1-(-2)", -1 - (-2), true);

}

void IntegerMathTest::TestMul(){

    TestOperator<Mul>( 1,  2, "1*2",      1 *   2,  true);
    TestOperator<Mul>(-1,  2, "-1*2",    -1 *   2,  true);
    TestOperator<Mul>( 1, -2, "1*(-2)",   1 * (-2), true);
    TestOperator<Mul>(-1, -2, "-1*(-2)", -1 * (-2), true);
    TestOperator<Mul>( 0, -2, "0*(-2)",   0 * (-2), true);

}

void IntegerMathTest::TestDivOK(){
    TestOperator<Div>(   4,  2, "4/2",        4 /    2, true);
    TestOperator<Div>(  -6,  2, "-6/2",      -6 /    2, true);
    TestOperator<Div>(   8, -2, "8/(-2)",     8 / (-2), true);
    TestOperator<Div>( -10, -2, "-10/(-2)", -10 / (-2), true);
    TestOperator<Div>(   0,  1, "0/1",        0       , true);

}

void IntegerMathTest::TestDivKO(){

    TestOperator<Div>(  1,  2, "1/2",      1 /    2, false);
    TestOperator<Div>( -1,  2, "-1/2",    -1 /    2, false);
    TestOperator<Div>(  1, -2, "1/(-2)",   1 / (-2), false);
    TestOperator<Div>( -1, -2, "-1/(-2)", -1 / (-2), false);
    TestOperator<Div>( -1,  0, "-1/0",     0       , false);
}

void IntegerMathTest::TestCombonation(){
    TestOperator<Add,Div,Mul>( 1,  2, "(1+2)/(1*2)",       1, false );
    TestOperator<Add,Div,Mul>( 2,  2, "(2+2)/(2*2)",       1, true  );
    TestOperator<Add,Sub,Mul>( 1,  2, "(1+2)-(1*2)",       1, true  );
    TestOperator<Mul,Div,Mul>( 1, -2, "(1*(-2))/(1*(-2))", 1, true  );
    TestOperator<Mul,Div,Add>( 1,  2, "(1*2)/(1+2)",       0, false  );
}

void IntegerMathTest::TestLongCombination(){
    Expr *expr = new Add(
                    new Mul(
                             new Div(2,1),
                             new Add(
                                 new Add(
                                     new Add(
                                         new Add(
                                             new Sub( 3, 2),
                                             new Mul( 4, 2)
                                          ), // end add
                                          45
                                     ), // end add
                                     -56
                                 ), // end add
                                 new Div( 42, 6)
                              ) // end add
                    ),
                    new Sub( 300, -20 ) // end mul
                ); // end add

    checkResult( expr, "((2/1)*(((((3-2)+(4*2))+45)+(-56))+(42/6)))+(300-(-20))", ((2/1)*(((((3-2)+(4*2))+45)+(-56))+(42/6)))+(300-(-20)), true ); // 330
    delete expr;
}

QTEST_GUILESS_MAIN(IntegerMathTest)
