clc; clear; close all; format long;

f = @(x) sin(x);
a = 0; b = pi; tol = 1e-4;

[R, n] = romberg(f, a, b, tol);

fprintf('Aproximarea: %.10f\n', R(n,n));
disp('Tabelul Romberg:');
disp(R);


function [R, n] = romberg(f, a, b, tol, Nmax)
    if nargin < 5
        Nmax = 10;
    end

    R = zeros(Nmax, Nmax);
    h = b - a;

    R(1,1) = h/2 * (f(a) + f(b));

    for k = 2:Nmax
        h = h / 2;
        sum_term = 0;

        for i = 1:2^(k-2)
            x = a + (2*i - 1)*h;
            sum_term = sum_term + f(x);
        end

        R(k,1) = 0.5 * R(k-1,1) + h * sum_term;

        for j = 2:k
            R(k,j) = (4^(j-1) * R(k,j-1) - R(k-1,j-1)) / (4^(j-1) - 1);
        end

        if abs(R(k,k) - R(k-1,k-1)) < tol
            R = R(1:k, 1:k); 
            n = k;
            return;
        end
    end

    warning('Nu s-a atins toleranța în %d pași.', Nmax);
    R = R(1:Nmax, 1:Nmax);
    n = Nmax;
end

