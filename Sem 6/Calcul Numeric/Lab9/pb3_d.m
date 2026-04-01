t2 = 0:6;
x2 = [4 3 2 1.5 2 3 4];
y2 = [4 4 3.5 2 0.5 0 0];

coef_x2 = spline_natural(t2, x2);
coef_y2 = spline_natural(t2, y2);

tt2 = linspace(0, 6, 300);
xx2 = zeros(size(tt2));
yy2 = zeros(size(tt2));

for i = 1:length(tt2)
    for j = 1:length(t2)-1
        if tt2(i) >= t2(j) && tt2(i) <= t2(j+1)
            dt = tt2(i) - t2(j);
            a = coef_x2(j,1); b = coef_x2(j,2); c = coef_x2(j,3); d = coef_x2(j,4);
            xx2(i) = a + b*dt + c*dt^2 + d*dt^3;
            a = coef_y2(j,1); b = coef_y2(j,2); c = coef_y2(j,3); d = coef_y2(j,4);
            yy2(i) = a + b*dt + c*dt^2 + d*dt^3;
            break;
        end
    end
end

figure;
plot(xx2, yy2, 'k-', x2, y2, 'ro');
axis equal;
title('Litera "C" desenată cu spline parametric');
grid on;


function coef = spline_natural(x, y)
x = x(:); y = y(:);  
n = length(x);
h = diff(x);

A = zeros(n);
rhs = zeros(n, 1);

A(1,1) = 1;  
A(n,n) = 1;

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