clc; clear; close all; format long;

approximeazaPopulatiaSUA();

function approximeazaPopulatiaSUA()
ani = [1960, 1970, 1980, 1990, 2000, 2010];
populatie = [179.323, 203.212, 226.505, 249.633, 281.422, 308.786];

x_query = [1975, 2018];
w = barycentricWeights(ani);
y_approx = barycentricInterpolation(ani, populatie, x_query, w);

fprintf('Populația aproximativă în 1975: %.3f milioane\n', y_approx(1));
fprintf('Populația aproximativă în 2018: %.3f milioane\n', y_approx(2));
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
