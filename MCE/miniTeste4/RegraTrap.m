function [Resultado,Erro] = RegraTrap(a,b,n)
    % a é a primeira abcissa
    % b é a segunda abcissa
    % n é o número de intervalos do método
    
    % calculo do h
    h = (b-a) / n;
    
    x = a+h:h:b-h;
    
    
    Area = (h/2) * (func(a) + 2*sum(func(x)) + func(b));
    
    M = 1; % M é o valor máximo da segunda derivada
    
    Erro = (h^2 / 12) * (b-a) * M; 
    Resultado = Area + Erro;
end