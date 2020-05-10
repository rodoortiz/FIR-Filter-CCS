
#define samples 31110
#define coefs 101

extern int firFilter(int, int*);
extern void backPointer();

int ynFir[samples] = {0}; //Arreglo para datos de salida
int xn[samples] = {0}; //Arreglo para datos de entrada
int hlp[coefs] = {0}; //Arreglo para coeficientes LP
int hhp[coefs] = {0}; //Arreglo para coeficientes HP
int hbp1[coefs] = {0}; //Arreglo para coeficientes BP1
int hbp2[coefs] = {0}; //Arreglo para coeficientes BP2

void main(void)
{
    int yn, acc;
    int i = 0;

    for(i=0; i<samples; i++) {

        acc = 0; //Acumulador para suma de filtros
        yn = firFilter(xn[i], &hlp[0]); //Calculo del FIR LP
        acc = acc+yn;
        yn = firFilter(xn[i], &hhp[0]); //Calculo del FIR HP
        acc = acc+yn;
        yn = firFilter(xn[i], &hbp1[0]); //Calculo del FIR BP1
        acc = acc+yn;
        yn = firFilter(xn[i], &hbp2[0]); //Calculo del FIR BP2
        acc = acc+yn;

        ynFir[i] = acc; //Guarda valor final de la suma de los filtros

        backPointer(); //Funcion para reacomodo de datos
    }

    while(1) {}
}
