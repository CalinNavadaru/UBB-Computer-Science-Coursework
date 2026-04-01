clc; clear; close all; format long;

P0 = [0, 0];
P1 = [1, 1];
T0 = [1, 2];
T1 = [-1, 1];

plot_hermite_curve(P0, P1, T0, T1);

function plot_hermite_curve(P0, P1, T0, T1)
t = linspace(0, 1, 200);

h00 = 2*t.^3 - 3*t.^2 + 1;
h10 = t.^3 - 2*t.^2 + t;
h01 = -2*t.^3 + 3*t.^2;
h11 = t.^3 - t.^2;

x = h00 * P0(1) + h10 * T0(1) + h01 * P1(1) + h11 * T1(1);
y = h00 * P0(2) + h10 * T0(2) + h01 * P1(2) + h11 * T1(2);

plot(x, y, 'b-', 'LineWidth', 2); hold on;
plot(P0(1), P0(2), 'ro', 'MarkerFaceColor', 'r');
plot(P1(1), P1(2), 'go', 'MarkerFaceColor', 'g');
quiver(P0(1), P0(2), T0(1), T0(2), 0.3, 'r', 'LineWidth', 1.5);
quiver(P1(1), P1(2), T1(1), T1(2), 0.3, 'g', 'LineWidth', 1.5);
legend('Curba Hermite', 'P0', 'P1', 'Tangenta la P0', 'Tangenta la P1');
title('Cubica Hermite Parametrică');
xlabel('x'); ylabel('y');
axis equal; grid on;
end
