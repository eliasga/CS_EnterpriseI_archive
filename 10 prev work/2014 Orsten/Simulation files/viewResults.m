%% RESULT VIEWER FOR ICEBERG TOWING
% Always run 'theProgram.m' beforehand

%% Control panel
run = plotRun;


%% Data inlet
    % Time
    t = x_s.Time;
    T = length(t);

    % Ship position
    xShip = x_s.Data;
    yShip = y_s.Data;
    psiShip = psi_s.Data;
    
    % Iceberg position
    xIce = x_i.Data;
    yIce = y_i.Data;
    
    % Towline tension
    Ftow = tension.Data;
    
    % Tension statistics
    Tmean = meanT.Data;
    TstanDev = stanDevT.Data;
    dRupture = deltaRupture.Data;
    dSlippage = deltaSlippage.Data;
    dOverturn = deltaOverturn.Data;
    disCon = isDisconnected.Data;
    
    % Ship measured velocities
    uShip = nu_s.Data(:,1);
    vShip = nu_s.Data(:,2);
    rShip = nu_s.Data(:,3);
    
    % Iceberg measured velocities
    uIce = nu_i.Data(:,1);
    vIce = nu_i.Data(:,2);
    
    % Ship geometry
    shipL = shipLength;
    shipB = shipBeam;
    xLoc = shipL_d(1);
    yLoc = shipL_d(2);
    
    if inDataType == 2
    
        % Ship observed
        xObs = eta_s_est.Data(:,1);
        yObs = eta_s_est.Data(:,2);
        psiObs = eta_s_est.Data(:,3);

        % Ship pre-Reference position
        xRef = s_xRef.Data;
        yRef = s_yRef.Data;
        psiRef = s_psiRef.Data;

        % Ship desired position
        xDes = s_xDes.Data;
        yDes = s_yDes.Data;
        psiDes = s_psiDes.Data;
        
        % Ship Observer velocities
        uObs = nu_s_est.Data(:,1);
        vObs = nu_s_est.Data(:,2);
        rObs = nu_s_est.Data(:,3);
        
        % Ship observer biases
        xBias = b_s_est.Data(:,1);
        yBias = b_s_est.Data(:,2);
        psiBias = b_s_est.Data(:,3);
        
        % LOS iceberg integral term
        yInt = y_int.Data;
        
    end
    
    if simCase == 5 || simCase == 6
        
        % Get delta penalty
        dPen = delta_pen.Data;
        
        % Get tau_pen
        uPen = tauSystem.Data(:,1);
        vPen = tauSystem.Data(:,2);
        rPen = tauSystem.Data(:,3);
        
    end
    
    if simCase == 8
        
        dPen = delta_pen.Data;
        U_ref = Uref.Data;
        
    end
    
    if simCase == 9
        err = QSerror.Data;
    end

    
%% Figure 1: X-Y plot of vessel and iceberg measured trajectories, with waypoints
if run(1) == 1;
    figure(1);
    clf;
    plot(xShip, yShip, 'g'); 
    hold on;
    plot(xIce, yIce, 'b');
    plot(WP(:,1),WP(:,2),':*r');    
    axis equal;
    xlabel('X-position [m]');
    ylabel('Y-position [m]');
    legend('Vessel trajectory','Iceberg trajectory','Waypoints');   
    grid on;
    title('XY-plot of vessel and iceberg trajectories, with waypoints');
end

%% Figure 2: Measured, Observed, Pre-referenced, Desired positions of ship
if run(2) == 2
    figure(2);
    clf;
        % x-positions
        subplot(3,1,1);
        hold all;
        plot(t,xShip,'g');
        plot(t,xObs,'b');
        plot(t,xRef,'Color',[.5 .5 0]);
        plot(t,xDes,'r');
        xlabel('Time [s]');
        ylabel('X-position [m]');
        legend('x measured','x observed','x pre-reference','x desired');
        grid on;
        title('Vessel positions: $\eta_s$ vs $\hat{\eta}_s$ vs $\eta_{ref}$ vs $\eta_{d}$','interpreter','latex');

        % y-positions
        subplot(3,1,2);
        hold all;
        plot(t,yShip,'g');
        plot(t,yObs,'b');
        plot(t,yRef,'Color',[.5 .5 0]);
        plot(t,yDes,'r');
        xlabel('Time [s]');
        ylabel('Y-position [m]');
        legend('y measured','y observed','y pre-reference','y desired');
        grid on;

        % psi-positions
        subplot(3,1,3);
        hold all;
        plot(t,psiShip,'g');
        plot(t,psiObs,'b');
        plot(t,psiRef,'Color',[.5 .5 0]);
        plot(t,psiDes,'r');
        xlabel('Time [s]');
        ylabel('\psi-position [rad]');
        legend('\psi measured','\psi observed','\psi pre-reference','\psi desired');
        grid on;
