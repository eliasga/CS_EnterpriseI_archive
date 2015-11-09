##############################################
---          Simulation Guide              ---
##############################################
-   	    By: Andreas Orsten		     -
----------------------------------------------

In order to run the simulations from the master thesis, simply follow these steps:


	1. Open 'theProgram.m'

	2. Under "Simulation control panel", assign the desired simulation case to the variable 'simCase'

		a) For Scenario 6, to see the towline rupture, change 'simulationTime' to 600.

		b) For Scenario 7, to change the current angle, change cAngle to either pi, 0, or 5*pi/8

		c) For Scenario 8, the limitation is implemented when running. To alter this, open 'HIL_model_overall.slx' in Simulink, and do the following:

			i) Enter the blocks 
				'LOS controller' -> 'Reference Model' -> 'Reference Models' -> 'Velocity Reference'
			iia) To disconnect the limitation:
				Enter the block 'delta_T penalty' and disconnect the block 'Change limiter' from the loop.
			iib) To completely remove the penalty, disconnect the block 'delta_T penalty', and feed 'U_ref' directly into 'U'.

		d) For Scenario 9, to change the desired error percentage, alter the variable 'errPct'.

	3. Run 'theProgram.m' and watch the relevant graphs open.

To view animations of the simulations, simply open 'animation.m'

	1. To change the speed of the animation, alter the variable 'speedbump'. Higher speedbump gives faster animation.
