clear
clc
asc_files = dir(fullfile(pwd, '*.asc'));

for i=1:length(asc_files); 

    j = importdata(asc_files(i,1).name, '\t', 37);

    %Time DEVICE_1 (Sample rate 1)	F8111	F8113	F8114	F8116
    f8111=j.data(:,2);
    f8113=j.data(:,3);
    f8114=j.data(:,4);
    f8116=j.data(:,5);

    str=asc_files(i,1).name([16:18]);


        switch str
            case 'pos', 
            sign=1;
            case 'neg'
            sign=-1;
        end

    A(i,2)=mean(f8116)+mean(f8114)-mean(f8111)-mean(f8113);
    A(i,1)=str2double(asc_files(i,1).name([13:14]))*sign*0.1;

end

A=sortrows(A,1);
plot(A(:,1),A(:,2),'-x','LineWidth',2,...
                'MarkerEdgeColor','b',...
                'MarkerFaceColor','b',...
                'MarkerSize',10)
            
grid on
hold on
xlabel('Relative Pitch');
ylabel('Thrust [N]');



[a,b]=polyfit(A(:,1),A(:,2),1);  
axesLimits1 = xlim;
xplot1 = linspace(axesLimits1(1), axesLimits1(2));

Starting3=rand(1);
options=optimset('Display','final');
Estimates3=fminsearch(@actuator_fun_lin,Starting3,options,A(:,1),A(:,2))

% Evaluate polynomial
yplot1 = polyval(a, xplot1);
plot(A(:,1),Estimates3(1)*A(:,1),'r')

formula=['F=',num2str(a(1)),'p']

Starting=rand(1);
options=optimset('Display','final');
Estimates=fminsearch(@actuator_fun,Starting,options,A(:,1),A(:,2))


Starting2=rand(1,2);
options=optimset('Display','final');
Estimates2=fminsearch(@actuator_fun2,Starting2,options,A(:,1),A(:,2))

hold on
plot(A(:,1),Estimates*abs(A(:,1)).*A(:,1),'g')
plot(A(:,1),Estimates2(1)*abs(A(:,1)).*A(:,1)+Estimates2(2)*A(:,1),'k')

legend('Measured data',['Linear fit ' formula ],['Nonlinear fit F=',num2str(Estimates),'*|p|p'],['Nonlinear fit F=',num2str(Estimates2(1)),'*|p|p + ',num2str(Estimates2(2)),'*p'],'Location','Best')
print -dpng VSPsway.png -r500