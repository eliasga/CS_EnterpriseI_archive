clc
%close all

%% User control panel
    % View ship observer?
    showObs = 0;
    
    % Animation speedbump (Shows only every (speedbump) instance)
    speedbump = 15;

    
%% Animation being performed
% Animation Field
fieldX = -8:16;
fieldY = -3.225:6.45/10:3.225;

% Error
if inDataType == 2
    error = QSerror.Data;
end

% Ship
    % Ship position data
    animTime = squeeze(x_s.Time);
    xShip = squeeze(x_s.Data);
    yShip = squeeze(y_s.Data);
    psiShip = squeeze(psi_s.Data);
    
    % Ship geometry
    shipL = shipLength;
    shipB = shipBeam;
    xLoc = shipL_d(1);
    yLoc = shipL_d(2);
    
    if inDataType == 2
        % Observer ship position data
        xShipO = eta_s_est.Data(:,1);
        yShipO = eta_s_est.Data(:,2);
        psiShipO = eta_s_est.Data(:,3);

        % desired Ship Position
        desX = s_xDes.Data(:,1);
        desY = s_yDes.Data(:,1);

        % Pre-reference Ship Position
        refX = s_xRef.Data(:,1);
        refY = s_yRef.Data(:,1);
    end
    
    % Ship velocities
    u_s = nu_s.Data(:,1);
    v_s = nu_s.Data(:,2);
    r_s = nu_s.Data(:,3);
    
% Iceberg
    % Iceberg position data
    xIce = squeeze(x_i.Data);
    yIce = squeeze(y_i.Data);
    
    % Iceberg velocity data
    uIce = nu_i.Data(:,1);
    vIce = nu_i.Data(:,2);
    
    % Iceberg geometry
    iceD = iceDiameter;
    circleSteps = 0:pi/20:2*pi;
    
    if inDataType == 2
        % desired Iceberg course
        iCourse = alphaIceberg.Data(:,1);
    end

