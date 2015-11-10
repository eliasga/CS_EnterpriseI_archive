clear
clc
close all
bdclose all

% String to hold an unique filename for the plots
timestr = datestr(now, 'yyyymmmddHHMM');


%% Load data
load realWorldData/CSE1_data_random_run4.mat


%% Preprocess and prepeare data
x=cse1_data(2,:); x(x==0)=NaN;
y=cse1_data(3,:); y(y==0)=NaN;
z=cse1_data(4,:); z(z==0)=NaN;

phi=cse1_data(5,:); phi(phi==0)=NaN;
theta=cse1_data(6,:); theta(theta==0)=NaN;
psi=cse1_data(7,:); psi(psi==0)=NaN;


limit=7500; % Last sample
start=1;    % Starting sample


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


%    N  E yaw
eta=[x';y';psi']';
eta6dof=[x';y';z';phi';theta';psi']'; 
nu=calcNu(eta6dof);


s=length(x);
eta_test=[x([1:s-1])' ;y([1:s-1])';psi([1:s-1])'; nu(:,1)' ; nu(:,2)' ; nu(:,6)' ]';
Ue=cse1_data([8:12],[start:limit])';
Ue_test=Ue([1:s-1],:);

lx1=0.425;
ly1=0.055;
lx2=0.425;
ly2=0.055;
lx3=0.415;

Te=[1 0 1 0 0; 0 1 0 1 1; ly1 -lx1 -ly2 -lx2 lx3];


%% Define input/output
z = iddata(eta_test, Ue_test, 0.05, 'Name', 'CS Enterprise I');
set(z, 'InputName', {'u1'        ...
                     'u2'        ...
                     'u3'        ...
                     'u4' ...
                     'u5' ...
                    },            ...
       'InputUnit', {'-' '-' '-' '-' '-'    ...
                    });
set(z, 'OutputName', {'North'        ...
                      'East'        ...
                      'Psi (Yaw)'        ...
                      'Surge speed'        ...
                      'Sway speed'        ...
                      'Yaw rate'        ...
                      },          ...
       'OutputUnit', {'m' 'm' 'rad' 'm/s' 'm/s' 'rad/s'});
set(z, 'Tstart', 0, 'TimeUnit', 's');

%% Plot input data
figure('Name', [z.Name ': input data']);
Pos = get(gcf,'Position');
set(gcf,'Position',[Pos(1), Pos(2)-Pos(4)/2, Pos(3)*1.25, Pos(4)*1.5]);
for i = 1:z.Nu
   subplot(z.Nu, 1, i);
   plot(z(:, [], i));
   title(['Input #' num2str(i) ': ' z.InputName{i}]);
   xlabel('');
   %axis('tight');
   if (i > z.Nu-1)
       xlabel([z.Domain ' (' z.TimeUnit ')']);
   end
end
saveas(gcf, [timestr '_figure1.png'])

%% Plot output data
figure('Name', [z.Name ': output data']);
Pos = get(gcf,'Position');
set(gcf,'Position',[Pos(1), Pos(2)-Pos(4)/2, Pos(3), Pos(4)*1.5]);
for i = 1:z.Ny
   subplot(z.Ny, 1, i);
   plot(z(:, i, []));
   title(['Output #' num2str(i) ': ' z.OutputName{i}]);
   xlabel('');
   axis('tight');
end
xlabel([z.Domain ' (' z.TimeUnit ')']);
saveas(gcf, [timestr '_figure2.png'])



%% Define parameters
Parameters = struct('Name', ...
   {'m'   ... % Mass 
    'Xud' ... % Added mass surge
    'Yvd' ...
    'Yrd' ...
    'Nvd' ...
    'Nrd' ...
    'Xu'  ...
    'Yv'  ...
    'Yr'  ...
    'Nv'  ...
    'Nr'  ...
    'xg'  ...
    'Iz'  ...
    'lx1' ... 
    'ly1' ... 
    'lx2' ... 
    'ly2' ... 
    'lx3' ... 
    'K1' ...
    'K2' ...
    'K3' ...
    'K4' ...
    'K5' ...
    'b1' ...
    'b2' ...
    'b3' ...
   },                     ...  
   'Unit', ...
   {'kg' 'kg' 'kg' 'kg' 'kg' 'kg' 'kg/s' 'kg/s' 'kg/s' 'kg/s' 'kg/s'   'm'  'kg*m^2'   'm' 'm' 'm' 'm' 'm' 'N' 'N' 'N' 'N' 'N' 'N' 'N' 'N' ...
        },   ...
    'Value', ...
     {14.1, -0.6, -15.0, -0.1,  -0.1,  -0.7,-0.55,-3.94, -0.1, 1.0, -0.3, 0.030,1.4, 0.425, 0.055, 0.425, 0.055, 0.425, 1.28,1.05,1.28,1.05,2.14,0,0,0},               ...  
     'Minimum',...
     {-Inf -5 -20 -50 -50 -50 -2 -10 -30 -30 -30  -0.1 1.0  -Inf -Inf -Inf -Inf -Inf 0.5 0.5 0.5 0.5 0.5 -10 -10 -10}, ... 
     'Maximum', ...
     {Inf -0.3 -5 50 50 0 -0.1 -0.2 30 30 0  0.1 2.0 Inf  Inf Inf Inf  Inf 2 2 2 2 10 10 10 10}, ... 
     'Fixed', ...
     {true false false false false false true true false false false false false true true true true true false false false false false  false false false});



  %% Defining initial states
  InitialStates = struct('Name', {'North'       ...
                                 'East'        ...
                                 'psi'   ...
                                 'u' ...
                                 'v' ...
                                 'r'}, ...
                  'Unit',    {'m' 'm' 'rad' 'm/s' 'm/s' 'rad/s'},   ...
                  'Value',   {x(1) y(1) psi(1) 0 0 0},     ...           
                  'Minimum', {-Inf -Inf -Inf -Inf -Inf -Inf},... 
                  'Maximum', {Inf Inf Inf Inf Inf Inf },... 
                  'Fixed',   {true true true false false false } ); % For some reason often better results are obtained when not setting the initial states to known..


%% Set up the idnlgrey object
FileName     = 'cse1_m';             % File describing the model structure.
Order        = [6 5 6];             % Model orders [ny nu nx].
Ts           = 0;                    % Time-continuous system.
nlgr = idnlgrey(FileName, Order, Parameters, InitialStates, Ts, ...
                'Name', z.Name, 'TimeUnit', 's');

            
            
set(nlgr, 'InputName', z.InputName, 'InputUnit', z.InputUnit);
set(nlgr, 'OutputName', z.OutputName, 'OutputUnit', z.OutputUnit);

present(nlgr)

figure;
compare(z, nlgr); % simulate the model and compare the response to measured values

%% Plot the results
figure;
Pos = get(gcf,'Position');
set(gcf,'Position',[Pos(1), Pos(2)-Pos(4)/2, Pos(3), Pos(4)*1.5]);
pe(z, nlgr);
saveas(gcf, [timestr '_figure3.png'])

duration = clock;
nlgr = pem(z, nlgr, 'Display', 'Full','maxiter', 5); % estimate parameters using "pem"
duration = etime(clock, duration);


disp(['Estimation time   : ' num2str(duration, 4) ' seconds']);
disp(['Time per iteration: ' num2str(duration/nlgr.EstimationInfo.Iterations, 4) ' seconds.']);

figure;
compare(z, nlgr);
saveas(gcf, [timestr '_figure4.png'])

figure;
Pos = get(gcf,'Position');
set(gcf,'Position',[Pos(1), Pos(2)-Pos(4)/2, Pos(3), Pos(4)*1.5]);
pe(z, nlgr);
saveas(gcf, [timestr '_figure5.png'])

present(nlgr);


%% Send an email with the results. 
% Define these variables appropriately:
mail = 'YourGmailName@gmail.com'; %Your GMail email address
password = 'yourPassword'; %Your GMail password

% Then this code will set up the preferences properly:
setpref('Internet','E_mail',mail);
setpref('Internet','SMTP_Server','smtp.gmail.com');
setpref('Internet','SMTP_Username',mail);
setpref('Internet','SMTP_Password',password);
props = java.lang.System.getProperties;
props.setProperty('mail.smtp.auth','true');
props.setProperty('mail.smtp.socketFactory.class', 'javax.net.ssl.SSLSocketFactory');
props.setProperty('mail.smtp.socketFactory.port','465');

a=present(nlgr);
% Send the email. Note that the first input is the address you are sending the email to
sendmail('hakon2k@gmail.com','MATLAB completed identify.m', ['Completed after ' num2str(duration) ' seconds\n' a(1,:) '\n' a(2,:) '\n' a(3,:) '\n'] ,{[timestr '_figure1.png'],[timestr '_figure2.png'],[timestr '_figure3.png'],[timestr '_figure4.png'],[timestr '_figure5.png'],})
