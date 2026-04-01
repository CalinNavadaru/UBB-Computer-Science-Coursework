clc; clear; close all; format long;

n = 10;
[x_nodes, w] = chebyshevNodesType2(n);
f = @(x) 1./(1 + 25*x.^2);       
y_nodes = f(x_nodes);
x_eval = linspace(-1, 1, 1000);
y_interp = barycentricInterpolation(x_nodes, y_nodes, x_eval, w);
y_exact = f(x_eval);

plot(x_eval, y_exact, 'b-', x_eval, y_interp, 'r--');
legend('f(x)', 'Interpolare baricentrică');
title('Interpolare baricentrică cu noduri Chebyshev #2');
grid on;


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

function w = barycentricWeights(x)
n = length(x);
w = ones(1, n);
for j = 1:n
    for k = [1:j-1, j+1:n]
        w(j) = w(j) / (x(j) - x(k));
    end
end
end

function [x, w] = chebyshevNodesType1(n)
j = 0:n;
x = cos((2*j + 1) * pi / (2*n + 2));
w = (-1).^j .* sin((2*j + 1) * pi / (2*n + 2));
end

function [x, w] = chebyshevNodesType2(n)
j = 0:n;
x = cos(j * pi / n);
delta = ones(1, n+1);
delta([1 end]) = 0.5;
w = (-1).^j .* delta;
end



