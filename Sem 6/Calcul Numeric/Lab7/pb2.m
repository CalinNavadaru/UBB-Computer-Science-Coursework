clc; clear; close all; format long;

x_nodes = linspace(-1, 1, 4); 
plotLagrangeBasis(x_nodes);

function plotLagrangeBasis(x_nodes)

n = length(x_nodes);
x_plot = linspace(min(x_nodes)-0.1, max(x_nodes)+0.1, 1000);
L = zeros(n, length(x_plot));

for k = 1:n
    L_k = ones(size(x_plot));
    for j = 1:n
        if j ~= k
            L_k = L_k .* (x_plot - x_nodes(j)) / (x_nodes(k) - x_nodes(j));
        end
    end
    L(k, :) = L_k;
end

figure;
hold on;
colors = lines(n);
legend_entries = cell(1, n);
for k = 1:n
    plot(x_plot, L(k, :), 'LineWidth', 2, 'Color', colors(k, :));
    legend_entries{k} = sprintf('\\ell_{%d}(x)', k-1); % salvăm textul pentru legendă
end
title('Polinoamele fundamentale Lagrange', 'Interpreter', 'latex');
xlabel('x', 'Interpreter', 'latex');
ylabel('$\ell_k(x)$', 'Interpreter', 'latex');
legend(legend_entries, 'Interpreter', 'latex');
grid on;
hold off;
end
