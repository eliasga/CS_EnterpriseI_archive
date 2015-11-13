%% Fetch the values

time = simout_eta_s.time';
eta_s_N = simout_eta_s.signals.values(:,1)';
eta_s_E = simout_eta_s.signals.values(:,2)';
eta_s_psi = simout_eta_s.signals.values(:,3)';

eta_i_N = simout_eta_i.signals.values(:,1)';
eta_i_E = simout_eta_i.signals.values(:,2)';
eta_i_psi = simout_eta_i.signals.values(:,3)';

eta_d_N = simout_eta_d.signals.values(:,1)';
eta_d_E = simout_eta_d.signals.values(:,2)';
eta_d_psi = simout_eta_d.signals.values(:,3)';

%% Plots the plots in a plot

plot(eta_s_E, eta_s_N, 'LineWidth', 3)
hold on
plot(eta_i_E, eta_i_N, 'r', 'LineWidth', 3)

for i = 1:500:length(time)
    line([eta_s_E(i), eta_i_E(i)], [eta_s_N(i), eta_i_N(i)], 'color', 'k')
    tow_length = sqrt((eta_s_N(i) - eta_i_N(i))^2 + (eta_s_E(i) - eta_i_E(i))^2);
    E_pos = eta_s_E(i) - 0.5*(eta_s_E(i) - eta_i_E(i));
    N_pos = eta_s_N(i) - 0.5*(eta_s_N(i) - eta_i_N(i));
    text(E_pos, N_pos, num2str(tow_length));
end

title('Plot of ship and iceberg position in the NE plane')
legend('Ship', 'Iceberg', 'Towline')
xlabel('East [m]')
ylabel('North [m]')