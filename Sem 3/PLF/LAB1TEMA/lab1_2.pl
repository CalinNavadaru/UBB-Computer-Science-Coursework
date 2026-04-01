%perechi(E: element, L1: list, Rez:list)
%(i,i,o), (o, o, i), (i, o, i) - determinist

perechi(E, [], []):-!.
perechi(E, [H|T], [[E, H] | Rez]):-
    perechi(E, T, Rez).

ali([], L2, L2):-!.
ali([H|T], Rez, [H | Rez2]):-
	H \== [],
        !,
	ali(T, Rez, Rez2).

%multime(l: list, g: list, rez: list)
%(i,i,o) - determinist
%(i,i,i) - determinist
%(i,o,i) - determinist
%(o,i,i) - determinist
multime([],L2, L2):-!.
multime(L1, [], L1):-!.
multime([H|T], L2, [H|T2]):-
    \+ member(H, L2),
    !,
    multime(T, L2, T2).

multime([H|T], L2, T2):-
    member(H, L2),
    !,
    multime(T, L2, T2).

%gen_perechi(L: list, Rez: list)
%(i, o) - determinist
gen_perechi([], []):-!.
gen_perechi([H], [[H]]):-!.
gen_perechi([H1, H2], [[H1, H2]]):-!.
gen_perechi([H|T], Rez2):-
    perechi(H, T, R),
    gen_perechi(T, Rez),
    multime(R, Rez, Rez2).




