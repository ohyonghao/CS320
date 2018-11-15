#ifndef VAR_H
#define VAR_H

#include <QObject>
#include "Expr.h"

class Var : public Expr
{
    Q_OBJECT
public:
    explicit Var(QString var, QObject *parent = nullptr);

    QTextStream& pp( QTextStream& qout ) const;
    QString toString() { return var;}
    qint64 exec();
private:
    QString var;
};

#endif // VAR_H