% Initiate ship and iceberg positions

    % Draw field
    figure(100);
    axis([fieldX(1) fieldX(end) fieldY(1) fieldY(end)])
    axis tight
    axis equal
    hold all
    grid on
    grid minor
    line( [fieldX(1) fieldX(end)] , [fieldY(1) fieldY(1)] );
    line( [fieldX(1) fieldX(end)] , [fieldY(end) fieldY(end)] );
    line( [fieldX(1) fieldX(1)] , [fieldY(1) fieldY(end)] );
    line( [fieldX(end) fieldX(end)] , [fieldY(1) fieldY(end)] );
    
    % Plot Observed Ship
    if showObs == 1
        [x1O, y1O] = rotateShipPos(xShipO(1), yShipO(1), -xLoc, -shipB/2, psiShipO(1));
        [x2O, y2O] = rotateShipPos(xShipO(1), yShipO(1), -xLoc, shipB/2, psiShipO(1));
        [x3O, y3O] = rotateShipPos(xShipO(1), yShipO(1), 0.8*shipL - xLoc, shipB/2, psiShipO(1));
        [x4O, y4O] = rotateShipPos(xShipO(1), yShipO(1), shipL - xLoc, 0, psiShipO(1));
        [x5O, y5O] = rotateShipPos(xShipO(1), yShipO(1), 0.8*shipL - xLoc, -shipB/2, psiShipO(1));

        shipO = fill( [x1O x2O x3O x4O x5O], [y1O y2O y3O y4O y5O], 'g');
    end
    
    % Plot ship
    [x1, y1] = rotateShipPos(xShip(1), yShip(1), -xLoc, -shipB/2, psiShip(1));
    [x2, y2] = rotateShipPos(xShip(1), yShip(1), -xLoc, shipB/2, psiShip(1));
    [x3, y3] = rotateShipPos(xShip(1), yShip(1), 0.8*shipL - xLoc, shipB/2, psiShip(1));
    [x4, y4] = rotateShipPos(xShip(1), yShip(1), shipL - xLoc, 0, psiShip(1));
    [x5, y5] = rotateShipPos(xShip(1), yShip(1), 0.8*shipL - xLoc, -shipB/2, psiShip(1));
    
    ship = fill( [x1 x2 x3 x4 x5], [y1 y2 y3 y4 y5], 'r');
    
    % Angular circle
    Axstart = 10;
    Aystart = -10;
    Alen = 3;
    N = 20;
    t = 2*pi/N*(1:N); 
    fill(Axstart+Alen*cos(t), Aystart+Alen*sin(t), 'w');
    
    % Add current direction
    Cxstop = Axstart + Alen*cos(cAngle);
    Cystop = Aystart + Alen*sin(cAngle);

    plot_arrow(Axstart,Aystart,Cxstop,Cystop,'color','black','linewidth',1);
    
    % Initiate ship heading arrow
    Sxstop = Axstart + Alen*cos(psiShip(1));
    Systop = Aystart + Alen*sin(psiShip(1));

    shipHeading = line([Axstart Sxstop],[Aystart Systop],'color','red','linewidth',1);
    
    % Initiate ship velocity text
    uText = text(-5,-8,sprintf(' surge velocity: %5.3f m/s \n sway velocity: %5.3f m/s \n current velocity: %5.3f m/s',u_s(1), v_s(1), cVelocity),'BackgroundColor',[.8 .8 .8]);
    
    % Plot iceberg
    xunit = 0.5*iceD * cos(circleSteps) + xIce(1);
    yunit = 0.5*iceD * sin(circleSteps) + yIce(1);
    iceberg = fill( xunit, yunit, 'c');
    %iceberg = plot(xunit, yunit);
    
    % Initiate iceberg heading arrow
    iAngle = atan2( vIce(1), uIce(1) );
    Ixstop = Axstart + Alen*cos(iAngle);
    Iystop = Aystart + Alen*sin(iAngle);
    
    iceHeading = line([Axstart Ixstop], [Aystart Iystop],'color','blue','linewidth',1);
    
    % Plot tow line
    [xS, yS] = rotateShipPos(xShip(1), yShip(1), -xLoc, 0, psiShip(1));
    towLine = line( [xIce(1) xS] , [yIce(1) yS] );

    % Write time
    time = title([num2str(0) ':' num2str(0)]);
    
    % Draw waypoints
    if viewWaypoints == 1
        plot(WP(:,1),WP(:,2),'-*r');
    end
    
    if inDataType == 2
        % Initiate desired iceberg heading arrow
        iDes_xstop = Axstart + Alen*cos(iCourse(1));
        iDes_ystop = Aystart + Alen*sin(iCourse(1));
        iDesCourse = line([Axstart iDes_xstop], [Aystart iDes_ystop],'color',[.5 .5 1],'linewidth',2);

        % Initiate desired ship position point
        desShipPos = plot(desX(1),desY(1),'*','color',[.5 .5 1]);

        % Initiate pre-referenced ship position point
        refShipPos = plot(refX(1),refY(1),'*','color',[.2 .7 1]);
    
        % Legend handling
        legend([shipHeading, iceHeading, iDesCourse,desShipPos,refShipPos],{'Ship Heading','Iceberg Course','Desired Iceberg Course','Desired ship position','Pre-referenced ship position'})
        
    end
    
