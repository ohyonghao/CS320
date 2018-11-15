#include "Compound.h"

Compound::Compound(QList<Statement *> statements, QObject *parent) :
    Statement(parent),
    statements{statements}
{
    foreach( Statement* statement, statements){
        statement->setParent(this);
    }
}


QTextStream& Compound::pp( QTextStream& qout, int depth ) const{
    pd(qout, depth ) << "begin" << endl;
    foreach( Statement* statement, statements ){
        statement->pp(qout, depth + 1);
    }
    pd(qout, depth) << "end" << endl;
    return qout;
}

Statement* Compound::exec(){
    foreach( Statement* statement, statements){
        statement->exec();
    }
    return this;
}
