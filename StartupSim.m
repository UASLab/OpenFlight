% Start file for the 'UMN OpenFlight Simulation'.
%
%Notes:
% This should be called prior to using Sim functions.
% Remember that the matlab path list gives priority to paths listed at the
% top.
%

%Version History: Version 1.0
% 04/12/2017  C. Regan     Initial Release (v1.0)
%


%% Set the base simulation directory
[filePath, ~] = fileparts(mfilename('fullpath'));

 
%% Add paths
% Turn off multiple path warning
warning('off', 'MATLAB:dispatcher:pathWarning');

% Add paths, excluding those containing 'CVS'
addpath(genpath(filePath))

% Turn on multiple path warning
warning('on', 'MATLAB:dispatcher:pathWarning');


%% Cleanup
clear filePath
