clc;
    close all;
    clear all;

%% Simulation control panel
    simCase = 1;
    plotRun = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];

%% Simulation case 1: pure force added to vessel
    if simCase == 1
        simulationTime = 100;   % seconds to run simulation
        
        Pship = [0; 0; 0]; % Initial ship position
        Piceberg = [-1; 0]; % Initial iceberg position
        cVelocity = 0.01; % m/s
        cAngle = pi;
        
        vesselForces = [5; 2; 0];
        
        % For animation
        viewWaypoints = 0;

        % For plots
        inDataType = 1;
        plotRun(10) = 10;
        plotRun(5) = 5;
        
        
        % Failure modes
        overturnLimit = 4;
            T_overturn = 130;               % Newton
            sd_overturn = 0.075*T_overturn;
        ruptureLimit = 3;
            T_break = 160;                  % Newton
            sd_break = 0.075*T_break;       % Berntsen08, p.85
        slippageLimit = 5;
            T_slip = 140;
            sd_slip = 0.075*T_slip;
    end
        
%% Simulation case 2: pure force, with slack line
    if simCase == 2
        simulationTime = 100;   % seconds to run simulation
        
        Pship = [0; 0; pi]; % Initial ship position
        Piceberg = [0; -0.3]; % Initial iceberg position
        cVelocity = 0.01; % m/s
        cAngle = pi;
        
        vesselForces = [5; -2; 0];
        
        % For animation
        viewWaypoints = 0;

        % For plots
        inDataType = 1;
        plotRun(5) = 5;
        plotRun(10) = 10;
        
        
        % Failure modes
        overturnLimit = 4;
            T_overturn = 130;               % Newton
            sd_overturn = 0.075*T_overturn;
        ruptureLimit = 3;
            T_break = 160;                  % Newton
            sd_break = 0.075*T_break;       % Berntsen08, p.85
        slippageLimit = 5;
            T_slip = 140;
            sd_slip = 0.075*T_slip;
    end
        
%% Simulation case 3: showing reliability indices
    if simCase == 3
        simulationTime = 100;   % seconds to run simulation
        
        Pship = [0; 0; 0]; % Initial ship position
        Piceberg = [-1; 0]; % Initial iceberg position
        cVelocity = 0.01; % m/s
        cAngle = pi;
        
        vesselForces = [5; 2; 0]; 
        
        % Failure modes
        overturnLimit = 11;
            T_overturn = 70;               % Newton
            sd_overturn = 0.075*T_overturn;
        ruptureLimit = 10;
            T_break = 160;                  % Newton
            sd_break = 0.075*T_break;       % Berntsen08, p.85
        slippageLimit = 10.5;
            T_slip = 140;
            sd_slip = 0.075*T_slip;
        
        % For animation
        viewWaypoints = 0;

        % For plots
        inDataType = 1;
        plotRun(5) = 5;
        plotRun(6) = 6;
        plotRun(10) = 10;
        plotRun(11) = 11;
    end
        
%% Simulation case 4: iceberg overturning occuring, with linear force applied
    if simCase == 4
        simulationTime = 20;   % seconds to run simulation
        
        Pship = [0; 0; pi/4]; % Initial ship position
        Piceberg = [-0.7; -0.7]; % Initial iceberg position
        cVelocity = 0.1; % m/s
        cAngle = pi;
        
        vesselForces = [4; -1; 0]; 
        
        % Failure modes
        overturnLimit = 7;
            T_overturn = 130;               % Newton
            sd_overturn = 0.075*T_overturn;
        ruptureLimit = 3;
            T_break = 160;                  % Newton
            sd_break = 0.075*T_break;       % Berntsen08, p.85
        slippageLimit = 5;
            T_slip = 140;
            sd_slip = 0.075*T_slip;
        
        % For animation
        viewWaypoints = 0;

        % For plots
        inDataType = 1;
        plotRun(5) = 5;
        plotRun(6) = 6;
        plotRun(10) = 10;
        plotRun(11) = 11;
        
    end
    
