lx1=0.425;
ly1=0.055;
lx2=0.425;
ly2=0.055;
lx3=0.415;

%Te=[1 0 1 0 0; 0 1 0 1 1; ly1 -lx1 -ly2 -lx2 lx3];
Te = [1     0       1       0       0; 
      0     1       0       1       1; 
     ly1  -lx1    -ly2    -lx2     lx3];


Ke = 100*diag([1.28 1.05 1.28 1.05 2.14]);

% Iceberg data
M_i = 1*[25.8     0       0;
           0        33.8    1.0115;
           0        1.0115  2.76];
       
M_i_inv = M_i^(-1);

D_i = 1*[2    0       0;
           0    7       0.1;
           0    0.1     0.5];
       
% Distances between ship and iceberg
pos_0_i = [0, 0, 0]';
pos_0_s = [0, 0, 0]';

pos_diff = pos_0_s - pos_0_i;

% Bias model
T_s = diag([1000, 1000, 1000]);

T_i = diag([1000, 1000, 1000]);

E_b_s = diag([1 1 1]);

E_b_i = diag([1 1 1]);

% Observer data
debug = 0;      % 0 for debug, 1 for not debug

K_1 = debug*[diag([-2.2   -2.2    -2.2]);
             diag([1.6    1.6     1.6])];
   
K_2 = debug*0.001*diag([1 1 1]);              % eta
K_3 = debug*0.001*diag([0.01 0.01 0.001]);    % bias
K_4 = debug*0.001*diag([0.1 0.1 0.1]);        % nu

T_s_inv = T_s^(-1);

Omega = diag([0.8 0.8 0.8]);            % central frequencies of the waves
Lambda = diag([0.1 0.1 0.1]);           % standard deviation of the wave filter

A_w = [zeros(3) eye(3);
       -Omega^2 -2*Lambda*Omega];
   
C_w = [zeros(3) eye(3)];

K_w = diag([1 1 1]);

E_w = [zeros(3);
       K_w];