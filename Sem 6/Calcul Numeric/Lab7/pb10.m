clc; clear; close all; format long;

aproximeazaSinCos5();

function aproximeazaSinCos5()
x_nodes = [0, pi/6, pi/4, pi/3, pi/2];

y_sin = [0, 1/2, sqrt(2)/2, sqrt(3)/2, 1];

y_cos = [1, sqrt(3)/2, sqrt(2)/2, 1/2, 0];

x_deg = 5;
x_rad = x_deg * pi / 180;

w_sin = barycentricWeights(x_nodes);
sin_approx = barycentricInterpolation(x_nodes, y_sin, x_rad, w_sin);

w_cos = barycentricWeights(x_nodes);
cos_approx = barycentricInterpolation(x_nodes, y_cos, x_rad, w_cos);

sin_exact = sin(x_rad);
cos_exact = cos(x_rad);

fprintf('sin(5°) ≈ %.10f (exact: %.10f, eroare: %.2e)\n', sin_approx, sin_exact, abs(sin_approx - sin_exact));
fprintf('cos(5°) ≈ %.10f (exact: %.10f, eroare: %.2e)\n', cos_approx, cos_exact, abs(cos_approx - cos_exact));
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


