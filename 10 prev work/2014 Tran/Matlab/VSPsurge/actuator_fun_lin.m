function err = actuator_fun_lin(k,pitch,force)
% F=k*abs(pitc)*pitch

%Fitted_Curve=k*abs(pitch).*pitch;
Fitted_Curve=k*pitch;

err = norm(Fitted_Curve-force);
