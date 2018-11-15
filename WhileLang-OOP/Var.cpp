#include "Var.h"

Var::Var(QString var, QObject *parent) : Expr(parent),
    var{var}
{

}

QTextStream& Var::pp( QTextStream& qout ) const{
    return qout << var;
}

qint64 Var::exec(){
    return Expr::getSymbolValue(var);
}
