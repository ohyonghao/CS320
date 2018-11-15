#ifndef STATEMENT_H
#define STATEMENT_H

#include <QObject>
#include <QTextStream>

class Statement : public QObject
{
    Q_OBJECT
public:
    explicit Statement(QObject *parent = nullptr);

    virtual QTextStream& pp( QTextStream& qout, int depth = 0 ) const = 0;
    virtual Statement* exec() = 0;
protected:
    inline QTextStream& pd( QTextStream& qout, int depth ) const{ for( int i = 0; i < depth << 1; i++) qout << " "; return qout;}
};

#endif // STATEMENT_H
