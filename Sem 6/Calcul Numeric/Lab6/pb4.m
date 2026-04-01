year = [1900 1910 1920 1930 1940 1950 1960 1970 1980 1990 2000 2010]';
pop = [75.995 91.972 105.710 123.200 131.670 150.700 ...
       179.320 203.210 226.510 249.630 281.420 308.790]';
t = year - 1900;

A = [ones(size(t)), t, t.^2, t.^3];
AtA = A' * A;
Atb = A' * pop;
c = gaussElim(AtA, Atb);

tp = [1975; 2015] - 1900;
Ap = [ones(size(tp)), tp, tp.^2, tp.^3];
pred_poly = Ap * c;

ln_pop = log(pop);
Ae = [t, ones(size(t))];
AtAe = Ae' * Ae;
Atlne = Ae' * ln_pop;
sol = gaussElim(AtAe, Atlne);
lambda = sol(1);
K = exp(sol(2));
pred_exp = K * exp(lambda * tp);

fprintf('Model polinomial: Pop(1975) = %.2f, Pop(2015) = %.2f\n', pred_poly(1), pred_poly(2));
fprintf('Model exponential: Pop(1975) = %.2f, Pop(2015) = %.2f\n', pred_exp(1), pred_exp(2));

function x = gaussElim(A, b)
    n = length(b);
    Ab = [A b];
    for i = 1:n
        for j = i+1:n
            m = Ab(j,i) / Ab(i,i);
            Ab(j,:) = Ab(j,:) - m * Ab(i,:);
        end
    end
    x = zeros(n,1);
    for i = n:-1:1
        x(i) = (Ab(i,end) - Ab(i,1:n) * x) / Ab(i,i);
    end
end
