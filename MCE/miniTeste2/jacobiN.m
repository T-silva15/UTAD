function [Xant,erroCalc] = jacobiN(A,B,n)
    format long;
    % função usa o método de jacobi para descobrir a solução da equação 
    % representada pelas matrizes 
    
    % verifica se A tem inversa (determinante é diferente de 0)
    % verifica se determinante é 0 ou muito próximo (menor que 1*10^-10)
    if abs(det(A)) <= 1*10^(-10)
        fprintf("Matriz 'A' não tem inversa! (det(A) == 0)\n");
        return
    end
    
    % calculo das diagonais e triangulares de A
    D = diag(diag(A));
    L = tril(-A,-1);
    U = triu(-A,1);
    
    % D^-1*(L+U)
    M = D\(L+U);
    % D^-1*B
    N = D\B;
    
    % raio espetral
    rho = max(abs(eig(M)));
    
    if rho >= 1
        fprintf("O Método é divergente! (rho >= 1)\n");
        return
    end
    
    
    % definição do iterador
    it = 0;
    
    % definição do ponto inicial de iteração
    %Xant = zeros(length(B),1);
    Xant = [0;1];
    
    % inicializar erro
    erroCalc = 1000;
    while (it <= n)
        it = it + 1;
    
        % calcula solução
        X = M*Xant+N; 
    
        % calcula erroCalc
        % erroCalc = norm(A*X-B,2); % RESÍDUO DA FUNÇÃO (pelo valor da função) 
        % erroCalc = norm(X-Xant,2); % ABSOLUTO
        % erroCalc = norm(X-Xant,inf); % ABSOLUTO INFINITO
        
         erroCalc = norm(X-Xant,2)/norm(X,2); % RELATIVO
        % erroCalc = norm(X-Xant,2)/norm(X,inf); % RELATIVO INFINITO
        
        % iguala X anterior ao X para a próxima iteração
        Xant = X;
    end
end
