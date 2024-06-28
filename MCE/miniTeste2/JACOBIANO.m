function [J] = JACOBIANO(X)
   
    % definição do jacobiano
    J = ones(2,2);
    J(1,1) = 2*X(1);
    J(1,2) = 4*X(2);        % não é preciso porque a matriz é inicializada com 1s
    J(2,1) = 18*X(1);
    J(2,2) = -2*X(2);

end