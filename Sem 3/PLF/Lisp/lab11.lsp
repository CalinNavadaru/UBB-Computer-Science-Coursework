;r1(lista: list k: integer)
(defun r1(lista k)
	(r1_aux lista k 1) 
)

;r1_aux(lista: list k: integer v: integer)
(defun r1_aux(lista k v)
	(cond
		((null lista) nil)
		((equal k v) (r1_aux (cdr lista) k (+ v 1)))
		(t (cons (car lista) (r1_aux (cdr lista) k (+ v 1))))
	)
)