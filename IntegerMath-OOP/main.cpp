#include <QCoreApplication>
#include <QTextStream>

#include "OfInterest.h"
int main(int /*argc*/, char */*argv*/[])
{
    QTextStream qout(stdout);
    OfInterest oi( 10 );

    foreach( values val, oi.ofInterest( 0, 9 ) ){
        qout << val.formula << "=" << val.value << "\n";
    }


    return 0;
    //return a.exec();
}
