clc; clear; close all; format long;

plotContraexempleInterpolare();

function plotContraexempleInterpolare()
N = [5, 10, 20];  

f_runge = @(x) 1./(1 + x.^2);
f_bernstein = @(x) abs(x);

x_runge = linspace(-5, 5, 1000);
x_bernstein = linspace(-1, 1, 1000);

figure;
for k = 1:length(N)
    n = N(k);

    
    xe = linspace(-5, 5, n+1);
    ye = f_runge(xe);
    we = barycentricWeights(xe);
    fe_interp = barycentricInterpolation(xe, ye, x_runge, we);

    [xc, wc] = chebyshevNodesType2(n);
    yc = f_runge(5 * xc); 
    fc_interp = barycentricInterpolation(5 * xc, yc, x_runge, wc);

    subplot(3,2,2*k-1);
    plot(x_runge, f_runge(x_runge), 'k', x_runge, fe_interp, 'r--');
    title(sprintf('Runge - echidistante, n = %d', n));
    legend('f', 'Interpolare'); grid on;

    subplot(3,2,2*k);
    plot(x_runge, f_runge(x_runge), 'k', x_runge, fc_interp, 'b--');
    title(sprintf('Runge - Cebîșev II, n = %d', n));
    legend('f', 'Interpolare'); grid on;
end

figure;
for k = 1:length(N)
    n = N(k);
    xe = linspace(-1, 1, n+1);
    ye = f_bernstein(xe);
    we = barycentricWeights(xe);
    fe_interp = barycentricInterpolation(xe, ye, x_bernstein, we);

    [xc, wc] = chebyshevNodesType2(n);
    yc = f_bernstein(xc);
    fc_interp = barycentricInterpolation(xc, yc, x_bernstein, wc);

    subplot(3,2,2*k-1);
    plot(x_bernstein, f_bernstein(x_bernstein), 'k', x_bernstein, fe_interp, 'r--');
    title(sprintf('Bernstein - echidistante, n = %d', n));
    legend('f', 'Interpolare'); grid on;

    subplot(3,2,2*k);
    plot(x_bernstein, f_bernstein(x_bernstein), 'k', x_bernstein, fc_interp, 'b--');
    title(sprintf('Bernstein - Cebîșev II, n = %d', n));
    legend('f', 'Interpolare'); grid on;
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

function [x, w] = chebyshevNodesType2(n)
j = 0:n;
x = cos(j * pi / n);
delta = ones(1, n+1);
delta([1 end]) = 0.5;
w = (-1).^j .* delta;
end

