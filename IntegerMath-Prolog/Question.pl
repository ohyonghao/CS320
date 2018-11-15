% Our facts:
interest(X,Y,X+Y).
interest(X,Y,X-Y).
interest(X,Y,X*Y).
interest(X,Y,X/Y):- divisable(X,Y).
% Our rule on division:
divisable( NUM, DEN):- 
    not(NUM=[]), not(DEN=[]), % blocks array creation from invalid expression
    EVAL is DEN, % eval D to determine if 0
    not(EVAL=0), 
    NUM mod DEN =:= 0.
% our expressions engine
build(VECTOR,VALUE):-
    setof(EXPRESSION, build(VECTOR, EXPRESSION, VALUE), LIST),
    print(LIST, VALUE).
% produces our five branches
build(VECTOR, EXPRESSION, VALUE):-
    append(V, U, VECTOR),
    expr(V, U, EXPRESSION),
    VALUE is EXPRESSION.
% compute the expressions
expr([], [R], R).
expr([],      [RH|RT], EXPRESSION):-
    expr([], RT, A),
    interest(RH, A, EXPRESSION).
expr([L],     [],      L).
expr([LH|LT], [],      EXPRESSION):-
    expr(LT, [], A),
    interest(A, LH, EXPRESSION).
expr([LH|LT], [RH|RT], EXPRESSION):-
    expr([LH|LT], [], A),
    expr([], [RH|RT], B),
    interest(B,A,EXPRESSION).

% The key is to ask the right question
% this predicate helps by asking for all
% answers to the question down to 0
run(_, LOWER, UPPER):- UPPER < LOWER,!.
run(VECTOR, LOWER, UPPER):- 
    UPPER >= LOWER,
    build(VECTOR,UPPER),
    NEWUPPER is UPPER - 1,!,
    run(VECTOR,LOWER,NEWUPPER).
% In case a number has no solution, skip it
run(VECTOR, LOWER, UPPER):-
    UPPER >= LOWER,
    NEWUPPER is UPPER - 1,!,
    run(VECTOR, LOWER, NEWUPPER).

% print all items in a list
print([],_).
print( [EXPRESSION|TAIL], VALUE ):-
    write(EXPRESSION),write("="),write(VALUE),nl,
    print(TAIL, VALUE).

:- begin_tests(build).
test(build1,[nondet]):-
    V=[4],
    build(V,E,4),
    E=4.
test(build2,[nondet]):-
    V=[1,2],
    build(V,E,2),
    E=2*1.
test(build3,[nondet]):-
    V=[1,2,3],
    build(V,E,4),
    E=2+3-1.
test(build4,[nondet]):-
    V=[1,2,3,4],
    build(V,E,10),
    E=1+(2+(3+4)).
test(expr,[nondet, blocked("Takes way too long to find an answer, if it will...")]):-
    V=[10,10,10,10],
    build(VECTOR,(10+10)/(10+10),1),
    V = VECTOR.
:- end_tests(build).
:- begin_tests(interest).
test(add,[nondet]):-
    interest(X,Y,10+10),
    X=10,
    Y=10,
    interest(X,Y,Z),
    Z=10+10.
test(divisable):-
    divisable(10,2).
test(indivisible,[fail]):-
    divisable(10,0).
:- end_tests(interest).
