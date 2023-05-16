#define cima 20
#define baixo 10

struct data{
	int dia;
	int mes;
	int ano;
};

struct bolo{
    char tipo;
    struct data d;
};

struct tortinha{
    struct data d;
    int dia_consumo;
};

struct frigobar{
    struct bolo *b[cima];
    struct tortinha *t[baixo];
};

struct frigobar criaFrigobar(){

}