#ifndef EXPR_H
#define EXPR_H

#include <QObject>
#include <QTextStream>
#include <QHash>

class Value;

class Expr : public QObject
{
    Q_OBJECT
public:
    explicit Expr(QObject *parent = nullptr);

    virtual ~Expr(){}

    // Evaluates the expression
    // Returns the value or NaN if the expression cannot be evaluated
    //virtual int eval( bool *ok = nullptr ) const = 0;
    virtual QTextStream& pp( QTextStream& qout ) const = 0;

    virtual qint64 exec() = 0;

private:
    static QHash<QString, qint64> symbolTable;

public:
    static qint64 getSymbolValue( QString key){return symbolTable[key];}
    static void   setSymbolValue( QString key, qint64 value ){symbolTable[key] = value;}


};
#endif // EXPR_H
