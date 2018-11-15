#ifndef INTEGERMATHTEST_H
#define INTEGERMATHTEST_H

#include <QObject>
#include <QTest>
#include <QTextStream>
#include "Expr.h"

class IntegerMathTest : public QObject
{
    Q_OBJECT
public:
    explicit IntegerMathTest(QObject *parent = nullptr);

private slots:
    void initTestCase()
    { qDebug("Starting Test Suite"); }
    void TestAdd();
    void TestSub();
    void TestMul();
    void TestDivOK();
    void TestDivKO();
    void TestCombonation();
    void TestLongCombination();

private:
    template <class T>
    void TestOperator(int lhs, int rhs, const QString& formula, int value, bool isNumber );

    template <class T, class R, class S>
    void TestOperator( int lhs, int rhs, const QString& formula, int value, bool isNumber );

    void checkResult(Expr* , const QString &formula, int value, bool isNumber);
};

template <class T>
void IntegerMathTest::TestOperator( int lhs, int rhs, const QString& formula, int value, bool isNumber ){
    Expr *expr = new T(lhs, rhs);
    checkResult( expr, formula, value, isNumber );
    delete expr;
}

template <class L, class M, class R>
void IntegerMathTest::TestOperator(int lhs, int rhs, const QString &formula, int value, bool isNumber ){
    Expr *expr = new M( new L(lhs, rhs), new R(lhs,rhs));
    checkResult( expr, formula, value, isNumber );
    delete expr;
}
#endif // INTEGERMATHTEST_H
