clc; clear; close all; format long;

solve_problem3();

function solve_problem3()
    n = 10;

    k = 1:n;
    xk = cos((2*k - 1) * pi / (2*n));  

    Ak = pi / n * ones(1, n);

    fx = xk .* exp(-xk.^2);

    I = sum(Ak .* fx);

    fprintf('Valoarea aproximativă a integralei: %.10f\n', I);
end
