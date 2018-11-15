#include "Bin.h"

Bin::Bin(QChar op, Expr* lhs, Expr* rhs, QObject *parent):
    Expr(parent),
    op{op},
    lhs{lhs},
    rhs{rhs}
{
    lhs->setParent(this);
    rhs->setParent(this);
}

QTextStream& Bin::pp( QTextStream& qout ) const{
    return rhs->pp( lhs->pp(qout)  << op );
}

qint64 Bin::exec(){
    switch(op.toLatin1()){
    case '>':
        return( lhs->exec() > rhs->exec());
    case '*':
        return (lhs->exec() * rhs->exec());
    case '/':
        return (lhs->exec() / rhs->exec());
    case '-':
        return (lhs->exec() - rhs->exec());
    case '+':
        return (lhs->exec() + rhs->exec());
    case '!':
        return (lhs->exec() != rhs->exec());
    case '%':
        return (lhs->exec() % rhs->exec());
    case '=':
        return (lhs->exec() == rhs->exec());
    default:
        throw;
    }
}
