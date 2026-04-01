t = 0:11;
x = [3, 1.75, 0.90, 0, 0.50, 1.50, 3.25, 4.25, 4.25, 3, 3.75, 6.00];
y = [4, 1.60, 0.50, 0, 1.00, 0.50, 0.50, 2.25, 4.00, 4, 4.25, 4.25];

coef_x = spline_natural(t, x);
coef_y = spline_natural(t, y);

tt = linspace(0, 11, 500);
xx = zeros(size(tt));
yy = zeros(size(tt));

for i = 1:length(tt)
    for j = 1:length(t)-1
        if tt(i) >= t(j) && tt(i) <= t(j+1)
            dt = tt(i) - t(j);
            a = coef_x(j,1); b = coef_x(j,2); c = coef_x(j,3); d = coef_x(j,4);
            xx(i) = a + b*dt + c*dt^2 + d*dt^3;
            a = coef_y(j,1); b = coef_y(j,2); c = coef_y(j,3); d = coef_y(j,4);
            yy(i) = a + b*dt + c*dt^2 + d*dt^3;
            break;
        end
    end
end

figure;
plot(xx, yy, 'b-', x, y, 'ro');
axis equal;
title('Litera de mână definită cu spline parametric');
xlabel('x'); ylabel('y');
grid on;

hold on;
plot(2*xx, yy, 'm--');  % dublare pe axa x
legend('Originală','Puncte','Dublată pe x');


figure;
comet(xx, yy);
title('Animație desenare literă (comet)');
axis equal;
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
