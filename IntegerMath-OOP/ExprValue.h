#ifndef EXPRVALUE_H
#define EXPRVALUE_H
#include "Expr.h"

#include <QObject>
#include <QTextStream>

class ExprValue : public Expr
{
    Q_OBJECT
public:
    ExprValue( int rhs, bool isRhs = false, QObject *parent = nullptr );
    ~ExprValue(){}

    // Evaluates the expression
    // Returns the value or NaN if the expression cannot be evaluated
    int eval( bool *ok = nullptr ) const;

    virtual QTextStream& print( QTextStream& qout ) const;
private:
    bool isRhs = false;
    bool isNumber = false;
    qint32 value;
};

#endif // EXPRVALUE_H
