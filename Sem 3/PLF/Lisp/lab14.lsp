;apartine(lista: list e: integer)
(defun apartine(lista e)
	(cond
		((null lista) nil)
		((equal e (car lista)) t)
		(t (apartine (cdr lista) e))
	)
)

;r4(lista: list)
(defun r4(lista)
	(cond
		((null lista) t)
		((apartine (cdr lista) (car lista)) nil)
		(t (r4 (cdr lista)))
	)
)