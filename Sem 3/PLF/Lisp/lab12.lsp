;r2(lista: list)
(defun r2(lista)
	(r2_aux (invers lista) () 1) 
)

;invers(L: list)
(defun invers (L)
	(invers_aux L ())
)
;invers_aux(L: list Col: list)
(defun invers_aux (L Col)
	(cond
		((null L) Col)
		(T (invers_aux (cdr L) (cons (car L) Col)))
	)
)

;r2_aux(lista: list col: list v: integer)
(defun r2_aux(lista col v)
	
	(cond
		((and (null lista) (equal v 0)) col)
		((and (null lista) (equal v 1)) (cons 1 col)) 
		((and (equal v 1) (equal (car lista) 9)) 
			(r2_aux (cdr lista) (cons 0 col) 1))
		((and (equal v 1) (not (equal (car lista) 9)))
			(r2_aux (cdr lista) (cons (+ (car lista) 1) col) 0))
		(t (r2_aux (cdr lista)(cons (car lista) col) 0))
	)
		
)