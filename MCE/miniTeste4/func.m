function [y,M] = func(x)
    % y = exp(-x) - x;
    % y = exp(x) - 3*x;
    % y = exp(x)/3;
    % y = -sqrt(exp(x-1));
    % y = x+1+atan(x);
    % y = exp(6*x) + 1.441*exp(4*x) - 0.3330;

    % for i=1:length(x)
    %     if (x(i) >= 0) && (x(i) <= 0.1) 
    %         y = x.^3+1;
    %         M = 1.001;
    %     elseif x(i) > 0.1 && x(i) <= 0.2
    %         y = 1.001+0.03*(x-0.1)+0.3*(x-0.1)^2+2*(x-0.1)^3;
    %         M = 1.009;
    %     elseif x(i) > 0.2 && x(i) <= 0.3
    %         y = 1.009+0.15*(x-0.2)+0.9*(x-0.2)^2+2*(x-0.2)^3;
    %         M = 1.035;
    %     else
    %         y = 0;
    %         M = 0;
    %     end
    % end
    
    %y = x.^3;
    y = (x.^2)+7;
    M = 0;

    %y = -0.25*x.^4+x.^3+2;
    %y = exp(x.^2);
    
    % y = 4.*x.^2-2.*x+2;
    
    % M = 3; % M é o valor máximo da 2ª/4ª derivada, não é usado, DEFINIDO
    % NA FUNÇÂO

end