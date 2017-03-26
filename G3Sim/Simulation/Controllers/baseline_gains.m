% Baseline Gains
%
% This script will setup the baseline control law gains.
%
% University of Minnesota
% Aerospace Engineering and Mechanics
% Copyright 2011 Regents of the University of Minnesota.
% All rights reserved.
%

switch lower(AC.aircraft)
    
    case 'ultrastick120'
        
        %% ======================== Lateral Control =============================%%
        
        %%                         YAW DAMPER
        k_YD=0.065;
        a_YD=-2.0;
        K_YD=zpk(0,a_YD,k_YD);   % Washout filter
        K_YDz = c2d(K_YD,SampleTime);
        [YDz_num,YDz_den]=tfdata(K_YDz,'v'); % obtain discrete T.F. coefficients
        
        %%                         ROLL TRACKER
        kp_RT=-0.52;
        ki_RT=-0.20;
        kp_RD= -0.07;
        
        %% ====================== Longitudinal Control ==========================%%
        
        %%                         THETA TRACKER
        kp_PT=-.84;
        ki_PT=-.23;
        kp_PD=-.08;

    case 'ultrastick25e'
        
        %% ======================== Lateral Control =============================%%
        
        %%                         YAW DAMPER
        k_YD=0.065;
        a_YD=-2.0;
        K_YD=zpk(0,a_YD,k_YD);   % Washout filter
        K_YDz = c2d(K_YD,SampleTime);
        [YDz_num,YDz_den]=tfdata(K_YDz,'v'); % obtain discrete T.F. coefficients
        
        %%                         ROLL TRACKER
        kp_RT= -.64;
        ki_RT= -.2;
        kp_RD=  -0.07; % Roll damper
        
        %% ====================== Longitudinal Control ==========================%%
        
        %%                         THETA TRACKER
        kp_PT=-.9;
        ki_PT=-.3;
        kp_PD=-.08; % Pitch damper
        
end
