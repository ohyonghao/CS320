#ifndef COMPOUND_H
#define COMPOUND_H

#include <QObject>
#include <QList>
#include "Statement.h"

class Compound : public Statement
{
    Q_OBJECT
public:
    explicit Compound(QList<Statement *> statements, QObject *parent = nullptr);

    virtual QTextStream& pp( QTextStream& qout, int depth ) const;
    virtual Statement* exec();
private:
    QList<Statement*> statements;
};

#endif // COMPOUND_H
