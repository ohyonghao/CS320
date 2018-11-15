#ifndef OUTPUT_H
#define OUTPUT_H

#include <QObject>
#include "Var.h"
#include "Statement.h"

class Output : public Statement
{
    Q_OBJECT
public:
    explicit Output(Var* var, QObject *parent = nullptr);

    virtual QTextStream& pp( QTextStream& qout, int depth ) const;
    virtual Statement* exec();
    void setOutputDevice( QString* out ){qout.setString(out);}
private:
    Var* var;
    QTextStream qout;

};

#endif // OUTPUT_H
