#include "ExprBinaryOperator.h"

ExprBinaryOperator::ExprBinaryOperator(Expr *lhs, Expr *rhs, const QChar op, QObject *parent) :
    Expr(parent),
    lhs(lhs),
    rhs(rhs),
    op(op)
{

    lhs->setParent(this);
    rhs->setParent(this);
}

QTextStream& ExprBinaryOperator::print( QTextStream& qout ) const{
    if(this->parent() != nullptr)
        qout << "(";

    qout << *(this->lhs) << this->op << *(this->rhs);

    if(this->parent() != nullptr)
        qout << ")";
    return qout;
}

int Div::eval( bool *ok ) const{
    // we assume its a number

    bool okok = true;
    int lhresult = lhs->eval(ok);
    okok = okok && *ok;

    int rhresult = rhs->eval(ok);
    *ok = okok && *ok;
    if( rhresult == 0 ){
        *ok = false;
        return 0;
    }else if( *ok && (lhresult % rhresult) ) *ok = false;

    return(lhresult / rhresult );
}
