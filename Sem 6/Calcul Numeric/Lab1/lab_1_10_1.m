clc; clear; close all; format long;

x = linspace(-0.1, 0.1, 100);
y = f_expresie(x);

plot(x, y, 'r', 'LineWidth', 2);
xlabel('x'); ylabel('f(x)');
title('Funcția f(x) calculată precis');
grid on;

function y = f_expresie(x)
    y = zeros(size(x)); 
    
    small_x = abs(x) < 1e-2; 
    y(small_x) = 1/2 + x(small_x)/6 + x(small_x).^2/24;
    
    normal_x = ~small_x; 
    y(normal_x) = (exp(x(normal_x)) - 1 - x(normal_x)) ./ x(normal_x).^2;
end
