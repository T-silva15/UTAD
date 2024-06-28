function [sol,erro] = MetBissW(a,b,n)
% a e b correspondem ao intervalo
% n corresponde ao numero de iteracoes


% itera n vezes pelo intervalo, aplicando o método novamente
    fprintf('\nMétodo das Bisseções [%.3f,%.3f]\n\n',a,b)
    erroCalc = 0;
    i = 1;
    while i <= n
        % calcula o erro
        erroCalc = abs(b-a)/2;
        % calcula ponto médio
        c = (a+b)/2;
        fprintf('i = %3d   erro = %.10f   xi = %.10f\n',i,erroCalc,c)
        
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
        i = i + 1;
    end
    format long;
    % sol corresponde ao intervalo e as iterações introduzidas
    sol = c;
    % erro calculado sobre o resultado final
    erro = erroCalc;
end
