
clear
clc
close all
bdclose all


%% Load and preprocess lab data

load dptest2/CSE1_data.mat


load dptest2/CSE1_data_reg_error.mat


start=8000;
limit=length(cse1_data)-120;

time=cse1_data(1,[start:limit])';


x=cse1_data(2,:); x(x==0)=NaN;
y=cse1_data(3,:); y(y==0)=NaN;
z=cse1_data(4,:); z(z==0)=NaN;

phi=cse1_data(5,:); phi(phi==0)=NaN;
theta=cse1_data(6,:); theta(theta==0)=NaN;
psi=cse1_data(7,:); psi(psi==0)=NaN;


x_d=cse1_data(21,[start:limit]);
y_d=cse1_data(22,[start:limit]);
psi_d=cse1_data(23,[start:limit]);

Ue=cse1_data([8:12],[start:limit])';

b = 1:length(x);
% find all valid values
idx = find(~isnan(x));
% do the interpolation
x_interp = interp1(b(idx),x(idx),b)';
x=x_interp([start:limit]);

b = 1:length(y);
% find all valid values
idx = find(~isnan(y));
% do the interpolation
y_interp = interp1(b(idx),y(idx),b)';
y=y_interp([start:limit]);


b = 1:length(z);
% find all valid values
idx = find(~isnan(z));
% do the interpolation
z_interp = interp1(b(idx),z(idx),b)';
z=z_interp([start:limit]);


b = 1:length(phi);
% find all valid values
idx = find(~isnan(phi));
% do the interpolation
phi_interp = interp1(b(idx),psi(idx),b)';
phi=phi_interp([start:limit]);


b = 1:length(theta);
% find all valid values
idx = find(~isnan(theta));
% do the interpolation
theta_interp = interp1(b(idx),psi(idx),b)';
theta=theta_interp([start:limit]);


b = 1:length(psi);
% find all valid values
idx = find(~isnan(psi));
% do the interpolation
psi_interp = interp1(b(idx),psi(idx),b)';
psi=psi_interp([start:limit]);

figure('Position',[1 600 1000 900])
subplot(3,1,1); plot(time,x,time,x_d); ylabel('North [m]'); legend('Actual position','Desired position','location','NorthEastOutside'); grid on;
subplot(3,1,2); plot(time,y,time,y_d); ylabel('East [m]'); legend('Actual position','Desired position','location','NorthEastOutside'); grid on;
subplot(3,1,3); plot(time,psi*180/pi,time,psi_d*180/pi); ylabel('Yaw [deg]'); legend('Actual heading','Desired heading','location','NorthEastOutside'); grid on;
xlabel('Time [s]');
print -dpng dpeta.png -r500

figure('Position',[1 600 1000 900])
subplot(3,1,1); plot(time,x-x_d','color','red'); ylabel('North [m]'); legend('North error','location','NorthEastOutside'); grid on;
subplot(3,1,2); plot(time,y-y_d','color','red'); ylabel('East [m]'); legend('East error','Desired position','location','NorthEastOutside'); grid on;
subplot(3,1,3); plot(time,psi*180/pi-psi_d'*180/pi,'color','red'); ylabel('Yaw [deg]'); legend('Yaw error','location','NorthEastOutside'); grid on;
xlabel('Time [s]');
print -dpng dperror.png -r500




figure('Position',[1 600 1000 900])
subplot(5,1,1); plot(time,Ue(:,1)); ylabel('u_1');
subplot(5,1,2); plot(time,Ue(:,2)); ylabel('u_2');
subplot(5,1,3); plot(time,Ue(:,3)); ylabel('u_3');
subplot(5,1,4); plot(time,Ue(:,4)); ylabel('u_4');
subplot(5,1,5); plot(time,Ue(:,5)); ylabel('u_5');
xlabel('Time [s]');
print -dpng dpue.png -r500
