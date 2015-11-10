clear 
clc
close all

acs_files = dir(fullfile(pwd, '*.asc'));

for i=1:length(acs_files); 
    j = importdata(acs_files(i,1).name, '\t', 37);




    f8113=j.data(:,3);
    f8114=j.data(:,4);


    str=acs_files(i,1).name([11:13]);

        switch str
            case 'pos', 
            sign=1;
            case 'neg'
            sign=-1;
        end
        
    pitch(i)=str2num(acs_files(i,1).name([5:6]))*sign*0.1;
    F8113(i,1)=mean(f8113);
    F8114(i,1)=mean(f8114);

end

TotalForce=F8114-F8113;
A=[pitch;TotalForce']';
A=sortrows(A,1);

ForcePerPropeller=A(:,2)/2;
plot(A(:,1),ForcePerPropeller,'-x','LineWidth',2,...
                'MarkerEdgeColor','b',...
                'MarkerFaceColor','b',...
                'MarkerSize',10)
            
grid on
hold on
xlabel('VSP relative pitch');
ylabel('Force per propeller');

 [a,b]=polyfit(A(:,1),ForcePerPropeller,1);
 
axesLimits1 = xlim;
xplot1 = linspace(axesLimits1(1), axesLimits1(2));


Starting3=rand(1);
options=optimset('Display','final');
Estimates3=fminsearch(@actuator_fun_lin,Starting3,options,A(:,1),ForcePerPropeller)


% Evaluate polynomial
yplot1 = polyval(a, xplot1);
plot(A(:,1),Estimates3(1)*A(:,1),'r')
disp('Linear estimation:');
formula=['F=',num2str(a(1)),'p']


hold on

Starting=rand(1);
options=optimset('Display','iter');
Estimates=fminsearch(@actuator_fun,Starting,options,A(:,1),ForcePerPropeller)


Starting2=rand(1,2);
options=optimset('Display','final');
Estimates2=fminsearch(@actuator_fun2,Starting2,options,A(:,1),ForcePerPropeller)

hold on
plot(A(:,1),Estimates*abs(A(:,1)).*A(:,1),'g')


Starting=rand(1);
options=optimset('Display','iter');
Estimates=fminsearch(@actuator_fun_lin,Starting,options,A(:,1),ForcePerPropeller)

hold on
plot(A(:,1),Estimates2(1)*abs(A(:,1)).*A(:,1)+Estimates2(2)*A(:,1),'k')


legend('Measured data',['Linear fit ' formula ],['Nonlinear fit F=',num2str(Estimates),'*|p|p'],['Nonlinear fit F=',num2str(Estimates2(1)),'*|p|p + ',num2str(Estimates2(2)),'*p'],'Location','Best')

print -dpng VSPsurge.png -r500