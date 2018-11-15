#ifndef VALUE_H
#define VALUE_H
#include "Expr.h"

#include <QObject>
#include <QTextStream>

class Value : public Expr
{
    Q_OBJECT
public:
    Value(qint64 value, QObject *parent = nullptr );
    ~Value(){}

    QTextStream& pp(QTextStream& qout) const;

    qint64 exec();
private:
    qint64 value;
};

#endif // VALUE_H
