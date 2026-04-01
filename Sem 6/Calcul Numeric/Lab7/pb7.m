clc; clear; close all; format long;

aproximeazaEXPInterpolare();

function aproximeazaEXPInterpolare()
f = @(x) exp(x.^2 - 1);
df5 = @(x) exp(x.^2 - 1) .* (16*x.^5 + 120*x.^3 + 120*x);

x_nodes = 1.0:0.1:1.4;
y_nodes = f(x_nodes);
x_eval = 1.25;

w = barycentricWeights(x_nodes);
f_interp = barycentricInterpolation(x_nodes, y_nodes, x_eval, w);

x = x_eval;
w_prod = prod(x - x_nodes);  
xi_interval = linspace(1.0, 1.4, 1000);
max_f5 = max(abs(df5(xi_interval)));
eroare_max = (max_f5 / factorial(5)) * abs(w_prod);

fprintf('f(1.25) ≈ %.10f (prin interpolare Lagrange)\n', f_interp);
fprintf('Valoare exactă f(1.25) = %.10f\n', f(x_eval));
fprintf('Eroare teoretică maximă estimată: %.2e\n', eroare_max);
fprintf('Eroare reală: %.2e\n', abs(f(x_eval) - f_interp));
end

function w = barycentricWeights(x)
n = length(x);
w = ones(1, n);
for j = 1:n
    for k = [1:j-1, j+1:n]
        w(j) = w(j) / (x(j) - x(k));
    end
end
end

function p = barycentricInterpolation(x, y, xx, w)
numer = zeros(size(xx));
denom = zeros(size(xx));
p = zeros(size(xx));

exactMatch = false(size(xx));  

for j = 1:length(x)
    diff = xx - x(j);
    
    idx = (diff == 0);
    exactMatch(idx) = true;
    
    temp = w(j) ./ diff;
    
    temp(idx) = 0;
    
    numer = numer + temp * y(j);
    denom = denom + temp;
end
p(~exactMatch) = numer(~exactMatch) ./ denom(~exactMatch);

for j = 1:length(x)
    idx = (xx == x(j));
    p(idx) = y(j);
end
end
