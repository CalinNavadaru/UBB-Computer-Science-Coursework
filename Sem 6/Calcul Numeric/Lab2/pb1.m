clc; clear; close all; format long;
disp(eps)
disp(realmax)
disp(realmin)

epsilon = 1.0;
while (epsilon + 1.0) ~= 1.0
    epsilon_prev = epsilon;
    epsilon = epsilon / 2;
end
epsilon = epsilon_prev;
disp(epsilon)

v = 1.0;
while v * 2 < Inf
    v = v * 2;
end
disp(v)

smallest_normalized = 2^(1 - 1023);
disp(smallest_normalized);
v1 = 1.0;
while v1 / 2 > 0
    v1 = v1 / 2;
end
disp(v1)

v2 = smallest_normalized * eps;
disp(v2)