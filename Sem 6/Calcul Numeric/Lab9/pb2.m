clc; clear; close all; format long;

x = [0, pi/4, pi/2, 3*pi/4, pi];
y = sin(x);
fp_start = cos(0);      
fp_end   = cos(pi);    

coef = spline_complet(x, y, fp_start, fp_end);

xx = linspace(0, pi, 100);
yy = zeros(size(xx));

for i = 1:length(xx)
    for j = 1:length(x)-1
        if xx(i) >= x(j) && xx(i) <= x(j+1)
            dx = xx(i) - x(j);
            a = coef(j,1);
            b = coef(j,2);
            c = coef(j,3);
            d = coef(j,4);
            yy(i) = a + b*dx + c*dx^2 + d*dx^3;
            break;
        end
    end
end

plot(xx, yy, 'b-', x, y, 'ro', xx, sin(xx), 'g--')
legend('Spline complet','Puncte nod','sin(x)')
title('Test spline complet pentru sin(x)')
xlabel('x'); ylabel('y');
grid on;


function coef = spline_complet(x, y, fp_start, fp_end)
x = x(:); y = y(:);
n = length(x);
h = diff(x);

A = zeros(n);
rhs = zeros(n, 1);

A(1,1) = 2*h(1);
A(1,2) = h(1);
rhs(1) = 3*((y(2)-y(1))/h(1) - fp_start);

A(n,n-1) = h(n-1);
A(n,n) = 2*h(n-1);
rhs(n) = 3*(fp_end - (y(n)-y(n-1))/h(n-1));

for i = 2:n-1
    A(i, i-1) = h(i-1);
    A(i, i)   = 2*(h(i-1)+h(i));
    A(i, i+1) = h(i);
    rhs(i) = 3*((y(i+1)-y(i))/h(i) - (y(i)-y(i-1))/h(i-1));
end

c = A \ rhs;

a = y(1:n-1);
b = zeros(n-1, 1);
d = zeros(n-1, 1);

for i = 1:n-1
    d(i) = (c(i+1) - c(i)) / (3*h(i));
    b(i) = (y(i+1) - y(i))/h(i) - h(i)*(2*c(i)+c(i+1))/3;
end

coef = [a, b, c(1:n-1), d];
end
