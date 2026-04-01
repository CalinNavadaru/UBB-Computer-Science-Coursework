clc; clear; close all; format long;

solve_problem7();

function solve_problem7()
    eps_tol = 1e-9;
    n = 1;
    prev_val = NaN;

    fprintf('n\tAproximare\t\tEroare\n');

    val_exact = sqrt(2) * gamma(1/4) * sqrt(pi) / gamma(3/4);

    while true
        [x, A] = gauss_quadrature('legendre', 50000);

        fx = (pi / 4) ./ sqrt( sin( (pi / 4) * (x + 1) ) );

        I = sum(A .* fx);
        err = abs(I - val_exact);
        
        fprintf('%d\t%.12f\t%.2e\n', n, I, err);
        if ~isnan(prev_val)
            delta = abs(I - prev_val);
            if n > 1 && delta < eps_tol
                fprintf('\nValoare finală: %.12f\n', I);
                fprintf('Număr minim de noduri pentru 9 zecimale: %d\n', n);
            break;
            end
        end

        prev_val = I;
        n = n + 1;
    end
end

function [x, A] = gauss_quadrature(type, n, varargin)
    alpha = zeros(n, 1);
    beta = zeros(n, 1);

    switch lower(type)
        case 'legendre'
            for k = 1:n
                if k == 1
                    beta(k) = 2; 
                else
                    beta(k) = 1 / (4 - 1 / ((k - 1)^2)); 
                end
            end
            beta = sqrt(beta(2:end));
        
        case 'chebyshev1'
            beta(1) = pi;
            for k = 2:n
                if k == 2
                    beta(k) = 0.5;
                else
                    beta(k) = 0.25;
                end
            end
            beta = sqrt(beta(2:end));

        case 'chebyshev2'
            beta(1) = 0.5 * pi;
            for k = 2:n
                beta(k) = 0.25;
            end
            beta = sqrt(beta(2:end));

        case 'jacobi'
            if length(varargin) < 2
                error('Jacobi requires parameters alpha and beta.');
            end
            a = varargin{1};
            b = varargin{2};
            for k = 0:n-1
                alpha(k+1) = (b^2 - a^2) / ((2*k + a + b) * (2*k + a + b + 2));
            end
            beta(1) = 2^(a + b + 1) * gamma(a + 1) * gamma(b + 1) / ...
                      ((a + b + 1) * gamma(a + b + 1));
            for k = 2:n
                k1 = k - 1;
                num = 4*k1*(k1 + a)*(k1 + b)*(k1 + a + b);
                den = (2*k1 + a + b - 1)*(2*k1 + a + b)^2*(2*k1 + a + b + 1);
                beta(k) = num / den;
            end
            beta = sqrt(beta(2:end));

        case 'laguerre'
            mu = 0;
            if ~isempty(varargin)
                mu = varargin{1};
            end
            for k = 1:n
                alpha(k) = 2*k - 1 + mu;
                if k == 1
                    beta(k) = gamma(1 + mu);
                else
                    beta(k) = (k - 1)*(k - 1 + mu);
                end
            end
            beta = sqrt(beta(2:end));

        case 'hermite'
            for k = 1:n
                alpha(k) = 0;
                if k == 1
                    beta(k) = sqrt(pi);
                else
                    beta(k) = 0.5*(k - 1);
                end
            end
            beta = sqrt(beta(2:end));

        otherwise
            error('Tip de cuadratură necunoscut.');
    end

    J = diag(alpha) + diag(beta, 1) + diag(beta, -1);

    [V, D] = eig(J);
    x = diag(D);
    [x, idx] = sort(x);
    V = V(:, idx);

    if strcmpi(type, 'laguerre')
        mu = 0;
        if ~isempty(varargin)
            mu = varargin{1};
        end
        A = gamma(1 + mu) * (V(1, :)').^2;
    elseif strcmpi(type, 'hermite')
        A = sqrt(pi) * (V(1, :)').^2;
    else
        A = 2 * (V(1, :)').^2;
    end
end
