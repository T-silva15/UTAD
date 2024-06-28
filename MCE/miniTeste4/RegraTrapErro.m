function [n,Resultado] = RegraTrapErro(a,b,Tol)
    %a + b
    
    n = 0;
    Erro  = Tol + 1;
    
    while Erro > Tol
        n = n +1 ; 
        h = (b-a) / n ;
    
        M = 3; % M é o valor máximo da segunda derivada
        Erro = (h^2 / 12) * (b-a) * M;
    
    end
    x = a+h:h:b-h;
    Area = (h/2) * (func(a) + 2*sum(func(x)) + func(b));
    
    Resultado = Area + Erro;
end