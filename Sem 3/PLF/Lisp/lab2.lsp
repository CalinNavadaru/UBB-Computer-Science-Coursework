;parcurg_st(arb, nv, nm)
;arb - arbore reprezentat ca si lista de noduri si numar de subarbori.
;nv - nr de varfuri curent din subarborele stang.
;nm - nr de muchii
(defun parcurg_st(arb nv nm)
	(cond
		((null arb) nil)
		((= nv (+ 1 nm)) nil)
		(t (cons (car arb) (cons (cadr arb) (parcurg_st (cddr arb) (+ 1 nv) (+ (cadr arb) nm)))))
	)
)
;parcurg_dr(arb, nv, nm)
;arb - arbore reprezentat ca si lista de noduri si numar de subarbori.
;nv - nr de varfuri curent din subarborele stang.
;nm - nr de muchii
(defun parcurg_dr(arb nv nm)
	(cond
		((null arb) nil)
		((= nv (+ 1 nm)) arb)
		(t (parcurg_dr (cddr arb) (+ 1 nv) (+ (cadr arb) nm)))
	)
)
;stang(arb)
;arb - arbore reprezentat ca si lista de noduri si numar de subarbori.
(defun stang(arb)
	(parcurg_st (cddr arb) 0 0)
)
;drept(arb)
;arb - arbore reprezentat ca si lista de noduri si numar de subarbori.
(defun drept(arb)
	(parcurg_dr (cddr arb) 0 0)
)
;adancime_aux(arb, e, k)
;arb - arbore reprezentat ca si lista de noduri si numar de subarbori.
;e - elementul cautat
;k - nivelul curent (la primul apel trebuie initializat cu 1)
(defun adancime_aux(arb e k)
	(cond
		((null arb) 0)
		((equal (car arb) e) k)
		(t (+ 0 (+ (adancime_aux (stang arb) e (+ k 1)) (adancime_aux (drept arb) e (+ k 1)))))
	)
)
;adancime(arb, e)
;arb - arbore reprezentat ca si lista de noduri si numar de subarbori.
;e - elementul cautat
(defun adancime(arb e)
	(- (adancime_aux arb e 1) 1)
)