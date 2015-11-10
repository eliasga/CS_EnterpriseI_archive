clear
clc
close

asc_files = dir(fullfile(pwd, '*.asc'));

for i=1:length(asc_files); 
    j = importdata(asc_files(i,1).name, '\t', 37);



    %Time DEVICE_1 (Sample rate 1)	F8111	F8113	F8114	F8116
    f8111=j.data(:,2);
    f8113=j.data(:,3);
    f8114=j.data(:,4);
    f8116=j.data(:,5);


    str=asc_files(i,1).name([15:17]);

        % This might seems unlogical, but 'pos' for file names indicates
        % positive drive direction of the towing carriage, hence negative
        % sway speed due to SNAME convention.
        switch str
            case 'pos', 
            sign=-1;
            case 'neg'
            sign=1;
        end
        
    A(i,2)=mean(f8116)+mean(f8114)-mean(f8111)-mean(f8113);
    A(i,1)=str2double(asc_files(i,1).name([11:13]))*sign*0.01;

end

A=sortrows(A,1);    

plot(A(:,1),A(:,2),'-x','LineWidth',2,...
                'MarkerEdgeColor','b',...
                'MarkerFaceColor','b',...
                'MarkerSize',10,...
                'LineStyle','none');
            
grid on
hold on
xlabel('Sway speed (v) [m/s]');
ylabel('Towing force (\tau_y) [N]');



[a,b]=polyfit(A([3:11],1),A([3:11],2),1);
 
axesLimits1 = xlim;
xplot1 = linspace(axesLimits1(1), axesLimits1(2));


% Evaluate polynomial
yplot1 = polyval(a, xplot1);
plot(xplot1,yplot1,'r')

formula=['\tau_y=',num2str(a(1)),'v ']
legend('Measured data',['Linear fit ' formula '(for |u|\leq 0.2 m/s)'])

print -dpng swayDamping.png -r500