function [sol, n] = MetBissInv(a, b, erroPedido)    
    erro = abs(b - a) / 2;
    i = 0;
    c = 0;
    
    fprintf('\nMétodo das Bisseções [%.3f, %.3f]\n\n', a, b)

    % Iterate until the error condition is satisfied
    while erro >= erroPedido && i <= 50
        % Calculate the midpoint
        c = (a + b) / 2;
        % Update the error
        erro = abs(b - a) / 2;
        fprintf('i = %3d     xi = %.10f     erro = %.10f\n', i + 1, c,erro)
        
        % Check the sign of func(a) * func(c)
        if func(a) * func(c) < 0
            % If a and c have the same signs, update b
            b = c;
        else
            % If a and c have opposite signs, update a
            a = c;
        end
        % Update the iteration count
        i = i + 1;
    end
    format long;
    sol = c;
    n = i;
    fprintf("\n\nO resultado foi %.10f e foram necessárias %.0f iterações para obter um erro inferior a %.10f", sol, n, erroPedido);
end
