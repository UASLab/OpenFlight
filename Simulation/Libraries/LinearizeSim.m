function [linmodel] = LinearizeSim(simModel, Sim)
% [longmod, spmod, latmod, linmodel = LinearizeSim(simModel, Sim)
%
% Linearizes the UAV model about a given operating point.
% This function will use your workspace variables. 
% Requires the Control System Toolbox and Simulink Control Design.
%
% Inputs:
%
% Outputs:
%   longmod  - longitudinal linear model
%   spmod    - short period approximation
%   latmod   - lateral directional linear model
%   linmodel - full linear model
%
%
% University of Minnesota 
% Aerospace Engineering and Mechanics 
% Copyright 2017 Regents of the University of Minnesota. 
% All rights reserved.
%

%% Load model into memory
isLoaded = bdIsLoaded(simModel); % check to see if model is loaded or open
if ~isLoaded
    load_system(simModel) % load model into system memory without opening diagram
end

%% LINEARIZE

% Set Inputs
% Model is setup with input pertubations on the desired system inputs
Sim.Trim.io = getlinio(simModel);
% inList = get(Sim.Trim.opSpec.Inputs, 'Block');
% numIn = length(Sim.Trim.io);
% 
% for indxIn = 1:numIn 
%     Sim.Trim.io(indxIn) = linio(inList{indxIn}, indxIn, 'in');
% end

% Set Outputs
outList = get(Sim.Trim.opSpec.Outputs, 'Block');
% numOut = length(outList);
% 
% for indxOut = 1:numOut 
%     Sim.Trim.io(numIn + indxOut)  = linio(outList{indxOut}, indxOut, 'out');
% end

type = get(Sim.Trim.io, 'Type');

%% Obtain lineariziation
linOpt = linearizeOptions;
linmodel = linearize(simModel, Sim.Trim.opPoint, Sim.Trim.io, linOpt);



%% Fix I/O and State Names
% inListSig = [Sim.Trim.MotorNames, Sim.Trim.SurfNames];
% set(linmodel, 'InputName', inListSig);


outListSig = strrep(outList, [simModel '/'], '');
set(linmodel, 'OutputName', outListSig);

        
        %% GENERATE LONGITUDINAL LINEAR MODEL
        % Longitudinal dynamics
        % States: u(7)  w(9)  q(5) theta(2) Ze(12) omega(13)
        % Inputs: elevator(2) throttle(1)
        % Outputs: Vs(10) alpha(12) q(5) theta(2) h (13) ax(7) az(9)
        
        % Generate State-space matrices for Longitudinal Model
        % Indices for desired state, outputs, and inputs
%         Xlon = [7 9 5 2 12 13];
%         Ylon = [10 12 5 2 13 7 9];
%         Ilon = [2 1];
%         longmod = modred(linmodel(Ylon, Ilon), setdiff(1:13, Xlon), 'Truncate');
%         longmod = xperm(longmod, [3 4 2 1 5 6]); % reorder state

        
        %% GENERATE SHORT PERIOD LINEAR MODEL
        % Short period dynamics
        % States:   w(9)  q(5)
        % Inputs: elevator(2)
        % Outputs:  alpha(12) q(5) az(9)
        
        % Generate State-space matrices for Longitudinal Model
        % Indices for desired state, outputs, and inputs
%         Xlon = [9 5];
%         Ylon = [12 5 9];
%         Ilon = 2;
%         spmod = modred(linmodel(Ylon,Ilon), setdiff(1:13,Xlon), 'Truncate');

        
        %% GENERATE LATERAL-DIRECTIONAL LINEAR MODEL
        % Lateral-directional dynamics
        % States: v(8) p(4) r(6) phi(1) psi(3)
        % Inputs: aileron(3) aileron(4) rudder(5)
        % Outputs: beta(11) p(4) r(6) phi(1) psi(3)
        
        % Generate State-space matrices for lateral-directional Model
        % Indices for desired state, outputs, and inputs
%         Xlat = [8 4 6 1 3];
%         Ylat = [11 4 6 1 3];
%         Ilat = [3 4 5];
%         latmod = modred(linmodel(Ylat, Ilat),setdiff(1:13, Xlat),'Truncate');
%         latmod = xperm(latmod,[5 3 4 1 2]); % reorder state



%% Cleanup
if ~isLoaded
    bdclose(simModel) % clear model from system memory if we had to load it
end
