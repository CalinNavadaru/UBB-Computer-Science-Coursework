n=20;
p=poly(1:n);
roots(p);

xi=1:n;
nc=condpol(poly(xi),xi);
format short g
[ncs,i]=sort(nc');
disp("Condiția pentru polinomul Wilkinson:");
disp([ncs,i])

ai=2 .^ (-1 .* (1:n));
nc=condpol(poly(ai),ai);
format short g
[ncs,i]=sort(nc');
disp("Condiția pentru polinomul cu rădăcinile a_k = 2^{-k}:");
disp([ncs,i])

subplot(2, 2, 1);
pert_n(n, poly(xi));
title('Perturbare normală - Polinom Wilkinson');

subplot(2, 2, 2);
pert_u(n, poly(xi));
title('Perturbare uniformă - Polinom Wilkinson');

subplot(2, 2, 3);
pert_n(n, poly(ai));
title('Perturbare normală - Polinom ak');

subplot(2, 2, 4);
pert_u(n, poly(ai));
title('Perturbare uniformă - Polinom ak');


function nc=condpol(p,xi)
if nargin<2
    xi=roots(p);
end
n=length(p)-1;
derivata_p=(n:-1:1).*p(1:end-1); 
nc=1./(abs(xi.*polyval(derivata_p,xi))).*(polyval(abs(p(2:end)),abs(xi)));
end

function pert_n(n, p)
h=plot(1:n,zeros(1,n),'.');
set(h,'Markersize',15);
hold on
for k=1:1000
     r=randn(1,n+1);
     pr=p.*(1+1e-10*r);
     z=roots(pr);
     h2=plot(z,'k.');
     set(h2,'Markersize',4)
end
axis equal
end

function pert_u(n, p)
    h = plot(1:n, zeros(1, n), '.');
    set(h, 'Markersize', 15);
    hold on   
    for k = 1:1000
        r = (1e-10) * rand(1, n + 1);
        pr = p + r .* p; 
        z = roots(pr); 
        h2 = plot(z, 'k.'); 
        set(h2, 'Markersize', 4);
    end
    axis equal; 
end