end
    
%% Figure 3: Measure vs Observed vessel positions
if run(3) == 3
    
    figure(3);
    clf;
    
        % x-positions
        aa(1) = subplot(3,1,1);
        hold all;
        plot(t,xShip,'g');
        plot(t,xObs,'--k');
        
        if simCase == 9
            
            n = 0;
            for i=1:1:T

                e = err(i);
                if e == 1
                    n = n+1;
                else
                    if n > 0
                        patch([t(i-1-n) t(i-1-n) t(i-1) t(i-1)], [0.8 1 1 0.8], 'k');
                        n = 0;
                    end
                end

            end
            
        end
        
        xlabel('Time [s]');
        ylabel('X-position [m]');
        if simCase ~= 9
            legend('x measured','x observed');
        else
            legend('x measured','x observed','Meas. error');
        end
        grid on;
        
        % y-positions
        aa(2) = subplot(3,1,2);
        hold all;
        plot(t,yShip,'g');
        plot(t,yObs,'--k');
        xlabel('Time [s]');
        ylabel('Y-position [m]');
        legend('y measured','y observed');
        grid on;

        % psi-positions
        aa(3) = subplot(3,1,3);
        hold all;
        plot(t,psiShip,'g');
        plot(t,psiObs,'--k');
        xlabel('Time [s]');
        ylabel('\psi-position [rad]');
        legend('\psi measured','\psi observed');
        grid on;
        
        linkaxes(aa,'x');
    
end
    
%% Figure 4: X-Y plot of vessel and iceberg measured trajectories, without waypoints, WITH yaw angles added (and disconnection point)
if run(4) == 4
    figure(4);
    clf;
    sTraj = plot(xShip, yShip, 'g'); 
    hold on;
    iTraj = plot(xIce, yIce, 'b');
    step = 100; %deciseconds
    len = 1;
    for i=1:step:T
        sYaw = plot_arrow(xShip(i),yShip(i),xShip(i)+len*cos(psiShip(i)),yShip(i)+len*sin(psiShip(i)),'color','red','linewidth',1);
        iPos = plot(xIce(i), yIce(i), 'ob');
    end
    if sum(disCon) > 0
       disInst = find(disCon==1,1)
       dcp = plot(xShip(disInst),yShip(disInst),'*r');
       plot(xIce(disInst),yIce(disInst),'*r');
    end
    axis equal;
    xlabel('X-position [m]');
    ylabel('Y-position [m]');
    if sum(disCon) == 0
        legend([sTraj,iTraj,sYaw(1),iPos(1)],'Vessel trajectory','Iceberg trajectory','Vessel yaw angles','Iceberg positions'); 
    else
        legend([sTraj,iTraj,sYaw(1),iPos(1),dcp],'Vessel trajectory','Iceberg trajectory','Vessel yaw angles','Iceberg positions','Disconnection point'); 
    end
    grid on;
    title(['XY-plot of vessel and iceberg. Yaw and corresponding iceberg pos. every ' num2str(step/10) 's.']);
end
    
%% Figure 5: Tension plots
if run(5) == 5
    figure(5);
    clf;
    tow = plot(t,Ftow, '-r');
    xlabel('Time [s]');
    ylabel('Tension [N]');
    grid on;
end
    
%% Figure 6: Tension plots, with tension, mean tension, variance
if run(6) == 6
    figure(6);
    clf;
        % Tension and mean tension
        subplot(2,1,1);
        hold all;
        plot(t,Ftow, '-r');
        plot(t,Tmean,'-b');
        xlabel('Time [s]');
        ylabel('Tension [N]');
        legend('T(t)','Mean T(t)');
        grid on;
        
        % Standard deviation
        subplot(2,1,2);
        plot(t,TstanDev,'-b');
        xlabel('Time [s]');
        ylabel('Tension [N]');
        legend('Standard deviation \sigma_T');
        grid on;
        
end
    
