clc; clear; close all; format long;

f = @(x) exp(-x.^2);
a = 0; b = 1; tol = 1e-6; n = 10;

I_trap = trapez_repetat(f, a, b, n);
I_simp = simpson_repetat(f, a, b, 2*ceil(n/2));  % n par
I_rect = dreptunghi_repetat(f, a, b, n);

I_as = adapt_simpson(f, a, b, tol);
I_at = adapt_trapez(f, a, b, tol);
I_ar = adapt_dreptunghi(f, a, b, tol);
I_aq = adquad(f, a, b, tol);

[R, k] = romberg(f, a, b, tol);
I_rom = R(k,k);

I_quad = quad(f, a, b);    
I_intg = integral(f, a, b); 

fprintf('f(x) = exp(-x^2), interval = [%.1f, %.1f]\n', a, b);
fprintf('-------------------------------\n');
fprintf('Trapez repetat     : %.10f\n', I_trap);
fprintf('Simpson repetat    : %.10f\n', I_simp);
fprintf('Dreptunghi repetat : %.10f\n', I_rect);
fprintf('Adaptiv Simpson    : %.10f\n', I_as);
fprintf('Adaptiv Trapez     : %.10f\n', I_at);
fprintf('Adaptiv Dreptunghi : %.10f\n', I_ar);
fprintf('adquad             : %.10f\n', I_aq);
fprintf('Romberg            : %.10f\n', I_rom);
fprintf('quad()             : %.10f\n', I_quad);
fprintf('integral()         : %.10f\n', I_intg);

function I = trapez_repetat(f, a, b, n)
    h = (b - a) / n;
    x = a + (1:n-1) * h;
    I = (b - a) / (2 * n) * (f(a) + 2 * sum(f(x)) + f(b));
end

function I = dreptunghi_repetat(f, a, b, n)
    h = (b - a) / n;
    x = a + h/2 : h : b - h/2;  
    I = h * sum(f(x));
end

function I = simpson_repetat(f, a, b, n)
    if mod(n, 2) ~= 0
        error('n trebuie sa fie par pentru formula Simpson.');
    end
    h = (b - a) / n;
    x = a:h:b;
    I = h/3 * (f(x(1)) + ...
        4 * sum(f(x(2:2:end-1))) + ...
        2 * sum(f(x(3:2:end-2))) + ...
        f(x(end)));
end

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

function I = adquad(f, a, b, tol)
    fa = f(a);
    fb = f(b);
    c = (a + b)/2;
    fc = f(c);

    I = quadstep(f, a, b, tol, fa, fc, fb);
end

function Q = quadstep(f, a, b, tol, fa, fc, fb)
    h = b - a;
    c = (a + b)/2;
    d = (a + c)/2;
    e = (c + b)/2;

    fd = f(d);
    fe = f(e);

    S1 = h/6 * (fa + 4*fc + fb);

    S2 = h/12 * (fa + 4*fd + 2*fc + 4*fe + fb);

    if abs(S2 - S1) < tol
        Q = S2 + (S2 - S1)/15;
    else
        Qa = quadstep(f, a, c, tol/2, fa, fd, fc);
        Qb = quadstep(f, c, b, tol/2, fc, fe, fb);
        Q = Qa + Qb;
    end
end

function [R, n] = romberg(f, a, b, tol, Nmax)
    if nargin < 5
        Nmax = 10;
    end

    R = zeros(Nmax, Nmax);
    h = b - a;

    R(1,1) = h/2 * (f(a) + f(b));

    for k = 2:Nmax
        h = h / 2;
        sum_term = 0;

        for i = 1:2^(k-2)
            x = a + (2*i - 1)*h;
            sum_term = sum_term + f(x);
        end

        R(k,1) = 0.5 * R(k-1,1) + h * sum_term;

        for j = 2:k
            R(k,j) = (4^(j-1) * R(k,j-1) - R(k-1,j-1)) / (4^(j-1) - 1);
        end

        if abs(R(k,k) - R(k-1,k-1)) < tol
            R = R(1:k, 1:k); 
            n = k;
            return;
        end
    end

    warning('Nu s-a atins toleranța în %d pași.', Nmax);
    R = R(1:Nmax, 1:Nmax);
    n = Nmax;
end