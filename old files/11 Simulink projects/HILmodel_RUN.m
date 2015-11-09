

clear all;
clc;

m = 17.6;

M_RB    = [		m	0	0	0	0	0;
				0	m	0	0	0	0;
				0	0	m	0	0	0;
				0	0	0	inf	0	0;
				0	0	0	0	0	0;
				0	0	0	0	0	1.76];
			
M_A     = [		2	0	0	0	0	0;
				0	10	0	0	0	0;
				0	0	0	0	0	0;
				0	0	0	0	0	0;
				0	0	0	0	0	0;
				0	0	0	0	0	1];
			
D_L     = [		-0.59739	0	0	0	0	0;
				0	-3.50625	0	0	0	0.18140;
				0	0	0	0	0	0;
				0	0	0	0	0	0;
				0	0	0	0	0	0;
				0	-7.250	0	0	0	-1.900];
			
D_L = - D_L;

D_NLxx	= [		1	0   0   0   0   0;
                0   1   0   0   0   1;
                0   0   1   0   0   0;
                0   0   0   1   0   0;
                0   0   0   0   1   0;
                0   1   0   0   0   1];
        
D_NLxy	= [		0   0   0   0   0   0;
                0   1   0   0   0   1;
                0   0   0   0   0   0;
                0   0   0   0   0   0;
                0   0   0   0   0   0;
                0   1   0   0   0   1];