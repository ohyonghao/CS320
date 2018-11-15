#include "If.h"

If::If(Expr *expr, Statement *one, Statement *two, QObject* parent):
    Statement{parent},
    expr{expr},
    one{one},
    two{two}
{
    expr->setParent(this);
    one->setParent(this);
    two->setParent(this);
}


QTextStream& If::pp( QTextStream& qout, int depth ) const{
    one->pp( expr->pp(pd(qout, depth) << "if ( ") << " )" << endl, depth + 2);
    return
    two->pp(pd(qout, depth) << "else" << endl, depth + 1 );
}

Statement* If::exec(){
    return expr->exec() ? one->exec() : two->exec();
}
