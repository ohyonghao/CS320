#include "ExprValue.h"

ExprValue::ExprValue(const int value, bool isRhs, QObject *parent ):
    Expr( parent ),
    isRhs( isRhs ),
    value( value )
{
}

int ExprValue::eval(bool */*ok*/) const{
    // Since this is a value, just return self
    return this->value;
}


QTextStream& ExprValue::print( QTextStream& qout ) const{
    if( isRhs && value < 0 && this->parent() )
        qout << '(' << this->value << ')';
    else qout << this->value;
    return qout;
}