%% Figure 7: Pre-reference modeled ship position vs desired ship position
if run(7) == 7
    
    figure(7);
    clf;
    
        % x-positions
        subplot(3,1,1);
        hold all;
        plot(t,xRef,'g');
        plot(t,xDes,'k');
        xlabel('Time [s]');
        ylabel('X-position [m]');
        legend('x pre-reference','x desired');
        grid on;
        
        % y-positions
        subplot(3,1,2);
        hold all;
        plot(t,yRef,'g');
        plot(t,yDes,'k');
        xlabel('Time [s]');
        ylabel('Y-position [m]');
        legend('y pre-reference','y desired');
        grid on;

        % psi-positions
        subplot(3,1,3);
        hold all;
        plot(t,psiRef,'g');
        plot(t,psiDes,'k');
        xlabel('Time [s]');
        ylabel('\psi-position [rad]');
        legend('\psi pre-reference','\psi desired');
        grid on;
    
end

%% Figure 8: Observer velocity performance, measured vs observed velocities
if run(8) == 8
    
    figure(8);
    clf;
    
        % x-positions
        subplot(3,1,1);
        hold all;
        plot(t,uShip,'g');
        plot(t,uObs,'k');
        xlabel('Time [s]');
        ylabel('Surge velocity [m/s]');
        legend('u measured','u observed');
        grid on;
        
        % y-positions
        subplot(3,1,2);
        hold all;
        plot(t,vShip,'g');
        plot(t,vObs,'k');
        xlabel('Time [s]');
        ylabel('Sway velocity [m/s]');
        legend('v measured','v observed');
        grid on;

        % psi-positions
        subplot(3,1,3);
        hold all;
        plot(t,rShip,'g');
        plot(t,rObs,'k');
        xlabel('Time [s]');
        ylabel('Yaw velocity [rad/s]');
        legend('r measured','r observed');
        grid on;
    
end

%% Figure 9: Observer biases in x,y,psi
if run(9) == 9
    
    figure(9);
    clf;
    
        % x-bias
        subplot(3,1,1);
        hold all;
        plot(t,xBias,'g');
        xlabel('Time [s]');
        ylabel('Force [N]');
        legend('Bias Force x-dir');
        grid on;
        
        % y-bias
        subplot(3,1,2);
        hold all;
        plot(t,yBias,'g');
        xlabel('Time [s]');
        ylabel('Force [N]');
        legend('Bias Force y-dir');
        grid on;

        % psi-bias
        subplot(3,1,3);
        hold all;
        plot(t,psiBias,'g');
        xlabel('Time [s]');
        ylabel('Momentum [Nm]');
        legend('Bias Force psi-dir');
        grid on;
    
end

%% Figure 10: X-Y plot of vessel and iceberg measured trajectories, without waypoints, WITH vessel projections added (and disconnection point)
if run(10) == 10
    figure(10);
    clf;
    sTraj = plot(xShip, yShip, 'g'); 
    hold on;
    iTraj = plot(xIce, yIce, 'b');
    step = 150; %deciseconds
    len = 1;
    if sum(disCon) > 0
       disInst = find(disCon==1,1);
       dcp = plot(xShip(disInst),yShip(disInst),'*r');
       plot(xIce(disInst),yIce(disInst),'*r');
    end
    for i=1:step:T
        
        % Plot ship projection
        [x1, y1] = rotateShipPos(xShip(i), yShip(i), -xLoc, -shipB/2, psiShip(i));
        [x2, y2] = rotateShipPos(xShip(i), yShip(i), -xLoc, shipB/2, psiShip(i));
        [x3, y3] = rotateShipPos(xShip(i), yShip(i), 0.8*shipL - xLoc, shipB/2, psiShip(i));
        [x4, y4] = rotateShipPos(xShip(i), yShip(i), shipL - xLoc, 0, psiShip(i));
        [x5, y5] = rotateShipPos(xShip(i), yShip(i), 0.8*shipL - xLoc, -shipB/2, psiShip(i));
    
        shipPlot = patch( [x1 x2 x3 x4 x5], [y1 y2 y3 y4 y5], 'g');
        set(shipPlot,'facealpha',0.1);
        set(shipPlot,'edgealpha',0.5);
        
        % Iceberg projection
        circleSteps = 0:pi/10:2*pi;
        xunit = 0.5*iceDiameter * cos(circleSteps) + xIce(i);
        yunit = 0.5*iceDiameter * sin(circleSteps) + yIce(i);
        iPos = patch( xunit, yunit, 'b' );
        set(iPos, 'facealpha', 0.1 );
        set(iPos, 'edgealpha', 0.5 );
        
        % Towline plot
        if sum(disCon) == 0 || (sum(disCon) > 0 && i < disInst)
            [xS, yS] = rotateShipPos(xShip(i), yShip(i), -xLoc, 0, psiShip(i));
            towLine = line( [xIce(i) xS] , [yIce(i) yS], 'LineStyle', '-', 'Color', 'r');
        end
    end
    axis equal;
    xlabel('X-position [m]');
    ylabel('Y-position [m]');
    if sum(disCon) == 0
        theLeg = legend([sTraj,iTraj,shipPlot,iPos, towLine],'Vessel trajectory','Iceberg trajectory','Vessel projection','Iceberg projection','Towline'); 
    else
        theLeg = legend([sTraj,iTraj,shipPlot,iPos,towLine,dcp],'Vessel trajectory','Iceberg trajectory','Vessel projection','Iceberg projection','Towline','Disconnection point'); 
    end
    shLegend = findobj(theLeg, 'Type', 'patch');
    set(shLegend, 'facea', 0.1);
    grid on;
    title(['XY-plot of vessel and iceberg. Vessel and iceberg projected every ' num2str(step/10) 's.']);
