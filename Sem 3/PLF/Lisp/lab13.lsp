;apartine(lista: list e: integer)
(defun apartine (lista e)
  (cond
    ((null lista) nil)
    ((equal e (car lista)) t)
    (t (apartine (cdr lista) e))))

;r3(lista: list)
(defun r3 (lista)
  (r3_aux lista ()))

;r3_aux(lista: list rez: list)
(defun r3_aux (lista rez)
  (cond
    ((null lista) rez)
    ((and (atom (car lista)) (not (apartine rez (car lista))))
     (r3_aux (cdr lista) (cons (car lista) rez )))
    ((atom (car lista))
     (r3_aux (cdr lista) rez))
	(t (r3_aux (cdr lista) (r3_aux (car lista) rez)))
	)
)
