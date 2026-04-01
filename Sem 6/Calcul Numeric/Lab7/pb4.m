clc; clear; close all; format long;

f = @(x) sin(x);                
x_nodes = linspace(0, pi, 5);   
x_point = pi/4;                

fx_interp = approximateAtPointLagrange(f, x_nodes, x_point);
fx_exact = f(x_point);

fprintf('Interpolare: f(%.4f) ≈ %.8f\n', x_point, fx_interp);
fprintf('Valoare exactă: f(%.4f) = %.8f\n', x_point, fx_exact);
fprintf('Eroare: %.2e\n', abs(fx_exact - fx_interp));


function fx_approx = approximateAtPointLagrange(f, x_nodes, x_point)
y_nodes = f(x_nodes);
fx_approx = lagrangeInterpolation(x_nodes, y_nodes, x_point);
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
