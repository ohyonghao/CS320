#ifndef EXPRBINARYOPERATOR_H
#define EXPRBINARYOPERATOR_H

#include <QObject>
#include "Expr.h"
#include "ExprValue.h"


class ExprBinaryOperator : public Expr
{
    Q_OBJECT
public:
    ExprBinaryOperator( Expr*, Expr*, const QChar, QObject *parent = nullptr );

    // Evaluates the expression
    // Returns the value or NaN if teh expression cannot be evaluated
    virtual int eval( bool *ok ) const=0;
    ~ExprBinaryOperator(){}

    // Printing
    virtual QTextStream& print( QTextStream& qout ) const;
protected:
    Expr* lhs;
    Expr* rhs;
    const QChar op;
};

/********************************************************************************
 * Class Add
 * ******************************************************************************/

class Add : public ExprBinaryOperator
{
    Q_OBJECT
public:
    explicit Add( Expr* lhs, Expr* rhs, QObject *parent = nullptr ) : ExprBinaryOperator (lhs, rhs, '+', parent){}
    explicit Add(int lhs, int rhs, QObject *parent = nullptr ) : ExprBinaryOperator (new ExprValue(lhs), new ExprValue(rhs, true), '+', parent){}
    explicit Add(Expr * lhs, int rhs, QObject *parent = nullptr ) : ExprBinaryOperator ( lhs, new ExprValue(rhs, true), '+', parent){}
    explicit Add(int lhs, Expr *rhs, QObject *parent = nullptr ) : ExprBinaryOperator (new ExprValue(lhs), rhs, '+', parent){}
    ~Add(){}
    inline int eval( bool *ok ) const{ return lhs->eval(ok) + rhs->eval(ok); }
    //virtual QTextStream& print( QTextStream& qout ) const;
};

/********************************************************************************
 * Class Sub
 * ******************************************************************************/

class Sub : public ExprBinaryOperator
{
    Q_OBJECT
public:
    explicit Sub( Expr* lhs, Expr* rhs, QObject *parent = nullptr ) : ExprBinaryOperator (lhs, rhs, '-', parent){}
    explicit Sub(int lhs, int rhs, QObject *parent = nullptr ) : ExprBinaryOperator (new ExprValue(lhs), new ExprValue(rhs, true), '-', parent){}
    explicit Sub(Expr * lhs, int rhs, QObject *parent = nullptr ) : ExprBinaryOperator ( lhs, new ExprValue(rhs, true), '-', parent){}
    explicit Sub(int lhs, Expr *rhs, QObject *parent = nullptr ) : ExprBinaryOperator (new ExprValue(lhs), rhs, '-', parent){}

    ~Sub(){}
    inline int eval( bool *ok ) const{ return lhs->eval(ok) - rhs->eval(ok); }
    inline const QString Op() const{ return "-";}
    //virtual QTextStream& print( QTextStream& qout ) const;
};

/********************************************************************************
 * Class Mul
 * ******************************************************************************/

class Mul : public ExprBinaryOperator
{
    Q_OBJECT
public:
    explicit Mul( Expr* lhs, Expr* rhs, QObject *parent = nullptr ) : ExprBinaryOperator (lhs, rhs, '*', parent){}
    explicit Mul(int lhs, int rhs, QObject *parent = nullptr ) : ExprBinaryOperator (new ExprValue(lhs), new ExprValue(rhs, true), '*', parent){}
    explicit Mul(Expr * lhs, int rhs, QObject *parent = nullptr ) : ExprBinaryOperator ( lhs, new ExprValue(rhs, true), '*', parent){}
    explicit Mul(int lhs, Expr *rhs, QObject *parent = nullptr ) : ExprBinaryOperator (new ExprValue(lhs), rhs, '*', parent){}
    ~Mul(){}
    inline int eval( bool *ok ) const{ return lhs->eval(ok) * rhs->eval(ok); }
    inline const QString Op() const{ return "*";}
    //virtual QTextStream& print( QTextStream& qout ) const;
};

/********************************************************************************
 * Class Div
 * ******************************************************************************/

class Div : public ExprBinaryOperator
{
    Q_OBJECT
public:
    explicit Div( Expr* lhs, Expr* rhs, QObject *parent = nullptr ) : ExprBinaryOperator (lhs, rhs, '/', parent){}
    explicit Div(int lhs, int rhs, QObject *parent = nullptr ) : ExprBinaryOperator (new ExprValue(lhs), new ExprValue(rhs, true), '/', parent){}
    explicit Div(Expr * lhs, int rhs, QObject *parent = nullptr ) : ExprBinaryOperator ( lhs, new ExprValue(rhs, true), '/', parent){}
    explicit Div(int lhs, Expr *rhs, QObject *parent = nullptr ) : ExprBinaryOperator (new ExprValue(lhs), rhs, '/', parent){}
    ~Div(){}
    int eval( bool *ok ) const;
    inline const QString Op() const{ return "/";}
    //virtual QTextStream& print( QTextStream& qout ) const;
};

#endif // EXPRBINARYOPERATOR_H
