clc; clear; close all; format long;

Taylor_arctan_eroare(0, 0, 1, 1e-5);
approx_arctan_1(1e-5);
function Taylor_arctan_eroare(x0, a, b, eps)

    domeniu = linspace(a, b, 100);
    f = @(x) atan(x);
    y_f = f(domeniu);
    P_n = zeros(size(domeniu));
    eroare = abs(y_f-P_n);
    eroare_maxima = max(eroare);
    grad = 0;
    
    while eroare_maxima > eps
      P_n = P_n + (((-1)^grad) * (domeniu - x0).^(2 * grad + 1)) / (2 * grad + 1);
      eroare = abs(y_f-P_n);
      eroare_maxima = max(eroare);
      grad = grad+1;
    end

    figure;
    plot(domeniu, y_f, 'b', 'LineWidth', 2); hold on;
    plot(domeniu, P_n, 'r--', 'LineWidth', 2);
    xlabel('x'); ylabel('f(x)');
    legend('arctan(x)', sprintf('Taylor n=%d', grad));
    title(sprintf('Aproximarea Taylor a lui arctan(x) în jurul lui x_0 = %.2f', x0));
    grid on;

    figure;
    plot(domeniu, eroare, 'k', 'LineWidth', 2);
    xlabel('x'); ylabel('Eroare');
    title('Eroarea de aproximare');
    grid on;
end
