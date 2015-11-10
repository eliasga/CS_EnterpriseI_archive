function err = actuator_fun2(k,pitch,force)
% F=k*abs(pitc)*pitch

Fitted_Curve=k(1)*abs(pitch).*pitch +k(2)*pitch;

err = norm(Fitted_Curve-force);
