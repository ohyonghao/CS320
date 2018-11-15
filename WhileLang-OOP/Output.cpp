#include "Output.h"
#include <QTextStream>

Output::Output(Var* var, QObject *parent) : Statement(parent),
    var{var},
    qout{stdout}
{
    var->setParent(this);
}

QTextStream& Output::pp( QTextStream& qout, int depth ) const{
    return var->pp(pd(qout, depth) << "output " ) << endl;
}

Statement* Output::exec(){
    var->pp(qout) << " = " << var->exec() << endl;
    qout.flush();
    return this;
}
