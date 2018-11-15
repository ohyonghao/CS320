#include "While.h"

While::While(Expr* expr, Statement* statement, QObject *parent) :
    Statement(parent),
    expr(expr),
    statement{statement}
{
    expr->setParent(this);
    statement->setParent(this);
}

QTextStream& While::pp( QTextStream& qout, int depth ) const{
    return statement->pp( expr->pp(pd(qout,depth) << "while ( " ) << " )" << " do" << endl, depth + 1 );
}

Statement* While::exec(){
    if( expr->exec() ){
        statement->exec();
        this->exec();
    }
    return this;
}