%% Simulation case 5: Thrust penalty control
    if simCase == 5
        
        simulationTime = 350;
        
        Pship = [0; 0; 0]; % Initial ship position
        Piceberg = [-1; 0]; % Initial iceberg position
        cVelocity = 0; % m/s
        cAngle = pi;
        
        etaRef = [800; 0; 0];
        nuRef = [0.01; 0; 0];
        
        % Failure modes
        overturnLimit = 1;
            T_overturn = 500;               % Newton
            sd_overturn = 0.075*T_overturn;
        ruptureLimit = 3;
        ruptureNear = 6;
            T_break = 160;                  % Newton
            sd_break = 0.075*T_break;       % Berntsen08, p.85
        slippageLimit = 1;
            T_slip = 500;
            sd_slip = 0.075*T_slip;
        
        % For animation
        viewWaypoints = 0;

        % For plots
        inDataType = 1;
        plotRun(10) = 10;
        plotRun(12) = 12;
        plotRun(13) = 13;
        plotRun(20) = 20;
        plotRun(21) = 21;
        
    end
    
%% Simulation case 6: Thrust penalty control
    if simCase == 6
        
        simulationTime = 350;
        
        Pship = [0; 0; 0]; % Initial ship position
        Piceberg = [-1; 0]; % Initial iceberg position
        cVelocity = 0; % m/s
        cAngle = pi;
        
        etaRef = [800; 0; 0];
        nuRef = [0.01; 0; 0];
        
        % Failure modes
        overturnLimit = 1;
            T_overturn = 500;               % Newton
            sd_overturn = 0.075*T_overturn;
        ruptureLimit = 5.8;
        ruptureNear = 7;
            T_break = 160;                  % Newton
            sd_break = 0.075*T_break;       % Berntsen08, p.85
        slippageLimit = 1;
            T_slip = 500;
            sd_slip = 0.075*T_slip;
        
        % For animation
        viewWaypoints = 0;

        % For plots
        inDataType = 1;
        plotRun(10) = 10;
        plotRun(12) = 12;
        plotRun(13) = 13;
        plotRun(20) = 20;
        plotRun(21) = 21;
        
    end
    
%% Simulation case 7: LOS-based algorithm, with observer, guidance and controller!
    if simCase == 7
        simulationTime = 400;
        
        % Initial positions
        Pship = [-3.5; -2.9; 0];
        Piceberg = [-4.5; -2.9];
        
        % Velocity reference
        u_ref = 0.03;       % m/s
        
        % Current velocity and angle
        cVelocity = 0.01; %m/s
        cAngle = 0;
        
        % Waypoints
        WP = [-5 -3;
              7 3];
        nPoints = size(WP,1);
        
        % Failure modes
        overturnLimit = 4;
            T_overturn = 130;               % Newton
            sd_overturn = 0.075*T_overturn;
        ruptureLimit = 3;
            T_break = 160;                  % Newton
            sd_break = 0.075*T_break;       % Berntsen08, p.85
        slippageLimit = 5;
            T_slip = 140;
            sd_slip = 0.075*T_slip;
            
        % For animation
        viewWaypoints = 1;

        % For plots
        inDataType = 2;
        plotRun(2) = 2;
        plotRun(3) = 3;
        plotRun(6) = 6;
        plotRun(7) = 7;
        plotRun(8) = 8;
        plotRun(9) = 9;
        plotRun(16) = 16;
        plotRun(17) = 17;
        
    end
    
%% Simulation case 8: Overall strategy: LOS alogrithm + Rel-base velocity reference control
if simCase == 8
    
    simulationTime = 1100;
        
        % Initial positions
        Pship = [-3.5; -2.9; 0];
        Piceberg = [-4.5; -2.9];
        
        % Velocity reference
        u_ref = 0.03;       % m/s
        
        % Current velocity and angle
        cVelocity = 0.01; %m/s
        cAngle = pi;
        
        % Waypoints
        WP = [-5 -3;
              17 13];
        nPoints = size(WP,1);
        
        % Failure modes
        overturnLimit = 1;
            T_overturn = 600;               % Newton
            sd_overturn = 0.075*T_overturn;
        ruptureNear = 9.5;
        ruptureLimitRef = 9;
        ruptureLimit = 9;
            T_break = 6;                  % Newton
            sd_break = 0.075*T_break;       % Berntsen08, p.85
        slippageLimit = 1;
            T_slip = 600;
            sd_slip = 0.075*T_slip;
            
        % For animation
        viewWaypoints = 1;

        % For plots
        inDataType = 2;
        plotRun(2) = 2;
        plotRun(3) = 3;
        plotRun(6) = 6;
        plotRun(7) = 7;
        plotRun(8) = 8;
        plotRun(9) = 9;
        plotRun(12) = 12;
        plotRun(13) = 13;
        plotRun(14) = 14;
        plotRun(16) = 16;
        plotRun(17) = 17;
        plotRun(18) = 18;
    
end

