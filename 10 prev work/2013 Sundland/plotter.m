%% Fetch the values

% Use Latex as interpreter for the plotting 
set(0, 'defaultTextInterpreter', 'latex');

% Time
time = simout_eta_s.time';

% Position and orientation of the ship
eta_s_N = simout_eta_s.signals.values(:,1)';
eta_s_E = simout_eta_s.signals.values(:,2)';
eta_s_psi = simout_eta_s.signals.values(:,3)';

% Velocity of the ship
nu_s_N = simout_nu_s.signals.values(:,1)';
nu_s_E = simout_nu_s.signals.values(:,2)';
nu_s_psi = simout_nu_s.signals.values(:,3)';

% Position and orientation of the iceberg
eta_i_N = simout_eta_i.signals.values(:,1)';
eta_i_E = simout_eta_i.signals.values(:,2)';
eta_i_psi = simout_eta_i.signals.values(:,3)';

% Velocity of the iceberg
nu_i_N = simout_nu_i.signals.values(:,1)';
nu_i_E = simout_nu_i.signals.values(:,2)';
nu_i_psi = simout_nu_i.signals.values(:,3)';

% Desired path for the controller
eta_d_N = simout_eta_d.signals.values(:,1)';
eta_d_E = simout_eta_d.signals.values(:,2)';
eta_d_psi = simout_eta_d.signals.values(:,3)';

% Estimated position and orientation of the ship
eta_s_hat_N = simout_eta_s_hat.signals.values(:,1)';
eta_s_hat_E = simout_eta_s_hat.signals.values(:,2)';
eta_s_hat_psi = simout_eta_s_hat.signals.values(:,3)';

% Estimated velocity of the ship
nu_s_hat_N = simout_nu_s_hat.signals.values(:,1)';
nu_s_hat_E = simout_nu_s_hat.signals.values(:,2)';
nu_s_hat_psi = simout_nu_s_hat.signals.values(:,3)';

% Estimated position and orientation of the iceberg
eta_i_hat_N = simout_eta_i_hat.signals.values(:,1)';
eta_i_hat_E = simout_eta_i_hat.signals.values(:,2)';
eta_i_hat_psi = simout_eta_i_hat.signals.values(:,3)';

% Estimated velocity of the iceberg
nu_i_hat_N = simout_nu_i_hat.signals.values(:,1)';
nu_i_hat_E = simout_nu_i_hat.signals.values(:,2)';
nu_i_hat_psi = simout_nu_i_hat.signals.values(:,3)';

% Forces in the tow rope
X_tow = simout_towforce.signals.values(:,1)';
Y_tow = simout_towforce.signals.values(:,2)';
N_tow = simout_towforce.signals.values(:,3)';

% Bias values from the bias model
bias_s_N = simout_bias_s.signals.values(:,1);
bias_s_E = simout_bias_s.signals.values(:,2);
bias_s_psi = simout_bias_s.signals.values(:,3);

%% Position in the NE plane

plot(eta_s_E, eta_s_N)
title('Position in the NE plane')
hold on
plot(eta_i_E, eta_i_N, 'g')
plot(eta_d_E, eta_d_N, 'r')
legend('Ship', 'Iceberg', 'Desired path')
ylabel('North [m]')
xlabel('East [m]')

%% Observer compared to real values - eta - ship

subplot(3,1,1), plot(time, eta_s_hat_N);
hold on
plot(time, eta_s_N, 'r')
title('Observer values for \eta compared to real values')
ylabel('Position [m]')
xlabel('Time [s]')
legend({'$$\hat{\eta_{s,n}}$$', '$$\eta_{s,n}$$'}, 'interpreter', 'latex', 'fontsize', 14)
subplot(3,1,2), plot(time, eta_s_hat_E);
hold on
plot(time, eta_s_E, 'r')
ylabel('Position [m]')
xlabel('Time [s]')
legend({'$$\hat{\eta_{s,e}}$$', '$$\eta_{s,e}$$'}, 'interpreter', 'latex', 'fontsize', 14)
subplot(3,1,3), plot(time, eta_s_hat_psi);
hold on
plot(time, eta_s_psi, 'r')
ylabel('Angle [rad]')
xlabel('Time [s]')
legend({'$$\hat{\eta_{s,\psi}}$$', '$$\eta_{s,\psi}$$'}, 'interpreter', 'latex', 'fontsize', 14)

