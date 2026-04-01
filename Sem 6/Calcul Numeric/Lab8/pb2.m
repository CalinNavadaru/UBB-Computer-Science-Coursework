clc; clear; close all; format long;

xi = [1.3, 1.6, 1.9];
fi = [0.6200860, 0.4554022, 0.2818186];
fpi = [-0.5220232, -0.5698959, -0.5811571];

x_vals = linspace(1.2, 2.0, 200);


H_vals = hermite_interp(x_vals, xi, fi, fpi);


f_real = interp1(xi, fi, x_vals, 'pchip');

figure;
plot(x_vals, H_vals, 'r-', 'LineWidth', 2); hold on;
plot(x_vals, f_real, 'b--', 'LineWidth', 1.5);
plot(xi, fi, 'ko', 'MarkerFaceColor', 'k');
legend('Interpolare Hermite', 'Interpolare pchip (doar pt comparatie)', 'Noduri');
title('Interpolare Hermite vs funcția originală');
xlabel('x'); ylabel('f(x)');
grid on;

function Hx = hermite_interp(x, xi, fi, fpi)
n = length(xi);
z = zeros(2*n, 1);
Q = zeros(2*n, 2*n);

for i = 1:n
    z(2*i-1) = xi(i);
    z(2*i) = xi(i);
    Q(2*i-1,1) = fi(i);
    Q(2*i,1) = fi(i);
    Q(2*i,2) = fpi(i);
    if i ~= 1
        Q(2*i-1,2) = (Q(2*i-1,1) - Q(2*i-2,1)) / (z(2*i-1) - z(2*i-2));
    end
end

for j = 3:2*n
    for i = j:2*n
        Q(i,j) = (Q(i,j-1) - Q(i-1,j-1)) / (z(i) - z(i-j+1));
    end
end

Hx = zeros(size(x));
for k = 1:length(x)
    xt = x(k);
    term = 1;
    Hx(k) = Q(1,1);
    for i = 1:2*n-1
        term = term * (xt - z(i));
        Hx(k) = Hx(k) + Q(i+1,i+1) * term;
    end
end
end
