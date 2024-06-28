% defining function
x=-1:0.01:4;
y1=exp(x);
y2=3*x;

% figure configuration
figure(1)
axis([-1 4 -1 4])
axis equal
grid on
hold on

% plot variations of main function
plot(x,y1,'b', LineWidth=2)
plot(x,y2,'g', LineWidth=2)

% labels main plot and x/y axis
xlabel('Eixo dos x')
ylabel('Eixo dos y')
title Simetrias

