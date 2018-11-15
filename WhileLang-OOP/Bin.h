#ifndef BIN_H
#define BIN_H

#include <QObject>
#include "Expr.h"
#include <QTextStream>


class Bin : public Expr
{
    Q_OBJECT
public:
    Bin(QChar op, Expr*, Expr*, QObject* parent = nullptr);
    virtual QTextStream& pp(QTextStream& qout) const;
    qint64 exec();
private:
    QChar op;
    Expr* lhs;
    Expr* rhs;
};


#endif // BIN_H
