#ifndef ASSIGN_H
#define ASSIGN_H

#include <QObject>
#include "Statement.h"
#include "Var.h"
#include "Value.h"

class Assign : public Statement
{
    Q_OBJECT
public:
    Assign(Var* var, Expr* expr, QObject* parent = nullptr);

    QTextStream& pp( QTextStream& qout, int depth = 0 ) const;
    virtual Statement* exec();
private:
    Var* var;
    Expr* expr;
};

#endif // ASSIGN_H
