clc; clear; close all; format long;

solve_problem4();

function solve_problem4()
    n = 10;
    k = 1:n;

    xk = cos(k * pi / (n + 1));

    Ak = (pi / (n + 1)) * (sin(k * pi / (n + 1))).^2;

    fx = exp(-xk.^2);

    I_approx = sum(Ak .* fx);

    exact = integral(@(x) sqrt(1 - x.^2) .* exp(-x.^2), -1, 1);

    fprintf('Aproximare: %.10f\n', I_approx);
    fprintf('Valoare exactă numerică: %.10f\n', exact);
    fprintf('Eroare absolută: %.2e\n', abs(I_approx - exact));
end