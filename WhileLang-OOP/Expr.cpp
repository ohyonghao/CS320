#include "Expr.h"
#include "Value.h"
#include "Bin.h"

Expr::Expr(QObject *parent) : QObject(parent)
{

}

QHash<QString, qint64>Expr::symbolTable;
