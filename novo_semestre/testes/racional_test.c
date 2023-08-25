int simplifi, rest1, rest2;

    simplifi = 2;
    aux.num = r.num;
    aux.den = r.den;
    while (simplifi < aux.num && simplifi < aux.den){
        rest1 = aux.num % simplifi;
        rest2 = aux.den % simplifi;
        while(!rest1 && !rest2){
            aux.num = aux.num / simplifi;
            aux.den = aux.den / simplifi;
            rest1 = aux.num % simplifi;
            rest2 = aux.den % simplifi;
        }
        simplifi++;
    }
    return aux;
