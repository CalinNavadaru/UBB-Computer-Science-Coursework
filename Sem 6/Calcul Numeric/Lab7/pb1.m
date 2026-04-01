clc; clear; close all; format long;

x_nodes = [0, 1, 2];
y_values = [1, 3, 2];
x_eval = linspace(0, 2, 100);
P = lagrangeInterpolation(x_nodes, y_values, x_eval);
plot(x_eval, P, '-r', x_nodes, y_values, 'bo');
legend('Interpolant', 'Noduri');

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

