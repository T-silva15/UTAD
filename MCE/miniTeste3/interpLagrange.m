function px = interpLagrange(X,Y,x)

    % X é a matriz das abcissas dos pontos 
    % Y é a matriz das ordenadas dos pontos
    % x é o ponto do qual queremos a estimativa do y -> px
    
    % verifica se método pode ser usado
    if length(X) ~= length(Y)
        fprintf("Vetores de dimensões diferentes!\n");
        return;
    end    
    if x > max(X) || x < min(X)
        fprintf("x inserido fora dos pontos da matriz X(extrapolação)!\n");
        return;
    end
    
    % inicializa polinómios  
    l = ones(length(X),1);
    px = 0;

    for i = 1: length(X)
        for j = 1 : length(X)
            if (i ~= j)
                l(i) = l(i) * (x-X(j))/(X(i)-X(j)); 
            end
        end
        px = px + Y(i)*l(i);
    end
end