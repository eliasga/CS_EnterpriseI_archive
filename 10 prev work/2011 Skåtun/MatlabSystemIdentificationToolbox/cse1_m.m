function [dx, y] = cse1_m(t, x, u, m, Xud, Yvd, Yrd, Nvd, Nrd, Xu, Yv, Yr, Nv, Nr,  xg, Iz, lx1,ly1,lx2,ly2,lx3,K1,K2,K3,K4,K5,b1,b2,b3, varargin)

% Output equations.
y = [x(1);                ... 
     x(2);                ... 
     x(3);                ... 
     x(4);                ... 
     x(5);                ... 
     x(6)                 ... 
    ];
   
     
M=[m-Xud 0 0; 0 m-Yvd m*xg-Yrd; 0 m*xg-Nvd Iz-Nrd];
     
D=[-Xu 0 0 ; 0 -Yv -Yr; 0 -Nv -Nr];     

Te=[1 0 1 0 0; 0 1 0 1 1; ly1 -lx1 -ly2 -lx2 lx3];

Ke=diag([K1 K2 K3 K4 K5]);

ue=[u(1); u(2); u(3); u(4); u(5)];

R=[cos(x(3)) -sin(x(3)) 0; sin(x(3)) cos(x(3)) 0; 0 0 1];

b=[b1;b2;b3];


dx= [zeros(3) R; zeros(3) -inv(M)*D]*y + [zeros(3); inv(M)]*Te*Ke*ue  + [zeros(3); inv(M)*transp(R)]*b;