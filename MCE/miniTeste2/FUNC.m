function [Y] = FUNC(X)

    % definição das funções (sistema não linear)
    Y = zeros(2,1);
    Y(1) = X(1)^2 + 2*X(2)^2 - 2;
    Y(2) = 9*X(1)^2 - X(2)^2 - 9;

end