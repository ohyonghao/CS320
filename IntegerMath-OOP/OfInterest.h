#ifndef OFINTEREST_H
#define OFINTEREST_H

/*
 * Consider an arithmetic expression (called "of interest") constructed by four occurrences of the number
 * 10, e.g.: (10+10)/(10+10). The value of this expression is 1. Can you construct another expression of
 * interest whose value is 2? What about 3?
 *
 * Code a program that determines which digits are the values of one such expression. Your program should
 * execute the following intermediate steps: (1) construct all the expressions of interest and (2) print
 * any expression whose value is between 0 and 9.
 *
 * A simple (and general) solution constructs any expression of interest with any number of operands, e.g.,
 * all the expressions with the numbers 1, 2, 3 and 4 such as (1-2)*(3-4). To this aim, let X be the set of
 * operands of an expression. Divide X into two parts Y and Z, there are many ways and you consider all.
 * Construct the expressions for Y and Z and join them with an arithmetic operator,  there are many ways and
 * you consider all.
 *
 * Remember that expressions in which a divisor is not a factor of its dividend have no value. This should be
 * handled by the code of assignment 1. For your information, the number of expressions of interest is 320
 * (like this course!): in any expression there are 3 operators, 5 is the Catalan number of 3. There are 5
 * binary trees with 3 nodes, thus 5*4^3 is the number of distinct expressions. Some of these expressions have
 * no value according to our convention.
 *
 * Submit your code as for problem 1 above.
 */

#include <QObject>
#include <QList>
#include "Expr.h"
#include "ExprValue.h"
#include "ExprBinaryOperator.h"
struct values{
    values(QString formula, int value, bool isNumber): formula(formula), value(value), isNumber(isNumber){}
    QString formula;
    int value;
    bool isNumber;
};

class OfInterest : public QObject
{
    Q_OBJECT
public:
    explicit OfInterest(int val, QObject *parent = nullptr);
    const QList<values>& allValues(){ return expressions; }
    const QList<values> ofInterest(int min, int max );

private:
    int val;
    QList<values> expressions;
    QList<Expr*> expr;
    void interest( );

    template<class X>
    void can( );

    template<class X, class Y>
    void can( );

    template<class X, class Y, class Z>
    void can( );
};

// Cascading templates will produce all the variants we need
template <class X>
void OfInterest::can(){
    can<X, Add>( );
    can<X, Sub>( );
    can<X, Mul>( );
    can<X, Div>( );
}

template <class X, class Y>
void OfInterest::can(){
    can<X, Y, Add>( );
    can<X, Y, Sub>( );
    can<X, Y, Mul>( );
    can<X, Y, Div>( );
}

// This one puts each final expression into the list
// Class could be easily modified to take any four numbers
template <class X, class Y, class Z>
void OfInterest::can( ){
    expr.append( new X( new Y( val, val ), new Z( val, val ) ) ); // _-_
    expr.append( new X( new Y( new Z( val, val ), val ), val ) ); // ///
    expr.append( new X( new Y( val, new Z( val, val ) ), val ) ); // /_
    expr.append( new X( val, new Y( new Z( val, val ), val ) ) ); // \/
    expr.append( new X( val, new Y( val, new Z( val, val ) ) ) ); // \_
}
#endif // OFINTEREST_H
