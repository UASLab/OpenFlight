function [Sim, Surf] = Config_Servo(Sim, Surf)
% Define the Control Surface Model Parameters

hz2rps = 2*pi;
d2r = pi/180;
%

%% Servo Model Parameters
switch lower(Sim.servoType)
    case lower({'Hitec_HS-5645MG', '5645'}) % HiTec HS-5645MG
        
        Surf.servoBw_rps = 3.43 * hz2rps; % Tested 10Jan2018, -3dB with 5 deg amplitude
        Surf.servoDamp_nd = 0.8; % FIXIT - Guess
        Surf.servoRateLim_rps = 300 * d2r; % Tested 10Jan2018
        Surf.servoLimPos_rad = 90 * d2r; % Guess
        Surf.servoLimNeg_rad = -90 * d2r; % Guess
        
        Surf.servoTimeDelay_s = 75.27 / 1000; % Tested 10Jan2018
        Surf.servoFreeplay_rad = 2.094 * d2r; % Tested 10Jan2018
        
    case lower({'Hitec_HS-5625MG', '5625'}) % HiTec HS-5625MG
        
        Surf.servoBw_rps = 3.52 * hz2rps; % Tested 10Jan2018, -3dB with 5 deg amplitude
        Surf.servoDamp_nd = 0.8; % FIXIT - Guess
        Surf.servoRateLim_rps = 440 * d2r; % Tested 10Jan2018
        Surf.servoLimPos_rad = 90 * d2r; % Guess
        Surf.servoLimNeg_rad = -90 * d2r; % Guess
        
        Surf.servoTimeDelay_s = 69.38 / 1000; % Tested 10Jan2018
        Surf.servoFreeplay_rad = 2.404 * d2r; % Tested 10Jan2018
        
    case lower({'Hitec_HS-225BB', '225BB'}) % HiTec HS-225BB
        
        Surf.servoBw_rps = 5.94211 * hz2rps; % Tested 11June2017, -3dB with 5 deg amplitude
        Surf.servoDamp_nd = 0.8; % FIXIT - Guess
        Surf.servoRateLim_rps = 560 * d2r; % Tested 11June2017
        Surf.servoLimPos_rad = 90 * d2r; % Guess
        Surf.servoLimNeg_rad = -90 * d2r; % Guess
        
        Surf.servoTimeDelay_s = 41.6667 / 1000; % Tested 11June2017
        Surf.servoFreeplay_rad = 0.960596 * d2r; % Tested 11June2017
        
    case lower({'Futaba_BLS471SV', 'BLS471SV'}) % Futaba BLS471SV
        % Tested using PMW Input @ 500 Hz update rate, 7.4 Volt, Stock Settings
        
        Surf.servoBw_rps = 25.8 * hz2rps; % Servo Bandwidth, Tested -3dB with 5 deg amplitude
        Surf.servoDamp_nd = 0.8; % FIXIT - Guess
        Surf.servoRateLim_rps = 880 * d2r; % Tested
        Surf.servoLimPos_rad = 90 * d2r; % Guess
        Surf.servoLimNeg_rad = -90 * d2r; % Guess
        
        Surf.servoTimeDelay_s = 10.85 / 1000; % Tested
        Surf.servoFreeplay_rad = 0.329 * d2r; % Tested
        
    otherwise
        
end


