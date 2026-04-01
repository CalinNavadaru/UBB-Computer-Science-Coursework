clc; clear; close all; format long;


f = @(x) sin(x);
a = 0; b = pi; tol = 1e-6;

I = adquad(f, a, b, tol);
fprintf('Rezultat cu adquad: %.10f\n', I);


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
