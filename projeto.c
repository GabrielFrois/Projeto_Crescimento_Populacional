#include <stdio.h>
#include <math.h>
#include <string.h>

struct dados{
    char nome[45];
    int periodo;
    int a;
    int b;
    double r;
};

double r(double t){
    return 300 * exp(0.3 * t);
}

double trapezio(int a, int b){
    int xn = b;
    int x0 = a;
    int n = 500;
    double h = (double) (xn - x0) / n;
    double x = x0 + h;
    double soma = 0;

    for(int i = 1; i <= n; i++){
        soma += r(x);
        x += h;
    }
    double p = h * ((r(x0) + r(xn)) / 2 + soma);
    return p;
}

void periodoPorExtenso(int periodo){
    char *extenso[10] = {
        "Um", "Dois", "Tres", "Quatro",
        "Cinco", "Seis", "Sete", "Oito", "Nove", "Dez"
    };
    if(periodo >= 1 && periodo <= 10){
        printf("%s", extenso[periodo - 1]);
    }else{
        printf("%d", periodo);
    }
}

void imprimirRelatorio(struct dados *pesquisadores, int numPesquisadores){
    for(int i = 0; i < numPesquisadores - 1; i++){
        for(int j = 0; j < numPesquisadores - i - 1; j++){
            if(pesquisadores[j].periodo > pesquisadores[j + 1].periodo){
                struct dados temp = pesquisadores[j];
                pesquisadores[j] = pesquisadores[j + 1];
                pesquisadores[j + 1] = temp;
            }
        }
    }
    printf("Relatorio:\n");
    printf("Periodo\tNome Pesquisador\tIntervalo [a.b]\t\tValor Populacional\n");
    for(int i = 0; i < numPesquisadores; i++){
        periodoPorExtenso(pesquisadores[i].periodo);
        printf("\t%s\t\t[%d,%d]\t\t\t%.2f\n", pesquisadores[i].nome, pesquisadores[i].a, pesquisadores[i].b, pesquisadores[i].r);
    }
}

int main(){
    int numPesquisadores;
    struct dados pesquisadores[100];
    int maxPeriodo = 0;
    int minPeriodo = 0;
    double maxPopulacao = 0;
    double minPopulacao = 0;
    char maxNome[45];
    char minNome[45];
    int numPeriodosMaior1500 = 0;

    printf("Informe o numero de pesquisadores:\n");
    scanf("%d", &numPesquisadores);

    for(int i = 0; i < numPesquisadores; i++){
        printf("Pesquisador %d\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]s", pesquisadores[i].nome);
        printf("Periodo: ");
        scanf("%d", &pesquisadores[i].periodo);
        printf("Intervalo [a]: ");
        scanf("%d", &pesquisadores[i].a);
        printf("Intervalo [b]: ");
        scanf("%d", &pesquisadores[i].b);

        pesquisadores[i].r = 1200 + trapezio(pesquisadores[i].a, pesquisadores[i].b);

        if(i == 0){
            maxPeriodo = pesquisadores[i].periodo;
            minPeriodo = pesquisadores[i].periodo;
            maxPopulacao = pesquisadores[i].r;
            minPopulacao = pesquisadores[i].r;
            strcpy(maxNome, pesquisadores[i].nome);
            strcpy(minNome, pesquisadores[i].nome);
        }else{
            if(pesquisadores[i].periodo > maxPeriodo){
                maxPeriodo = pesquisadores[i].periodo;
                strcpy(maxNome, pesquisadores[i].nome);
                maxPopulacao = pesquisadores[i].r;
            }
            if(pesquisadores[i].periodo < minPeriodo){
                minPeriodo = pesquisadores[i].periodo;
                strcpy(minNome, pesquisadores[i].nome);
                minPopulacao = pesquisadores[i].r;
            }
        }
        if(pesquisadores[i].r > 1500){
            numPeriodosMaior1500++;
        }
    }

    printf("Quantidade de periodos com populacao maior que 1500: %d\n", numPeriodosMaior1500);
    printf("Maior periodo populacional: ");
    periodoPorExtenso(maxPeriodo);
    printf(" - Pesquisador: %s - Valor populacional: %.2f\n", maxNome, maxPopulacao);
    printf("Menor periodo populacional: ");
    periodoPorExtenso(minPeriodo);
    printf(" - Pesquisador: %s - Valor populacional: %.2f\n", minNome, minPopulacao);

    imprimirRelatorio(pesquisadores, numPesquisadores);
    return 0;
}