% Generate animation
icebergTraceX = zeros(length(psiShip),1);
icebergTraceY = zeros(length(psiShip),1);
for i=1:speedbump:length(psiShip)
    
    % Redraw observer ship
    if showObs == 1
        % Ship corner positions
        [x1O, y1O] = rotateShipPos(xShipO(i), yShipO(i), -xLoc, -shipB/2, psiShipO(i));
        [x2O, y2O] = rotateShipPos(xShipO(i), yShipO(i), -xLoc, shipB/2, psiShipO(i));
        [x3O, y3O] = rotateShipPos(xShipO(i), yShipO(i), 0.8*shipL - xLoc, shipB/2, psiShipO(i));
        [x4O, y4O] = rotateShipPos(xShipO(i), yShipO(i), shipL - xLoc, 0, psiShipO(i));
        [x5O, y5O] = rotateShipPos(xShipO(i), yShipO(i), 0.8*shipL - xLoc, -shipB/2, psiShipO(i));

        % Redraw Ship
        set(shipO,'XData',[x1O x2O x3O x4O x5O],'YData',[y1O y2O y3O y4O y5O]);
    end
    
    % Ship corner positions
    [x1, y1] = rotateShipPos(xShip(i), yShip(i), -xLoc, -shipB/2, psiShip(i));
    [x2, y2] = rotateShipPos(xShip(i), yShip(i), -xLoc, shipB/2, psiShip(i));
    [x3, y3] = rotateShipPos(xShip(i), yShip(i), 0.8*shipL - xLoc, shipB/2, psiShip(i));
    [x4, y4] = rotateShipPos(xShip(i), yShip(i), shipL - xLoc, 0, psiShip(i));
    [x5, y5] = rotateShipPos(xShip(i), yShip(i), 0.8*shipL - xLoc, -shipB/2, psiShip(i));
    
    % Redraw Ship
    set(ship,'XData',[x1 x2 x3 x4 x5],'YData',[y1 y2 y3 y4 y5]);
        
    % Redraw Ship heading
    Sxstop = Axstart + Alen*cos(psiShip(i));
    Systop = Aystart + Alen*sin(psiShip(i));
    set(shipHeading,'XData',[Axstart Sxstop],'YData',[Aystart Systop]);
    
    % Draw iceberg trace
    icebergTraceX(i) = xIce(i);
    icebergTraceY(i) = yIce(i);
    iTraceX = icebergTraceX(1:speedbump:i);
    iTraceY = icebergTraceY(1:speedbump:i);
    plot(iTraceX,iTraceY,'color','blue');
    
    % Redraw Iceberg
    xunit = 0.5*iceD * cos(circleSteps) + xIce(i);
    yunit = 0.5*iceD * sin(circleSteps) + yIce(i);
    set(iceberg,'XData',xunit,'YData',yunit);
    
    % Redraw iceberg heading
    iAngle = atan2( vIce(i), uIce(i) );
    Ixstop = Axstart + Alen*cos(iAngle);
    Iystop = Aystart + Alen*sin(iAngle);
    set(iceHeading,'XData',[Axstart Ixstop],'YData',[Aystart Iystop]);
    
    % Redraw Tow Line
    [xS, yS] = rotateShipPos(xShip(i), yShip(i), -xLoc, 0, psiShip(i));
    set(towLine,'XData',[xIce(i) xS],'YData',[yIce(i) yS]);
        
    if inDataType == 2
        % Redraw ship color if pos error
        if error(i) == 0
            set(ship,'FaceColor',[1 0 0]);
        else
            set(ship,'FaceColor',[0 0 0]);
        end

        % Redraw Desired Iceberg Course
        iDes_xstop = Axstart + Alen*cos(iCourse(i));
        iDes_ystop = Aystart + Alen*sin(iCourse(i));
        set(iDesCourse,'XData',[Axstart iDes_xstop], 'YData', [Aystart iDes_ystop]);

        % Redraw Desired Ship position
        set(desShipPos,'XData',desX(i),'YData',desY(i));

        % Redraw pre-Referenced Ship position
        set(refShipPos,'XData',refX(i),'YData',refY(i));
    end
    
    % Update velocities
    set(uText,'str',sprintf(' surge velocity: %5.3f m/s \n sway velocity: %5.3f m/s \n current velocity: %5.3f m/s',u_s(i), v_s(i), cVelocity))
    
    % Update timer
    theMin = floor(animTime(i)/60);
    theSec = floor(animTime(i)) - theMin*60;
    set(time,'str',[num2str(theMin) ':' num2str(theSec)]);
    
    
    if i < length(psiShip)
        pause( (animTime(i+1) - animTime(i))/10 );
    end
    
end






