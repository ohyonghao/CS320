#include "OfInterest.h"
#include <QList>
OfInterest::OfInterest(int value, QObject *parent) :
    QObject(parent),
    val(value)
{
    can<Add>();
    can<Sub>();
    can<Mul>();
    can<Div>();
    interest();
}

void OfInterest::interest( )
{
    foreach( Expr* item, expr ){
        QString stringOut;
        QTextStream sout(&stringOut);
        bool ok{true};
        sout << *item;
        int value = item->eval(&ok);
        expressions.append(values(stringOut,value,ok));
    }
}

const QList<values> OfInterest::ofInterest( int min, int max ){
    QList<values> result;
    foreach( values v, expressions ){
        if( v.isNumber && v.value <= max && v.value >= min )
            result.append(v);
    }
    return result;
}
