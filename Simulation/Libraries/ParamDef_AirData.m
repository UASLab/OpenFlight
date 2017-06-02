function [AirData] = ParamDef_AirData(type, AirData)
% Define the AirData Model Parameters

hz2rps = 2*pi;

AirData.errEnable = 1;

switch lower(type.sys)
    case {'pitot', 'pitotstatic'} % Simple Pitot-Static
        [AirData] = ParamDef_Pd(type.Pd, AirData);
        [AirData] = ParamDef_Ps(type.Ps, AirData);
        
        
        % Create Transfer Functions for the tube response
        AirData.tubeLength_m = 0.5; % FIXME - Aircraft Specific
        AirData.vSound_mps = 340; % FIXME - Environment Driven
        tubeBw_rps = AirData.vSound_mps / (4*AirData.tubeLength_m) * hz2rps; % Bandwidth
        tubeDamp_nd = 0.3; % Worst-case for resonable lengths
        
        AirData.tubeTF_num = [tubeBw_rps^2];
        AirData.tubeTF_den = [1, 2*tubeDamp_nd*tubeBw_rps, tubeBw_rps^2];
        
    case {'bird'} % NASA Birds
        [AirData] = ParamDef_Bird(AirData);
        
        % Time delay, measurement to signal
        AirData.timeDelay_s = 0.001; % (FIXME - Check all values!!)
    otherwise
end

function [AirData] = ParamDef_Ps(type, AirData)
% Static Pressure Transducer

hz2rps = 2*pi;

switch lower(type)
    case 'ams5915-1200-b' % (FIXME - Check all values!!)
        
        % Create Transfer Functions for the transducer response
        % Keep numerator and denominator seperate for entry into Simulink TF block
        % Static Pressure Transfer Function
        PsBw_rps = (0.35 / 0.001) * hz2rps; % Bandwidth, Rise time is 0.5-1.0 ms
        AirData.PsTF_num = PsBw_rps;
        AirData.PsTF_den = [1, PsBw_rps];
        
        % Temperature Transfer Function
        tempBw_rps = PsBw_rps; % Bandwidth
        AirData.tempTF_num = AirData.PsTF_num;
        AirData.tempTF_den = AirData.PsTF_den;
        
        % Time delay, measurement to signal
        AirData.PsTimeDelay_s = 1 / (100e3); % Assume 1 frame at slow I2C clock 100KHz
        AirData.tempTimeDelay_s = AirData.PsTimeDelay_s;
        
        % Dynamic Pressure Error Model
        AirData.PsScf = 1;
        AirData.PsBias = 0; % Pa
        AirData.PsSigma = 15.0 * 50; % Pa
        AirData.PsSeed = randi([1, intmax('int16')], 1); % Noise Seed
        
        % Temperature Error Model
        AirData.tempScf = 1;
        AirData.tempBias = 0; % K
        AirData.tempSigma = 0.5; % K
        AirData.tempSeed = randi([1, intmax('int16')], 1); % Noise Seed
    otherwise
end

function [AirData] = ParamDef_Pd(type, AirData)
% Dynamic Pressure Transducer

hz2rps = 2*pi;

switch lower(type)
    case 'ams5915-0020-d-b' % (FIXME - Check all values!!)
        
        % Create Transfer Functions for the transducer response
        % Keep numerator and denominator seperate for entry into Simulink TF block
        % Dynamic Pressure Transfer Function
        PdBw_rps = (0.35 / 0.001) * hz2rps; % Bandwidth, Rise time is 0.5-1.0 ms
        AirData.PdTF_num = PdBw_rps;
        AirData.PdTF_den = [1, PdBw_rps];
        
        % Temperature Transfer Function
        tempBw_rps = PdBw_rps; % Bandwidth
        AirData.tempTF_num = AirData.PdTF_num;
        AirData.tempTF_den = AirData.PdTF_den;
        
        % Time delay, measurement to signal
        AirData.PdTimeDelay_s = 1 / (100e3); % Assume 1 frame at slow I2C clock 100KHz
        AirData.tempTimeDelay_s = AirData.PdTimeDelay_s;
        
        % Dynamic Pressure Error Model
        AirData.PdScf = 1;
        AirData.PdBias = 0; % Pa
        AirData.PdSigma = 15.0 * 4; % Pa
        AirData.PdSeed = randi([1, intmax('int16')], 1); % Noise Seed
        
        % Temperature Error Model
        AirData.tempScf = 1;
        AirData.tempBias = 0; % K
        AirData.tempSigma = 0.5; % K
        AirData.tempSeed = randi([1, intmax('int16')], 1); % Noise Seed
    otherwise
end

function [AirData] = ParamDef_Bird(AirData) % (FIXME - Check all values!!)
% NASA "Bird" Null-Seeking Anemometers

hz2rps = 2*pi;

% Create Transfer Functions for the transducer response
% Keep numerator and denominator seperate for entry into Simulink TF block
% Anemometer Transfer Function
velBw_rps = 20 * hz2rps; % Bandwidth
AirData.velTF_num = velBw_rps;
AirData.velTF_den = [1, velBw_rps];

% Alpha Vane Transfer Function
alphaBw_rps = 10 * hz2rps; % Bandwidth
AirData.alphaTF_num = alphaBw_rps;
AirData.alphaTF_den = [1, alphaBw_rps];

% Beta Vane Transfer Function
betaBw_rps = 10 * hz2rps; % Bandwidth
AirData.betaTF_num = betaBw_rps;
AirData.betaTF_den = [1, betaBw_rps];

% Anemometer Error Model
AirData.velScf = 1;
AirData.velBias = 0; % m/s
AirData.velSigma = 0.001; % m/s
AirData.velSeed = randi([1, intmax('int16')], 1); % Noise Seed

% Alpha Vane Error Model
AirData.alphaScf = 1;
AirData.alphaBias = 0; % rad
AirData.alphaSigma = 0.0000005; % rad
AirData.alphaSeed = randi([1, intmax('int16')], 1); % Noise Seed

% Beta Vane Error Model
AirData.betaScf = 1;
AirData.betaBias = 0; % rad
AirData.betaSigma = 0.0000005; % rad
AirData.betaSeed = randi([1, intmax('int16')], 1); % Noise Seed

