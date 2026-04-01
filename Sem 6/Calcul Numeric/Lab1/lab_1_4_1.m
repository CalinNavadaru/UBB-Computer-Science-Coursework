clc; clear; close all; format long;

Taylor_grad_erf_fix(1, 2, 5, 50);
function Taylor_grad_erf_fix(x0, a, b, n)

    domeniu = linspace(a, b, 100);

    % Funcția obiectiv
    f = @(x) erf(x);

    % Inițializăm polinomul Taylor de grad n în jurul lui x0
    P_n = @(x) 0;
    for k = 0:n-1
        termen = @(x) ((-1)^k * (2/sqrt(pi)) * (x - x0).^(2*k + 1)) / ((2*k + 1) * factorial(k));
        P_n_temp = P_n;  
        P_n = @(x) P_n_temp(x) + termen(x);
    end
    % Valoarea funcției și a aproximării Taylor pe domeniu
    y_f = f(domeniu);
    y_Pn = P_n(domeniu);

    % Plotăm funcția și polinomul Taylor
    figure;
    plot(domeniu, y_f, 'b', 'LineWidth', 2); hold on;
    plot(domeniu, y_Pn, 'r--', 'LineWidth', 2);
    xlabel('x'); ylabel('f(x)');
    legend('erf', sprintf('Taylor n=%d', n));
    title(sprintf('Aproximarea Taylor a lui erf în jurul lui x_0 = %.2f', x0));
    grid on;

    % Calculul erorii
    eroare = abs(y_f - y_Pn);
    figure;
    plot(domeniu, eroare, 'k', 'LineWidth', 2);
    xlabel('x'); ylabel('Eroare');
    title('Eroarea de aproximare');
    grid on;
end

