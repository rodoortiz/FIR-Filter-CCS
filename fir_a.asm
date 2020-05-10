
		.global _firFilter
		.global _backPointer

Nw 		.set 101 ;Tamaño del buffer (No. coeficientes)
xb 		.space 16*Nw ;Buffer para datos de entrada (16 bits)
xbf		.long 0
aux		.long 0

_firFilter
		SETC SXM
		MOVW DP, #xb ;Direccionamiento a pagina de memoria donde esta definida xb

		MOV @xb, ACC ;Copia ACC a primer localidad de xb
		MOVL XAR7, #xb ;Apuntador a inicio de xb
		ZAPA

		RPT #Nw-1 ;Ciclo para cálculo del FIR
		|| MAC P,*XAR4++,*XAR7++

		ADDL ACC, P ;Acumula último producto
		SFR	ACC, #15 ;# bits a la derecha para quedar en Q15

		MOVL XAR0, XAR7 ;Guarda última dirección de xb en XAR0

		LRETR ;Devuelve valor de ACC a programa en C

_backPointer
		MOVL XAR7, XAR0 ;Apunta a final de xb con XAR7
		RPT #Nw-1  ;Reacomoda datos, desplazandolos uno, y regresa a inicio de xb
		|| DMOV *--XAR7

		LRETR
