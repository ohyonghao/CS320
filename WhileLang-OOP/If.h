#ifndef IF_H
#define IF_H

#include <QObject>
#include "Expr.h"
#include "Statement.h"

class If : public Statement
{
public:
    If(Expr* expr, Statement* one, Statement* two, QObject *parent = nullptr);

    virtual QTextStream& pp( QTextStream& qout, int depth ) const;
    virtual Statement* exec();
private:
    Expr* expr;
    Statement* one;
    Statement* two;
};

#endif // IF_H