end

%% Figure 11: Only delta-indices
if run(11) == 11
    % Delta indexes
    figure(11);
    clf;
        hold all;
        plot(t,dRupture,'-b');
        plot(t,ruptureLimit*ones(length(t),1),'--b','LineWidth',2);
        plot(t,dSlippage,'-r');
        plot(t,slippageLimit*ones(length(t),1),'--r','LineWidth',2);
        plot(t,dOverturn,'-g');
        plot(t,overturnLimit*ones(length(t),1),'--g','LineWidth',2);
        xlabel('Time [s]');
        ylabel('Delta value [-]');
        legend('\delta Rupture','Rupture limit','\delta Slippage','Slippage limit','\delta Overturning','Overturning limit');
        grid on;
end
        
%% Figure 12: Only delta_rupture
if run(12) == 12
    figure(12);
    clf;
        hold all;
        plot(t,dRupture,'-b');
        if simCase == 8
            plot(t,ruptureLimitRef*ones(length(t),1),'--b','LineWidth',2);
        else
            plot(t,ruptureLimit*ones(length(t),1),'--b','LineWidth',2);
        end
        plot(t,ruptureNear*ones(length(t),1),'--g','LineWidth',2);
        xlabel('Time [s]');
        ylabel('Delta value [-]');
        legend('\delta Rupture','Rupture limit','Rupture near');
        grid on;    
end

%% Figure 13: Show delta penalty
if run(13) == 13
    
    figure(13);
    clf;
        plot(t,dPen.*100,'-r');
        xlabel('Time [s]');
        ylabel('Penalty percentage [%]');
        grid on;
    
end

%% Figure 14: Ship velocities
if run(14) == 14
    
    figure(14);
    clf;
        subplot(3,1,1);
        plot(t,uShip,'-b');
        xlabel('Time [s]');
        ylabel('Surge Velocity [m/s]');
        grid on;
        subplot(3,1,2);
        plot(t,vShip,'-b');
        xlabel('Time [s]');
        ylabel('Sway Velocity [m/s]');
        grid on;
        subplot(3,1,3);
        plot(t,rShip,'-b');
        xlabel('Time [s]');
        ylabel('Yaw Velocity [rad/s]');
        grid on;
    
end

%% Figure 15: Force input to system
if run(15) == 15
    
    figure(15);
    clf;
        subplot(3,1,1);
        plot(t,uPen,'-b');
        xlabel('Time [s]');
        ylabel('Surge Force [N]');
        grid on;
        
        subplot(3,1,2);
        plot(t,vPen,'-b');
        xlabel('Time [s]');
        ylabel('Sway Force [N]');
        grid on;
        
        subplot(3,1,3);
        plot(t,rPen,'-b');
        xlabel('Time [s]');
        ylabel('Yaw Force [Nm]');
        grid on;
    
end

