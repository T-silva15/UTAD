function [It, Resultado] = RegraSimpsonErro(a,b,Tol)
    %UNTITLED Summary of this function goes here
    %   Detailed explanation goes here
    
    n = 0;
    Erro  = Tol + 1;
    
    while Erro > Tol
        n = n +1 ; 
    
        h = (b-a) / n ;
    
        M = (16+48+12)*exp(1); % M é o valor máximo da quarta derivada
        Erro = (h^4 / 180) * (b-a) * M;
    
    
    end
    
    if(mod(n,2) ~= 0 )
        %porque n tem de ser par
        n = n+1;
    end
    
    It = n;
    
    x = a:h:b;
    
    f = func(x); 
    sumImpar = 0;
    sumPar = 0;
    
    for k = 1:length(x)/2 -1
        sumImpar = sumImpar + f(2*k +1);
    end
    
    for k = 1:length(x)/2 
        sumPar = sumPar + f(2*k);
    end
    
    Area = (h/3) * ( func(a) + 2*sumImpar + 4*sumPar + func(b) );
    Resultado = Area+Erro ;

end