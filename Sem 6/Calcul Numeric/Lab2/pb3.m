clc; clear; close all; format long;

sin_c = my_sin_pade(10,10, pi);
cos_c = my_cos_pade(10,10, pi/2);
disp(sin_c);
disp(cos_c);
disp(abs(sin(pi) - sin_c));
disp(abs(cos(pi/2) - cos_c));

function R = my_sin_pade(m, k, x)
    % Aproximare Padé [m/k] a functiei sin
    % m - gradul numaratorului
    % k - gradul numitorului
    % x - punctele la care evaluam
    x = mod(x + pi, 2 * pi) - pi;
    c = zeros(m+k+1, 1);    
    for p = 0:m+k
        if mod(p, 4) == 1
            c(p+1) = 1 / factorial(p); % sin(0) = 0, dar coeficienții impari sunt nenuli
        elseif mod(p, 4) == 3
            c(p+1) = -1 / factorial(p); % -sin(x)
        else
            c(p+1) = 0;
        end
    end
    
    % Construim sistemul pentru coeficientii numitorului
    b = zeros(m+k+1, 1);  % Facem b suficient de lung și completăm cu 0
    b(1) = 1; % Primul coeficient este fixat la 1
    if k > 0
        C = toeplitz(c(m+1:m+k), c(m+1:-1:m-k+2));
        bv = -c(m+(1:k)+1);
        
        if cond(C) > 1e12
             %warning("Matricea Toeplitz este aproape singulară. Folosesc pinv().");
             b(2:k+1) = pinv(C) * bv;
        else
            b(2:k+1) = C \ bv;
        end
    end    
    % Calculăm coeficienții numărătorului
    a = zeros(m+1, 1);
    for j = 0:m
        for l = 0:j
               a(j+1) = a(j+1) + c(j-l+1) * b(l+1);
        end
    end
    
    % Construim fracția rațională R(x) = P_m(x) / Q_k(x)
    vp = polyval(flip(a), x); % Evaluare numărător
    vq = polyval(flip(b), x); % Evaluare numitor
    R = vp ./ vq;
end

function R = my_cos_pade(m, k, x)
    % Aproximare Padé [m/k] a functiei cos
    % m - gradul numaratorului
    % k - gradul numitorului
    % x - punctele la care evaluam
    x = mod(x + pi, 2 * pi) - pi;
    c = zeros(m+k+1, 1);    
    for p = 0:m+k
        if mod(p, 2) == 0
            c(p+1) = (-1)^(p/2) / factorial(p);
        else
            c(p+1) = 0;
        end
    end
    
    % Construim sistemul pentru coeficientii numitorului
    b = zeros(m+k+1, 1);  % Facem b suficient de lung și completăm cu 0
    b(1) = 1; % Primul coeficient este fixat la 1
    if k > 0
        C = toeplitz(c(m+1:m+k), c(m+1:-1:m-k+2));
        bv = -c(m+(1:k)+1);
        
        if cond(C) > 1e12
             %warning("Matricea Toeplitz este aproape singulară. Folosesc pinv().");
             b(2:k+1) = pinv(C) * bv; 
        else
            b(2:k+1) = C \ bv;
        end
    end
    
    % Calculăm coeficienții numărătorului
    a = zeros(m+1, 1);
    for j = 0:m
        for l = 0:j
             a(j+1) = a(j+1) + c(j-l+1) * b(l+1);
        end
    end
    
    % Construim fracția rațională R(x) = P_m(x) / Q_k(x)
    vp = polyval(flip(a), x); % Evaluare numărător
    vq = polyval(flip(b), x); % Evaluare numitor
    R = vp ./ vq;
end
