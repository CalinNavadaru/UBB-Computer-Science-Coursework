clc; clear; close all; format long;
%Taylor_grad_exp_fix(0, -100, 100, 5);
Taylor_ln_grad_fix(0, -0.99, 5, 5);
function Taylor_grad_exp_fix(x0, a, b, n)

    domeniu = linspace(a, b, 100);

    % Funcția obiectiv
    f = @(x) exp(x);

    % Inițializăm polinomul Taylor de grad n în jurul lui x0
    P_n = @(x) 0;
    for k = 0:n
        termen = @(x) ((x - x0).^(k)) / factorial(k);
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
    legend('exp', sprintf('Taylor n=%d', n));
    title(sprintf('Aproximarea Taylor a lui exp în jurul lui x_0 = %.2f', x0));
    grid on;

    % Calculul erorii
    eroare = abs(y_f - y_Pn);
    figure;
    plot(domeniu, eroare, 'k', 'LineWidth', 2);
    xlabel('x'); ylabel('Eroare');
    title('Eroarea de aproximare');
    grid on;
end

function Taylor_ln_grad_fix(x0, a, b, n)

    domeniu = linspace(a, b, 100);

    %initializam functia obiectiv
    f = @(x) log(x + 1);

    %initializam si calculam polinomul Tyalor de grad n
    P_n = @(x) 0;
    for k = 1:n
        termen = @(x) ((x - x0).^k * (-1)^(k + 1)) / k;
        P_n_temp = P_n;
        P_n = @(x) P_n_temp(x) + termen(x);
    end

    %valorile functiei si a polinomului Taylor pe domeniu
    y_f = f(domeniu);
    y_Pn = P_n(domeniu);

    figure;
    plot(domeniu, y_f, 'b', 'LineWidth', 2); hold on;
    plot(domeniu, y_Pn, 'r--', 'LineWidth', 2);
    xlabel('x'); ylabel('f(x)');
    legend('ln(1 + x)', sprintf('Taylor n=%d', n));
    title(sprintf('Aproximarea Taylor a lui ln(1 + x) în jurul lui x_0 = %.2f', x0));
    grid on;

    eroare = abs(y_f - y_Pn);
    figure;
    plot(domeniu, eroare, 'k', 'LineWidth', 2);
    xlabel('x'); ylabel('Eroare');
    title('Eroarea de aproximare');
    grid on;
    
    ln2_taylor = P_n(1);
    ln2_real = log(2);
    disp(P_n);
    fprintf('Aproximare Taylor ln(2) = %.10f\n', ln2_taylor);
    fprintf('Valoare reală ln(2)    = %.10f\n', ln2_real);
    fprintf('Eroare absolută        = %.10e\n', abs(ln2_real - ln2_taylor));
end
