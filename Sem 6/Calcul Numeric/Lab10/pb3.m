clc; clear; close all; format long;

f = @(x) sin(x);
a = 0; b = pi; tol = 1e-4;

I_simpson = adapt_simpson(f, a, b, tol);
I_trapez  = adapt_trapez(f, a, b, tol);
I_drept   = adapt_dreptunghi(f, a, b, tol);

disp("Simpson:");
disp(I_simpson);
disp("Trapez:");
disp(I_trapez);
disp("Drept:");
disp(I_drept);

function I = adapt_simpson(f, a, b, tol)
    fa = f(a); fb = f(b); fc = f((a + b)/2);
    I = adapt_simpson_step(f, a, b, tol, fa, fc, fb);
end

function I = adapt_simpson_step(f, a, b, tol, fa, fc, fb)
    c = (a + b)/2;
    d = (a + c)/2;
    e = (c + b)/2;
    fd = f(d);
    fe = f(e);

    S1 = (b - a)/6 * (fa + 4*fc + fb);
    S2 = (b - a)/12 * (fa + 4*fd + 2*fc + 4*fe + fb);
    
    if abs(S2 - S1) < tol
        I = S2 + (S2 - S1)/15;
    else
        I = adapt_simpson_step(f, a, c, tol/2, fa, fd, fc) + ...
            adapt_simpson_step(f, c, b, tol/2, fc, fe, fb);
    end
end

function I = adapt_trapez(f, a, b, tol)
    fa = f(a); fb = f(b);
    I = adapt_trapez_step(f, a, b, tol, fa, fb);
end

function I = adapt_trapez_step(f, a, b, tol, fa, fb)
    c = (a + b)/2;
    fc = f(c);

    T1 = (b - a)/2 * (fa + fb);
    T2 = (b - a)/4 * (fa + 2*fc + fb);

    if abs(T2 - T1) < tol
        I = T2;
    else
        I = adapt_trapez_step(f, a, c, tol/2, fa, fc) + ...
            adapt_trapez_step(f, c, b, tol/2, fc, fb);
    end
end

function I = adapt_dreptunghi(f, a, b, tol)
    I = adapt_dreptunghi_step(f, a, b, tol);
end

function I = adapt_dreptunghi_step(f, a, b, tol)
    c = (a + b)/2;
    m = (a + c)/2;
    n = (c + b)/2;

    R1 = (b - a) * f(c);
    R2 = (b - a)/2 * (f(m) + f(n));

    if abs(R2 - R1) < tol
        I = R2;
    else
        I = adapt_dreptunghi_step(f, a, c, tol/2) + ...
            adapt_dreptunghi_step(f, c, b, tol/2);
    end
end

