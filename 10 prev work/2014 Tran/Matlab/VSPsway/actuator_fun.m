function err = actuator_fun(k,pitch,force)
% F=k*abs(pitc)*pitch

Fitted_Curve=k*abs(pitch).*pitch;

err = norm(Fitted_Curve-force);
