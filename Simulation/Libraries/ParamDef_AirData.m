function [AirData] = ParamDef_AirData(AirData)
% Define the AirData Model Parameters



AirData.errEnable = 1;

switch lower(AirData.type)
    case {'pitot', 'pitotstatic'} % Simple Pitot-Static
        [AirData] = ParamDef_Pd(AirData);
        [AirData] = ParamDef_Ps(AirData);
        
        % Time delay, measurement to signal
        AirData.timeDelay_s = 0.001; % (FIXME - Check all values!!)
        
    case {'bird'} % NASA Birds
        [AirData] = ParamDef_Bird(AirData);
        
        % Time delay, measurement to signal
        AirData.timeDelay_s = 0.001; % (FIXME - Check all values!!)
    otherwise
end

function [AirData] = ParamDef_Ps(AirData)
% Static Pressure Transducer

hz2rps = 2*pi;

switch lower(AirData.typePs)
    case 'ams5915-1200-b' % (FIXME - Check all values!!)
        
        % Create Transfer Functions for the transducer response
        PsBand_rps = 100 * hz2rps; % Bandwidth
        tempBand_rps = 10 * hz2rps; % Bandwidth
        
        AirData.PsTF = tf([PsBand_rps], [1, PsBand_rps]);
        AirData.tempTF = tf([tempBand_rps], [1, tempBand_rps]);
        
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

function [AirData] = ParamDef_Pd(AirData)
% Dynamic Pressure Transducer

hz2rps = 2*pi;

switch lower(AirData.typePd)
    case 'ams5915-0020-d-b' % (FIXME - Check all values!!)
        
        % Create Transfer Functions for the transducer response
        PdBand_rps = 100 * hz2rps; % Bandwidth
        tempBand_rps = 10 * hz2rps; % Bandwidth
        
        AirData.PdTF = tf([PdBand_rps], [1, PdBand_rps]);
        AirData.tempTF = tf([tempBand_rps], [1, tempBand_rps]);
        
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
velBand_rps = 20 * hz2rps; % Bandwidth
alphaBand_rps = 10 * hz2rps; % Bandwidth
betaBand_rps = 10 * hz2rps; % Bandwidth

AirData.velTF = tf([velBand_rps], [1, velBand_rps]);
AirData.alphaTF = tf([alphaBand_rps], [1, alphaBand_rps]);
AirData.betaTF = tf([betaBand_rps], [1, betaBand_rps]);

% Anemometer Error Model
AirData.velScf = 1;
AirData.velBias = 0; % m/s
AirData.velSigma = 0.001; % m/s
AirData.velSeed = randi([1, intmax('int16')], 1); % Noise Seed

% Alpha Error Model
AirData.alphaScf = 1;
AirData.alphaBias = 0; % rad
AirData.alphaSigma = 0.0000005; % rad
AirData.alphaSeed = randi([1, intmax('int16')], 1); % Noise Seed

% Beta Error Model
AirData.betaScf = 1;
AirData.betaBias = 0; % rad
AirData.betaSigma = 0.0000005; % rad
AirData.betaSeed = randi([1, intmax('int16')], 1); % Noise Seed