%% Observer compared to real values - nu - ship

subplot(3,1,1), plot(time, nu_s_hat_N);
hold on
plot(time, nu_s_N, 'r')
title('Observer values for \nu compared to real values')
ylabel('Velocity [m/s]')
xlabel('Time [s]')
legend({'$$\hat{\nu_{s,n}}$$', '$$\nu_{s,n}$$'}, 'interpreter', 'latex', 'fontsize', 14)
subplot(3,1,2), plot(time, nu_s_hat_E);
hold on
plot(time, nu_s_E, 'r')
ylabel('Velocity [m/s]')
xlabel('Time [s]')
legend({'$$\hat{\nu_{s,e}}$$', '$$\nu_{s,e}$$'}, 'interpreter', 'latex', 'fontsize', 14)
subplot(3,1,3), plot(time, nu_s_hat_psi);
hold on
plot(time, nu_s_psi, 'r')
ylabel('Angle/time [rad/s]')
xlabel('Time [s]')
legend({'$$\hat{\enu_{s,\psi}}$$', '$$\nu_{s,\psi}$$'}, 'interpreter', 'latex', 'fontsize', 14)

%% Observer compared to real values - eta - iceberg

subplot(3,1,1), plot(time, eta_i_hat_N);
hold on
plot(time, eta_i_N, 'r')
title('Observer values for \eta compared to real values')
ylabel('Position [m]')
xlabel('Time [s]')
legend({'$$\hat{\eta_{i,n}}$$', '$$\eta_{i,n}$$'}, 'interpreter', 'latex', 'fontsize', 14)
subplot(3,1,2), plot(time, eta_i_hat_E);
hold on
plot(time, eta_i_E, 'r')
ylabel('Position [m]')
xlabel('Time [s]')
legend({'$$\hat{\eta_{i,e}}$$', '$$\eta_{i,e}$$'}, 'interpreter', 'latex', 'fontsize', 14)
subplot(3,1,3), plot(time, eta_i_hat_psi);
hold on
plot(time, eta_i_psi, 'r')
ylabel('Angle [rad]')
xlabel('Time [s]')
legend({'$$\hat{\eta_{i,\psi}}$$', '$$\eta_{i,\psi}$$'}, 'interpreter', 'latex', 'fontsize', 14)

%% Observer compared to real values - nu - iceberg

subplot(3,1,1), plot(time, nu_i_hat_N);
hold on
plot(time, nu_i_N, 'r')
title('Observer values for \nu compared to real values')
ylabel('Velocity [m/s]')
xlabel('Time [s]')
legend({'$$\hat{\nu_{s,n}}$$', '$$\nu_{s,n}$$'}, 'interpreter', 'latex', 'fontsize', 14)
subplot(3,1,2), plot(time, nu_i_hat_E);
hold on
plot(time, nu_i_E, 'r')
ylabel('Velocity [m/s]')
xlabel('Time [s]')
legend({'$$\hat{\nu_{i,e}}$$', '$$\nu_{i,e}$$'}, 'interpreter', 'latex', 'fontsize', 14)
subplot(3,1,3), plot(time, nu_i_hat_psi);
hold on
plot(time, nu_i_psi, 'r')
ylabel('Angle/time [rad/s]')
xlabel('Time [s]')
legend({'$$\hat{\enu_{i,\psi}}$$', '$$\nu_{i,\psi}$$'}, 'interpreter', 'latex', 'fontsize', 14)

%% Forces in the tow rope

subplot(3,1,1), plot(time, X_tow);
title('Forces and moments in the tow rope')
ylabel('Force [N]')
xlabel('Time [s]')
legend('X_{tow}')
subplot(3,1,2), plot(time, Y_tow, 'g');
ylabel('Force [N]')
xlabel('Time [s]')
legend('Y_{tow}')
subplot(3,1,3), plot(time, N_tow, 'r');
ylabel('Moment [Nm]')
xlabel('Time [s]')
legend('N_{tow}')

%% Bias model

subplot(3,1,1), plot(time, bias_s_N);
title('Biases on the ship')
ylabel('Bias')
xlabel('Time [s]')
legend('N')
subplot(3,1,2), plot(time, bias_s_E, 'g');
ylabel('Bias')
xlabel('Time [s]')
legend('E')
subplot(3,1,3), plot(time, bias_s_psi, 'r');
ylabel('Bias')
xlabel('Time [s]')
legend('\psi')