;apartine_aux(lista, e)
;lista - o lista neliniara de atomi
;e - un atom
(defun apartine_aux (lista e)
		(cond
				((equal lista e) (list t))
				((atom lista) nil)
				(t (apply #'append (mapcar #'(lambda (v)
								(apartine_aux v e)) lista
				)
			)
		)
	)	
)
;apartine(lista, e)
;lista - o lista neliniara de atomi
;e - un atom
(defun apartine(lista e) 
		((lambda (v)
				(cond 
					((null v) nil)
					(t t)
				)
		) 
		(apartine_aux lista e)
	)
)