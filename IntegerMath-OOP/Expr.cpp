#include "Expr.h"
#include "ExprValue.h"
#include "ExprBinaryOperator.h"

Expr::Expr(QObject *parent) : QObject(parent)
{

}

QTextStream& operator<<( QTextStream & qout, const Expr& rhs ){
    return rhs.print( qout );
}