%% Simulation case 9: HIL with faulty position measurements
    if simCase == 9

        simulationTime = 400;

        % Initial positions
        Pship = [-3.5; -2.9; 0];
        Piceberg = [-4.5; -2.9];

        % Velocity reference
        u_ref = 0.03;       % m/s

        % Current velocity and angle
        cVelocity = 0.01; %m/s
        cAngle = 0;

        % Waypoints
        WP = [-5 -3;
              7 3];
        nPoints = size(WP,1);
        
        % Position measurement error percentage
        errPct = .2;

        % Failure modes
        overturnLimit = 4;
            T_overturn = 130;               % Newton
            sd_overturn = 0.075*T_overturn;
        ruptureLimit = 3;
            T_break = 160;                  % Newton
            sd_break = 0.075*T_break;       % Berntsen08, p.85
        slippageLimit = 5;
            T_slip = 140;
            sd_slip = 0.075*T_slip;

        % For animation
        viewWaypoints = 1;

        % For plots
        inDataType = 2;
        plotRun(2) = 2;
        plotRun(3) = 3;
        plotRun(6) = 6;
        plotRun(7) = 7;
        plotRun(8) = 8;
        plotRun(9) = 9;
        plotRun(16) = 16;
        plotRun(17) = 17;
        plotRun(19) = 19;

    end
       
%%          Modelling part                           #
% ###############################################

    % Towing Vessel Parameters [CS Enterprise I]
        shipLength = 1.105; % m
        shipBeam = 0.248; % m

            % Values from Tran (2014)
            shipMass = 17.6;  % kg
            Iz_s = 1.76;    
            x_g = 0.03;     
            X_u = -0.59739;   
            Y_v = - 3.50625;    
            Y_r = -7.25;      
            N_v = 0.1814;    
            N_r = - 1.9;   

            % Values from Cybership II, Skjetne (2005)
            X_udot = - 2;
            Y_vdot = - 10;
            Y_rdot = - 0;
            N_vdot = - 0;
            N_rdot = - 1;
            X_absuu = -1.3274;
            X_uuu = -5.8664;
            Y_absvv = -36.2823;
            N_absvv = 5.0437;

            % Values for calculation of "vessel position placement" on the
            % vessel in BODY-frame
            shipL_d = [shipLength-0.55; 0];     % where Ship Position is placed on the Vessel - On a BODY-frame with x=0 at aft and y=0 at beam/2
            Rfp = [0; 0];                       % where Rope Fastening Point is placed --- || ---

        % Towing vessel calculations
            Dist_spv_rfp = sqrt( ( shipL_d(1) - Rfp(1) )^2 + (shipL_d(2) - Rfp(2) )^2 ); %distance from fastpoint to positionpoint

            % Towing Vessel Matrices
            Ms_rb = [shipMass 0 0;
                     0 shipMass shipMass*x_g;
                     0 shipMass*x_g Iz_s];
            Ms_a = -[X_udot 0 0;
                     0 Y_vdot Y_rdot;
                     0 Y_rdot N_rdot];
            Ds = [-X_u 0 0;
                  0 -Y_v -N_v;
                  0 -Y_r -N_r];
            K_M = [ 1 0 0; 
                    0 1 0; 
                    0 -shipL_d(1) 0];
            Ms_tot = Ms_rb + Ms_a;

    % Iceberg Parameters [iceberg model, large, upside-down bottle with 1 kg weight hanging underneath]
        Rho_ice = 916.7;    % kg/m3
        Rho_sw = 1000;      % kg/m3
        scale = 1/50;       % -
        iceDiameter = 0.2;     % m
        iceHeight = 0.8;       % m
        iceMass = 23;        % liter = kg
        C_wi = 0.75;            % Found from Marchenko/Eik ... Robe

        % Iceberg calculations

        iceVolume = pi*iceDiameter^2*iceHeight/4;
        iceDraught = iceMass/(pi*iceDiameter^2*Rho_sw/4)
        S_i = iceDiameter * iceDraught;    % Underwater projected surface for surge calculation (marchenkoEik)
        iX_uu = -Rho_sw*C_wi*S_i;
        iY_vv = -Rho_sw*C_wi*S_i;

        % Iceberg matrices
        Mi_rb = iceMass*[1 0; 0 1]
        Mi_a = iceMass*[1 0; 0 1]
        Di = [50 0;   % D matrix isnt really correct. just preliminary values
              0 50]

    % Ocean current modelling
        Vc = [cVelocity*cos(cAngle);
              cVelocity*sin(cAngle)];

    % Towline modelling
        TowLineLength = 1.11; %m
        K_tow = 20; % is EA/L, just chosen some value to estimate tension..
        
        % Statistical parameters for tension mean and variance
        Ninstances = 50;
        saved_init = zeros(Ninstances,1);
        
        % Parameters for reliability index
        kappa = 2;      % Is approximately 2, check graph for function (2.46) in Berntsen, p.35
                        %n=1:0.01:30;
                        %a = sqrt(2.*log(n)) + 0.57722./sqrt(2.*log(n));
                        %plot(n,real(a))
   
