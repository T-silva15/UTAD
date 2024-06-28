function [Erro , Resultado] = RegraSimpson(a,b,n)
    
    if(mod(n,2) ~= 0)
        fprintf("N tem de ser numero par")
        return;
    end
    
    h = (b-a) / n;
    
    x = a:h:b;
    
    [f,M] = func(x); 
    sumImpar = 0;
    sumPar = 0;
    
    for k = 1:length(x)/2 -1
        sumImpar = sumImpar + f(2*k +1);
    end
    
    for k = 1:length(x)/2 
        sumPar = sumPar + f(2*k);
    end
    Area = (h/3) * ((func(a) + 2*sumImpar + 4*sumPar + func(b)))
    
    %M = 0; % máximo da 4 derivada
    Erro = (h.^4 ./ 180) .* (b-a) .* M; 
    Resultado = Area + Erro;
end