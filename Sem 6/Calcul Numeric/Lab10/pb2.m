clc; clear; close all; format long;

f = @(x) sin(x);
a = 0; b = pi;
n = 6;  

grafica_trapez(f, a, b, n);
grafica_simpson(f, a, b, n);

function grafica_trapez(f, a, b, n)
    h = (b - a) / n;
    x = linspace(a, b, 1000);
    y = f(x);

    figure;
    plot(x, y, 'b', 'LineWidth', 1.5); hold on;

    for i = 0:n-1
        xi = a + i * h;
        xf = xi + h;
        fill([xi xf xf xi], [0 0 f(xf) f(xi)], 'r', 'FaceAlpha', 0.3, 'EdgeColor', 'k');
    end

    title('Aproximarea integralei prin formula trapezelor');
    xlabel('x'); ylabel('f(x)');
    grid on;
end

function grafica_simpson(f, a, b, n)
    if mod(n, 2) ~= 0
        error('n trebuie sa fie par pentru Simpson.');
    end

    h = (b - a) / n;
    x = linspace(a, b, 1000);
    y = f(x);

    figure;
    plot(x, y, 'b', 'LineWidth', 1.5); hold on;

    for i = 0:2:n-2
        x0 = a + i*h;
        x1 = x0 + h;
        x2 = x0 + 2*h;
        
        xx = linspace(x0, x2, 100);
        yy = f(x0)*(x2 - xx).*(x1 - xx)/((x2 - x0)*(x1 - x0)) + ...
             f(x1)*(xx - x0).*(x2 - xx)/((x1 - x0)*(x2 - x1)) + ...
             f(x2)*(xx - x0).*(xx - x1)/((x2 - x0)*(x2 - x1));
        fill([xx, fliplr(xx)], [yy, zeros(size(yy))], 'g', 'FaceAlpha', 0.3, 'EdgeColor', 'k');
    end

    title('Aproximarea integralei prin formula Simpson');
    xlabel('x'); ylabel('f(x)');
    grid on;
end

