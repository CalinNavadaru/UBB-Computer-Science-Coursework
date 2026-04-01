clc; clear; close all; format long;

x = 13 * pi;
N = 70;
x = mod(x, 2 * pi);
sin_x = taylor_sin(x, N);
cos_x = taylor_cos(x, N);

% Comparatie cu functiile MATLAB standard
sin_exact = sin(x);
cos_exact = cos(x);

disp(sin_x);
disp(cos_x);
disp(sin_exact);
disp(cos_exact);
disp(abs(sin_x - sin_exact));
disp(abs(cos_x - cos_exact));

function s = taylor_sin(x, N)
    % Functie pentru calculul lui sin(x) folosind seria Taylor
    % x - valoarea pentru care se calculeaza sin(x)
    % N - numarul de termeni in serie
    s = 0;
    for n = 0:N-1
        term = ((-1)^n * x^(2*n+1)) / factorial(2*n+1);
        s = s + term;
    end
end

function c = taylor_cos(x, N)
    % Functie pentru calculul lui cos(x) folosind seria Taylor
    % x - valoarea pentru care se calculeaza cos(x)
    % N - numarul de termeni in serie
    c = 0;
    for n = 0:N-1
        term = ((-1)^n * x^(2*n)) / factorial(2*n);
        c = c + term;
    end
end
