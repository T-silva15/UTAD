function[X,erroCalc] = matrizNewtonN(X0,it)
    format long;
    % X0 é o ponto de partida
    % o sistema não linear está definido no FUNC.m 
    % o seu Jacobiano está definido no JACOBIANO.m

    n = 0;
    erroCalc = 1000;
    fprintf("Metodo de Newton para [%f;%f]\n",X0(1),X0(2));
    while (n < it)
        n = n + 1;
        
        % iteração
        % Xn+1 = Xn - J(X)^-1 * F(X)
        X = X0 - JACOBIANO(X0)\FUNC(X0); 
        
        % calcula erroCalc
         erroCalc = norm(FUNC(X),2); % RESÍDUO DA FUNÇÃO (pelo valor da função) 
        
        % erroCalc = norm(X-X0,2); % ABSOLUTO
        % erroCalc = norm(X-X0,inf); % ABSOLUTO INFINITO
        
        % erroCalc = norm(X-X0,2)/norm(X,2); % RELATIVO
        % erroCalc = norm(X-X0,2)/norm(X,inf); % RELATIVO INFINITO

        
        fprintf("Resultado da iteração %d =  [%f;%f] \n", n, X(1),X(2));

        % iguala Xant ao X para preparar a próxima iteração
        X0 = X;
    end
end