#ifndef WHILELANGTEST_H
#define WHILELANGTEST_H

#include <QObject>
#include <QTest>
#include <QTextStream>
#include "Expr.h"

class WhileLanguageTest : public QObject
{
    Q_OBJECT
public:
    explicit WhileLanguageTest(QObject *parent = nullptr);

private slots:
    void initTestCase()
    { qDebug("Starting Test Suite"); }
    void TestPrint();
    void TestExecValue();
    void TestExecVar();
    void TestExecIfIf();
    void TestExecIfElse();
    void TestExecCompound();
    void TestExecBin();
    void TestExecWhile();
    void TestExecAssign();
    void TestExecOutput();
    void TestFactorial();

private:

};

#endif // WHILELANGTEST_H
