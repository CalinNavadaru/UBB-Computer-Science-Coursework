%g

% invers(L:list, LRez: list)
% (i, o) - determinist
invers(L, Rez) :-
	invers_aux([], L, Rez).
% invers_aux(Col:list, L:list, LRez: list) e primul argument e
% colectoarea (i, i, o) – determinist
invers_aux(Col, [], Col).
invers_aux(Col, [H|T], Rez) :-
	invers_aux([H|Col], T, Rez).

%f(L: list, Rez: list)
%calculeaza precedentul
%(i,o), (0,i) - determinist
f([H|T], Rez):-
	invers([H|T], [H1|T1]),
	V is 1,
	faux([H1|T1], V, R1),
	invers(R1, Rez).

%faux(L: list, V: integer, Rez: list)
%calculeaza precedentul unui numar avand numerele pe pozitii opuse
%(i, i, o) - determinist
faux([], _, []):-!.
faux([H|T], V, Rez):-
	V is 1,
	H is 0,
	!,
	faux(T, V, Rez1),
	R = [9 | Rez1],
	Rez = R.

faux([H|T], V, Rez):-
	V is 1,
	\+ H is 0,
	!,
	V1 is 0,
	faux(T, V1, Rez1),
	H1 is H - 1,
	R = [H1 | Rez1],
	Rez = R.

faux([H|T], V, Rez):-
	V is 0,
	!,
	faux(T, V, Rez1),
	R = [H | Rez1],
	Rez = R.
