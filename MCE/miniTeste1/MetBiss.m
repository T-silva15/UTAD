function [sol] = MetBiss(a,b,n)
% a e b correspondem ao intervalo
% n corresponde ao numero de iteracoes


% itera n vezes pelo intervalo, aplicando o método novamente
    fprintf('\nMétodo das Bisseções [%.3f,%.3f]\n\n',a,b)
    for i = 1:n
        % calcula ponto médio
        c = (a+b)/2;
        fprintf('i = %3d     xi = %.10f\n',i,c)
        
        % verifica sinal de f(a)*f(c)

        if func(a)*func(c) < 0
            % caso a e c tenham sinais contrários
            % b assume o valor de c (meio do intervalo)
            b = c;
        else
            % caso a e c tenham sinais iguais
            % sabemos que b terá sinal oposto
            % logo a assumer o valor de c (meio do intervalo)
            a = c;
        end
    end
    format long;
    sol = c;
end
