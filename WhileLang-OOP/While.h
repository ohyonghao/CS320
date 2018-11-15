#ifndef WHILE_H
#define WHILE_H

#include <QObject>
#include "Expr.h"
#include "Statement.h"

class While : public Statement
{
    Q_OBJECT
public:
    explicit While(Expr* expr, Statement* statement, QObject *parent = nullptr);

    virtual QTextStream& pp( QTextStream& qout, int depth ) const;
    virtual Statement* exec();
private:
    Expr* expr;
    Statement* statement;
};

#endif // WHILE_H
