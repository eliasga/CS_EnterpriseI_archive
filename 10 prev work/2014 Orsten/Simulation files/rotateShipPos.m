function [xGlobal, yGlobal] = rotateShipPos(x, y, xLoc, yLoc, psiShip)

d = sqrt( xLoc^2 + yLoc^2 );
alpha = atan2( yLoc, xLoc );


xGlobal = x + d*cos(psiShip + alpha);
yGlobal = y + d*sin(psiShip + alpha);
