clc; clear; close all; format long;

aproximeazaRadical115();

function aproximeazaRadical115()
f = @(x) sqrt(x);
x_eval = 115;

x_nodes = [100, 110, 120];
y_nodes = f(x_nodes);

w = barycentricWeights(x_nodes);
f_interp = barycentricInterpolation(x_nodes, y_nodes, x_eval, w);

f_exact = f(x_eval);
eroare = abs(f_exact - f_interp);

fprintf('Aproximare sqrt(115) ≈ %.10f\n', f_interp);
fprintf('Valoare exactă sqrt(115) = %.10f\n', f_exact);
fprintf('Eroare absolută = %.2e\n', eroare);

if eroare < 0.0005
    fprintf('Aproximare are 3 zecimale exacte corecte.\n');
else
    fprintf('Aproximarea NU are 3 zecimale exacte. Mărește numărul de noduri.\n');
end
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
