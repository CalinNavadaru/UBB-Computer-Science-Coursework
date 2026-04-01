clc; clear; close all; format long;

f = @(x) exp(-x.^2);              
x_nodes = linspace(-2, 2, 5);     
x_eval = linspace(-2.5, 2.5, 100);

plotFunctionAndInterpolant(f, x_nodes, x_eval);

function plotFunctionAndInterpolant(f, x_nodes, x_eval)


y_nodes = f(x_nodes);
y_interp = lagrangeInterpolation(x_nodes, y_nodes, x_eval);
y_true = f(x_eval);

figure;
plot(x_eval, y_true, 'b-', 'LineWidth', 2); hold on;
plot(x_eval, y_interp, 'r--', 'LineWidth', 2);
plot(x_nodes, y_nodes, 'ko', 'MarkerFaceColor', 'k');
legend('f(x)', 'L_m f(x)', 'Noduri', 'Location', 'Best');
title('Funcția f și interpolantul Lagrange');
xlabel('x'); ylabel('valoare');
grid on; hold off;
end

function P = lagrangeInterpolation(x_nodes, y_values, x_eval)
n = length(x_nodes);
P = zeros(size(x_eval));

for i = 1:n
    L = ones(size(x_eval));
    for j = 1:n
        if j ~= i
            L = L .* (x_eval - x_nodes(j)) / (x_nodes(i) - x_nodes(j));
        end
    end
    P = P + y_values(i) * L;
end
end
