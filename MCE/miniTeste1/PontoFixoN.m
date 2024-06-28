function [x,i] = PontoFixoN(x0,n,show)
    % Ponto fixo com n iterações

    % define iterator
    i=0;

    % checks for number of arguments
    % logical variable that decides whether or not to show screen output
    % if nothing is specified default to true(show)
    if nargin < 3
        show = true;
    end
    
    % checks for number of arguments
    % if tolerance is not input, default it to 0.00005
    if nargin < 2 
        n = 50; 
    end

    % output check
    if show
        fprintf('Metodo Ponto Fixo\n');
    end

    % main loop
    while(i < n)
        % calculates value of function on point x0
        x = func(x0);

        % calculates relative error of x0
        erro = abs(x-x0)/abs(x);
        
        % equals x0 to x for next iteration
        x0=x;
        % increments iterator
        i=i+1;

    % output check
    if show
        % prints values for that iteration
        fprintf('i = %3d     x = %.10f     erro = %.10f\n', i, x0,erro)
    end
    end
end
