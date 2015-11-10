clear
clc
close all

acs_files = dir(fullfile(pwd, '*.asc'));


for i=1:length(acs_files); 

    j = importdata(acs_files(i,1).name, '\t', 37);

    f1=j.data(:,2);
    f2=j.data(:,3);
    speed=j.data(:,4);

    A(i,1)=mean(speed);
    A(i,2)=mean(f2)-mean(f1);
end

A=sortrows(A,1);
cfg=plot(A(:,1),A(:,2),'-x','LineWidth',2,...
                'MarkerEdgeColor','b',...
                'MarkerFaceColor','b',...
                'MarkerSize',10,...
                'LineStyle','none');
            
grid on
hold on
xlabel('Surge speed [m/s]');
ylabel('Surge force [N]');
axis([-0.65 0.65 -1.3 1.3]);


% Extract the linear part |u|<0.2 m/s

A=A([13:42],:);

            
grid on
hold on
xlabel('Surge speed (u) [m/s]');
ylabel('Surge force (\tau_x) [N]');

[a,b]=polyfit(A(:,1),A(:,2),1);
 
axesLimits1 = xlim;
xplot1 = linspace(axesLimits1(1), axesLimits1(2));


% Evaluate polynomial
yplot1 = polyval(a, xplot1);
plot(xplot1,yplot1,'r');

formula=['\tau_x=',num2str(a(1)),'u'];
legend('Measured data',['Linear fit ' formula ' (for |u|\leq 0.2 m/s)'])

print -dpng surgeDamping.png -r500
