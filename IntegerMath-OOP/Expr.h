#ifndef EXPR_H
#define EXPR_H

#include <QObject>
#include <QTextStream>

class ExprValue;

class Expr : public QObject
{
    Q_OBJECT
public:
    explicit Expr(QObject *parent = nullptr);

    virtual ~Expr(){}

    // Evaluates the expression
    // Returns the value or NaN if the expression cannot be evaluated
    virtual int eval( bool *ok = nullptr ) const = 0;
    virtual QTextStream& print( QTextStream& qout ) const = 0;
    // Printing
    friend QTextStream& operator<<( QTextStream& qout, const Expr& );

};

#endif // EXPR_H