%% Figure 16: X-Y plot of vessel and iceberg measured trajectories, with waypoints, WITH vessel projections added, WITH current arrow (and disconnection point)
if run(16) == 16
    figure(16);
    clf;
    sTraj = plot(xShip, yShip, 'g'); 
    hold on;
    iTraj = plot(xIce, yIce, 'b');
    step = 1000; %deciseconds
    len = 1;
    if sum(disCon) > 0
       disInst = find(disCon==1,1);
       dcp = plot(xShip(disInst),yShip(disInst),'*r');
       plot(xIce(disInst),yIce(disInst),'*r');
    end
    for i=1:step:T
        
        % Plot ship projection
        [x1, y1] = rotateShipPos(xShip(i), yShip(i), -xLoc, -shipB/2, psiShip(i));
        [x2, y2] = rotateShipPos(xShip(i), yShip(i), -xLoc, shipB/2, psiShip(i));
        [x3, y3] = rotateShipPos(xShip(i), yShip(i), 0.8*shipL - xLoc, shipB/2, psiShip(i));
        [x4, y4] = rotateShipPos(xShip(i), yShip(i), shipL - xLoc, 0, psiShip(i));
        [x5, y5] = rotateShipPos(xShip(i), yShip(i), 0.8*shipL - xLoc, -shipB/2, psiShip(i));
    
        shipPlot = patch( [x1 x2 x3 x4 x5], [y1 y2 y3 y4 y5], 'g');
        set(shipPlot,'facealpha',0.1);
        set(shipPlot,'edgealpha',0.5);
        
        % Iceberg projection
        circleSteps = 0:pi/10:2*pi;
        xunit = 0.5*iceDiameter * cos(circleSteps) + xIce(i);
        yunit = 0.5*iceDiameter * sin(circleSteps) + yIce(i);
        iPos = patch( xunit, yunit, 'b' );
        set(iPos, 'facealpha', 0.1 );
        set(iPos, 'edgealpha', 0.5 );
        
        % Towline plot
        if sum(disCon) == 0 || (sum(disCon) > 0 && i < disInst)
            [xS, yS] = rotateShipPos(xShip(i), yShip(i), -xLoc, 0, psiShip(i));
            towLine = line( [xIce(i) xS] , [yIce(i) yS], 'LineStyle', '-', 'Color', 'r');
        end
    end
    plotWP = plot(WP(:,1),WP(:,2),':*r');   
    
    % Plot current
    cStart = [4; -3];
    len = 2;
    cStop = cStart + len*[cos(cAngle); sin(cAngle)];
    plotCurrent = plot_arrow(cStart(1),cStart(2),cStop(1),cStop(2),'Color','k','LineWidth',2);
    
    axis equal;
    xlabel('X-position [m]');
    ylabel('Y-position [m]');
    if sum(disCon) == 0
        theLeg = legend([sTraj,iTraj,shipPlot,iPos, towLine,plotWP,plotCurrent(1)],'Vessel trajectory','Iceberg trajectory','Vessel projection','Iceberg projection','Towline','Waypoints','Current direction'); 
    else
        theLeg = legend([sTraj,iTraj,shipPlot,iPos,towLine,dcp,plotWP,plotCurrent(1)],'Vessel trajectory','Iceberg trajectory','Vessel projection','Iceberg projection','Towline','Disconnection point','Waypoints','Current direction'); 
    end
    shLegend = findobj(theLeg, 'Type', 'patch');
    set(shLegend, 'facea', 0.1);
    grid on;
    title(['XY-plot of vessel and iceberg. Vessel and iceberg projected every ' num2str(step/10) 's.']);
end

%% Figure 17: Iceberg LOS y_int
if run(17) == 17
    
    figure(17);
    clf;
    
        plot(t,yInt,'-b');
        xlabel('Time [s]');
        ylabel('Distance [m]');
        legend('LOS iceberg integral term, y_{int}');
        grid on;
    
end

%% Figure 18: Velocity reference vs. measured absolute velocity
if run(18) == 18
    
    figure(18);
        clf;
    
        U_abs = sqrt(uShip.^2 + vShip.^2);
        
        hold all;
        plot(t,U_ref,'-b');
        plot(t,U_abs,'-r');
        xlabel('Time [s]');
        ylabel('Velocity [m/s]');
        legend('U_{ref,i}','|u_s|');
        grid on;
    
    
end

%% Figure 19: Positioning error
if run(19) == 19
    
    figure(19);
    clf;
    
    n = 0;
    for i=1:1:T
        
        e = err(i);
        if e == 1
            n = n+1;
        else
            if n > 0
                patch([t(i-1-n) t(i-1-n) t(i-1) t(i-1)], [0 1 1 0], 'k');
                n = 0;
            end
        end
        
    end
        xlabel('Time [s]');
        legend('Measurement error');
        xlim([0 t(T)]);
        grid off;
    
    
end

%% Figure 20: surge Ship velocities
if run(20) == 20
    
    figure(20);
    clf;
        plot(t,uShip,'-b');
        xlabel('Time [s]');
        ylabel('Surge Velocity [m/s]');
        grid on;
    
end

%% Figure 21: surge Force input to system
if run(21) == 21
    
    figure(21);
    clf;
        plot(t,uPen,'-b');
        xlabel('Time [s]');
        ylabel('Surge Force [N]');
        grid on;
    
end

