#include "Assign.h"
#include "Var.h"
#include "Value.h"

Assign::Assign(Var *var, Expr *expr , QObject *parent):
    Statement(parent),
    var{var},
    expr{expr}
{
    var->setParent(this);
    expr->setParent(this);
}

QTextStream& Assign::pp( QTextStream& qout, int depth ) const{
    return expr->pp(var->pp( pd(qout, depth) ) << " := " ) << endl;
}

Statement* Assign::exec(){
    Expr::setSymbolValue(var->toString(), expr->exec());
    return this;
}
