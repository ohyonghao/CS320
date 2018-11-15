#include "Value.h"

Value::Value( qint64 value, QObject *parent ):
    Expr( parent ),
    value( value )
{
}

QTextStream& Value::pp( QTextStream& qout ) const{

    return qout << value;
}

qint64 Value::exec(){
    return this->value;
}
