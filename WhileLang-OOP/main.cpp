#include <QCoreApplication>
#include <QTextStream>
#include <QList>

#include "Value.h"
#include "Var.h"

#include "Assign.h"
#include "Compound.h"
#include "If.h"
#include "While.h"
#include "Output.h"
#include "Bin.h"
#include "Statement.h"

int main(int /*argc*/, char */*argv*/[])
{
    QTextStream qout(stdout);

    Statement* factorial = new Compound(QList<Statement*>()
                               << new Assign(new Var("n"), new Value(5))
                               << new Assign(new Var("r"), new Value(1))
                               << new While(new Bin('>',new Var("n"), new Value(0)),
                                     new Compound(QList<Statement*>()
                                        << new Assign( new Var("r"), new Bin('*', new Var("r"), new Var("n")))
                                        << new Assign( new Var("n"), new Bin('-', new Var("n"), new Value(1)))
                                   )
                               )
                               << new Output( new Var("r"))
                            );
    factorial->pp(qout);
    factorial->exec();
    delete factorial;
    // In this language, to keep things simple, the following conventions are used:
    // ! means !=
    // = means ==
    // This program produces the sequence from the Collatz Conjecture found on Wikipedia:
    // https://en.wikipedia.org/wiki/Collatz_conjecture
    // with the following rules:
    // If n is even, divide by 2
    // If n is odd, multiply by 3 and add 1
    // Stop when n == 1
    // Print number of steps to reach repeating sequence (4,2,1,...)
    Statement* collatz = new Compound(QList<Statement*>()
                             << new Assign( new Var("n"), new Value(19))
                             << new Assign( new Var("count"), new Value(0) )
                             << new Output( new Var("n"))
                             << new While( new Bin('!', new Var("n"), new Value(1) ),
                                       new Compound(QList<Statement*>()
                                           << new If( new Bin('=', new Bin('%', new Var("n"), new Value(2)), new Value(0) ),
                                                  new Assign( new Var("n"), new Bin('/', new Var("n"), new Value(2))),
                                                  new Assign( new Var("n"), new Bin('+', new Bin( '*', new Var("n"), new Value(3)), new Value(1)))
                                                  )
                                           << new Assign( new Var("count"), new Bin('+', new Var("count"), new Value(1)))
                                           << new Output( new Var("n"))
                                           )
                                    )
                             << new Output( new Var("count"))
                             );
    collatz->pp(qout);
    collatz->exec();
    delete collatz;
    return 0;
}
