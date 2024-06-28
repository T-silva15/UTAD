function [erro_abs,erro_rel] = ErroCalc(x,x_ap)

% Error Calculation
erro_abs = abs(x-x_ap);
erro_rel = abs(x-x_ap)/abs(x);

% Result Output
fprintf("O erro absoluto é: %.3f\n", erro_abs)
fprintf("O erro relativo é: %.3f\n", erro_rel)