%%          Observer part                            #
% ###############################################

    % Observer values
    T_bias = diag([20 200 20]); %20 200 20
    E_bias = diag([.1 .1 .1]);
    K2_obs = diag([0.25 1 0.5]); % 0.25 1 0.5
    K3_obs = diag([1 1 1]);
    K4_obs = diag([250 300 100]); %150 300 100
    
%     % Observer matrices
%     A0_obs = [-K2_obs zeros(3);
%               -K3_obs -inv(T_bias)];
%     B0_obs = [eye(3);
%               zeros(3)];
%     C0_obs = [K4_obs -eye(3)];
%     E0_obs = [zeros(3);
%               E_bias];

%%          Guidance part                            #
% ###############################################

    % Operator parameters (for integral gain initiation)
        % The offset is in which direction the iceberg is pulled relative to
        % the desired path.
    Offset_direction = 0;   % (1 for right, -1 for left, 0 for none)
    WPi_init = 2;

    % LOS parameters
    n = 4;              % number of shiplengths radius of circle surrounding ship
    Rk = 2 * shipLength;     % radius of circle of acceptance for switching waypoints
    sigma = 0.005;        % Integral gain for LoS with current
    %sigma_ship = 0.05;  % Integral gain for p_des for ship  ( BRUKES DENNE? )

    % Marine Craft Simulator, Reference model
    Ms_d = Ms_rb + Ms_a;
    Ds_d = .5*Ds;
    Gs_d = [1 0 0; 0 1 0; 0 0 1];
    Omega_d = (Ms_d\Gs_d).^(1/2);
    Delta_d = 0.5 * Ms_d\Ds_d/Omega_d;
    %A_ref2 = (2*Delta_d + eye(3)) * Omega_d;
    %B_ref2 = (2*Delta_d + eye(3)) * Omega_d^2;
    %C_ref2 = Omega_d^3;

    % Tune reference model
    A_ref = [0.176     0           0;
             0          0.5      0;
             0          0           0.9642];
    B_ref = [0.0554     0           0;
             0          0.22        0;   
             0          0           0.1741];
    C_ref = [0.05*0.0038     0           0;
             0          0.047       0;  
             0          0           0.0109]; 
%     A_ref = [0.176     0           0;
%              0          0.5      0;
%              0          0           0.9642];
%     B_ref = [0.0554     0           0;
%              0          0.22        0;   
%              0          0           0.1741];
%     C_ref = [0.0038     0           0;
%              0          0.047       0;  
%              0          0           0.0109]; 
         
    % Physical limitations, saturation elemtens in the Reference Filter
    u_surge_max = 2;        % m/s
    u_sway_max = 1;     	% m/s
    u_yaw_max = 2*pi/60;      % rad/s
    %a_xy_max = 0.2;         % m/s^2 (if different values are desired for surge and sway, this must be changed, along with the script in the reference model)
    %a_yaw_max = u_yaw_max/5;   % rad/s2

%%          Controller part                          #
% ###############################################

    % Integrator backstepping controller
    S_trans = [0 -1 0;
               1 0 0;
               0 0 0];
    Kp = [10 0 0;  % 0.1
          0 .1 0;
          0 0 .1];
    if simCase == 5 || simCase == 6
        Kp(1,1) = 0.1;
    end
    Kd = [50 0 0;   % 50
          0 10 0;
          0 0 10];

%% Run simulink models
if simCase == 1 || simCase == 2 || simCase == 3 || simCase == 4
    sim 'HIL_model_experiments1.slx';
    viewResults
end

if simCase == 5 || simCase == 6
    sim 'HIL_model_experiments2.slx';
    viewResults
end

if simCase == 7
    sim 'HIL_model.slx';
    viewResults
end

if simCase == 8
    sim 'HIL_model_overall.slx';
    viewResults
end

if simCase == 9
    sim 'HIL_model_error.slx';
    viewResults
end


